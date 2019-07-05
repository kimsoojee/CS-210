#include <stdio.h>

#define N 8

int matrix[N][N];

void print_matrix(){
    int i,j;
    for ( i = 0 ; i < N ; i++ ){
        for( j = 0 ; j < N ; j++ ){
            printf( "%d ", matrix[i][j]);
        }
        printf( "\n" );
    }
    printf( "\n" );
}

int valid( int i , int j ){
    
    for (int x = 0; x < N; x++){ //check col and row
        if ((matrix[x][j]) | (matrix[i][x]))
            return 0;
    }
    for (int x = i, y = j; x >= 0 && y >= 0; x--,y--){ // left upward diagonal
        if (matrix[x][y])
            return 0;
    }
    for (int x = i, y = j; x < N && y >= 0; x++,y--){ // left downward diagonal
        if (matrix[x][y])
            return 0;
    }
    
    for (int x = i, y = j; x >= 0 && y < N; x--,y++){ // right upward diagonal
        if (matrix[x][y])
            return 0;
    }
    for (int x = i, y = j; x < N && y < N; x++,y++){ // left downward diagonal
        if (matrix[x][y])
            return 0;
    }

    
    return 1;
}

int count = 0;
void putall( int id ){ /*id: index for the current queen*/
    for ( int i = id * N; i < 8*8 ; i++ ){
        if( valid(i/8, i%8) ){ //if current position is a valid one
            matrix[i/8][i%8] = 1;
            if( id == N-1 ){  //if this is the last one to place
                //find a solution and output result
                count += 1; //count the solution
                printf("%dsolution\n", count);
                print_matrix();
                
            }
            else{
                //calculate the start_position for next queen.
                putall( id + 1 );
            }
            matrix[i/8][i%8] = 0; //if this is not right position, make it 0
        }
    }
}

    
int main() {
    putall(0);
}

