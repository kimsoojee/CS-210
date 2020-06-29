//
//  final.c
//  PA
//
//  Created by 김수지 on 11/18/17.
//  Copyright © 2017 SooJee Kim, Daisy Luo. All rights reserved.
//

// ************* TEAM : Daisy Luo, SooJee Kim *******************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *addrs_t;
typedef void *any_t;

typedef struct MemBlock {
	struct MemBlock *next;
	struct MemBlock *prev;
	int isFree;
	size_t size;
} MemBlock;

MemBlock *M1;

typedef struct VMemBlock {
	struct VMemBlock *next;
	struct VMemBlock *prev;
	size_t size;
	addrs_t *RT_cell;
} VMemBlock;

VMemBlock *M2;
VMemBlock *tail_M2;
addrs_t *RT;

size_t subtractSize(size_t size, size_t structSize) {
	if ((int)size - (int)structSize < 0) {
		return 0;
	}
	return size - structSize;
}

void Init(size_t size) {

	// initialize the memory management list
	M1 = (MemBlock*) malloc(size);
	M1->next = NULL;
	M1->prev = NULL;
	M1->isFree = 1;      //free = 1, otherwise = 0
	M1->size = subtractSize(size, sizeof(MemBlock));
}

void VInit(size_t size) {

	M2 = (VMemBlock*) malloc(size);
	M2->next = NULL;
	M2->prev = NULL;
	M2->RT_cell = NULL;
	M2->size = subtractSize(size, sizeof(VMemBlock));
	tail_M2 = M2;

	//allocating memory for the redirection table array, minimum block size is 8 bytes, so we may need up to ceil(size/(8 + sizeof(VMemBlock))) blocks
	int maxRtSize = (size + 8 + sizeof(VMemBlock) - 1) / (8 + sizeof(VMemBlock));
	RT = (addrs_t*) malloc(maxRtSize * sizeof(addrs_t));
	int i;
	for (i = 0; i < maxRtSize; i++) {
		RT[i] = NULL;
	}
}

addrs_t Malloc(size_t size) {

	if (size <= 0) {     // If size is zero or negative value, return NULL
		return NULL;
	}

	MemBlock *block = M1;
	while (!(block->isFree) || block->size < size) {
		block = block->next;
		if (block == NULL) {
			return NULL;  // We went through whole list, no available memory
		}
	}

	// Align each block at a multiple of 8
	int blockSize = size;
	if (blockSize % 8) {
		blockSize += 8 - (size % 8);
	}
	int leftoverSize = subtractSize(subtractSize(block->size, blockSize), sizeof(MemBlock));

	// If this block is larger than what we need, split it
	if (leftoverSize > 0) {

		MemBlock *leftover = (MemBlock*) ((addrs_t) block + blockSize
				+ sizeof(MemBlock));

		leftover->next = block->next;
		leftover->size = leftoverSize;
		leftover->isFree = 1;
		leftover->prev = block;
		if (leftover->next != NULL) {
			leftover->next->prev = leftover;
		}
		block->next = leftover;
		block->size = blockSize;
	}

	block->isFree = 0;
	return (addrs_t) block + sizeof(MemBlock);
}

addrs_t *VMalloc(size_t size) {
	if (size <= 0) {     // If size is zero or negative value, return NULL
		return NULL;
	}
	if (tail_M2->size < size) {
		return NULL; // not enough available memory
	}

	int i = 0;
	while (RT[i] != NULL) {
		i++; //find the first available index in the redirection table
	}

	VMemBlock *block = tail_M2;

	// Align each block at a multiple of 8
	int blockSize = size;
	if (blockSize % 8) {
		blockSize += 8 - (size % 8);
	}
	int leftoverSize = subtractSize(subtractSize(block->size, blockSize), sizeof(VMemBlock));

	if (leftoverSize > 0) {

		VMemBlock *leftover = (VMemBlock*) ((addrs_t) block + blockSize
				+ sizeof(VMemBlock));
		leftover->next = NULL;
		leftover->size = leftoverSize;
		leftover->prev = block;
		block->next = leftover;
		block->size = blockSize;
		block->RT_cell = RT + i;
		tail_M2 = leftover;
	}
	else {
		return NULL;  // Not enough memory to allocate another VMemBlock
	}
	RT[i] = (addrs_t) block + sizeof(VMemBlock);
	return RT + i; // pointer to cell i in redirection table

}

void Free(addrs_t addr) {

	MemBlock *block = (MemBlock*) (addr - sizeof(MemBlock));
	MemBlock *prev = block->prev;
	MemBlock *next = block->next;

	block->isFree = 1; // Free the block

	// Merge with previous block
	while (prev != NULL && prev->isFree) {
		prev->size = prev->size + block->size + sizeof(MemBlock);
		prev->next = next;
		if (next != NULL) {
			next->prev = prev;
		}
		block = prev;
		prev = block->prev;
	}

	// Merge with next block
	while (next != NULL && next->isFree) {
		block->size = block->size + next->size + sizeof(MemBlock);
		block->next = next->next;
		next = block->next;
		if (next != NULL) {
			next->prev = block;
		}
	}
}

void VFree(addrs_t *addr) {
	VMemBlock *block = (VMemBlock*) (*addr - sizeof(VMemBlock));
	tail_M2->size = tail_M2->size + block->size + sizeof(VMemBlock);

	// remove block from linked list
	if (block->next != NULL) {
		block->next->prev = block->prev;
	}
	if (block->prev != NULL) {
		block->prev->next = block->next;
	}

	VMemBlock *moveTo = block;
	VMemBlock *current = block->next;

	// slide each memory block left
	while (current != NULL) {
		VMemBlock *prev = current->prev;
		VMemBlock *next = current->next;
		if (prev != NULL) {
			prev->next = moveTo;
		}
		if (next != NULL) {
			next->prev = moveTo;
		}
		if (current == tail_M2) {
			tail_M2 = moveTo;
		} else {
			*(current->RT_cell) = (addrs_t) moveTo + sizeof(VMemBlock);
		}
		memmove(moveTo, current, current->size + sizeof(VMemBlock));
		moveTo = (VMemBlock*) ((addrs_t) moveTo + moveTo->size
				+ sizeof(VMemBlock));

		current = next;

	}
	*addr = NULL; // NULL out the spot in the redirection table

}

addrs_t Put(any_t data, size_t size) {

	addrs_t address = Malloc(size);

	if (address == NULL) {
		return NULL; // Memory could not be allocated
	}

	memcpy(address, data, size);
	return address;
}

addrs_t *VPut(any_t data, size_t size) {
	addrs_t *address = VMalloc(size);

	if (address == NULL) {
		return NULL; // Memory could not be allocated
	}

	memcpy(*address, data, size);
	return address;


}

void Get(any_t return_data, addrs_t addr, size_t size) {

	memcpy(return_data, addr, size);
	Free(addr);
}

void VGet(any_t return_data, addrs_t *addr, size_t size) {
	memcpy(return_data, *addr, size);
	VFree(addr);
}
