LIBS        = -lm
INC_PATH    = -I.
CC_FLAGS    = -g

all: pa31 pa32

pa31: hcheck.o pa3.o
	cc $(CC_FLAGS) $(INC_PATH) -o $@ hcheck.c $(LIBS)

pa32: hcheck.o pa3.o
	cc -DVHEAP $(CC_FLAGS) $(INC_PATH) -o $@ hcheck.c $(LIBS)


clean :
	rm -f *.o *~ $(PROGS)
