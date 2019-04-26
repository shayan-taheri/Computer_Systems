// Shayan Taheri (A01956093)

/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) {
  
    // Defining the variables in this pogram
  
    int block_size = 0;
    int temp = 0;
    int index = 0;
    int last = 0;
    int block_row = 0;
    int block_column = 0;
    int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;

    // When M == N == 32 bits. it would be really helpful if we consider the technique of blocking or loop interchange !
    
    if ((M == 32) && (N == 32)) {
      
	block_size = 8;
	temp = 0;
	index = 0;
	last = 0;
	block_row = 0;
	block_column = 0;
	i = 0;
	j = 0;
	for (block_column = 0; block_column < M; block_column += block_size) {
	for (block_row = 0; block_row < N; block_row += block_size) {
	for (i = block_row; (i < block_row + block_size) && (i < N); i++) {
	for (j = block_column; (j < block_column + block_size) && (j < M); j++) {

	if (i != j) {
	  B[j][i] = A[i][j];}
	
	if (i == j) {
	  temp = A[i][j];
	  index = i;
	  last = 1;}}

	if (last == 1) {
	  B[index][index] = temp;
	  last = 0;}
	}}}}
	
/* When M == N == 64 bits. This mode can be done by loop unrolling and considering 8 variable for saving data.
   Maybe the names of variables are confusing but they don't mean anything in this condition and because of
   the limitation for defining new variables, I have used previous ones. */
	
    if ((M == 64) && (N == 64)) {
      
	block_size = 0;
	temp = 0;
	index = 0;
	last = 0;
	block_row = 0;
	block_column = 0;
	i = 0;
	j = 0;
	x = 0;
	y = 0;
	
	for(j = 0; j < 64 ; j += 8 ) {
           for(N = 0; N < 64 ; N += 8) {
	     for (i = N ;i < N + 8 ; i += 2) {
	     
	     block_size = A[i][j];
             temp = A[i][j+1];
             index = A[i][j+2];
             last = A[i][j+3];

	     block_row = A[i+1][j];
	     block_column = A[i+1][j+1];
	     x = A[i+1][j+2];
	     y = A[i+1][j+3];

             B[j][i] = block_size;
             B[j+1][i] = temp;
             B[j+2][i] = index;
             B[j+3][i] = last;

             B[j][i+1]= block_row;
             B[j+1][i+1] = block_column;
             B[j+2][i+1] = x;
             B[j+3][i+1] = y;}
             
             for (i = N + 7 ; i >= N ; i -= 2) {
	            
	     block_size = A[i][j+4];
             temp = A[i][j+5];
             index = A[i][j+6];
             last = A[i][j+7];

	     block_row = A[i-1][j+4];
	     block_column = A[i-1][j+5];
	     x = A[i-1][j+6];
	     y = A[i-1][j+7];

             B[j+4][i] = block_size;
             B[j+5][i] = temp;
             B[j+6][i] = index;
             B[j+7][i] = last;

             B[j+4][i-1]= block_row;
             B[j+5][i-1] = block_column;
             B[j+6][i-1] = x;
             B[j+7][i-1] = y;}
	
	   }}}
	
    /* For this one, We should first consider a portion of the cache that is hard to be implemented. First, I have defined
    a smaller block and then improve it by adding some specification */
	
    if ((M == 61) && (N == 67)) {
      
	temp = 0;
	index = 0;
	last = 0;
	block_row = 0;
	block_column = 0;
	i = 0;
	j = 0;
	for (block_row = 0; block_row < 60; block_row += 20) {
	for (block_column = 0; block_column < 60; block_column += 6) {
	for (i = block_row; i < block_row + 20; i++) {
	for (j = block_column; j < block_column + 6; j++) {

	if (i != j) {
	  B[j][i] = A[i][j];}
	
	if (i == j) {
	  temp = A[i][j];
	  index = i;
	  last = 1;}}

	if (last == 1) {
	  B[index][index] = temp;
	  last = 0;}
	}}}
	
	for (i = 0; i <= 65; i++) {
	  if (i != 60) {
	    B[60][i] = A[i][60];}
	  if (i == 60) {
	    temp = A[i][60];}}
	    
	    B[60][60] = temp;
	    
	for (block_row = 60; block_row < 66; block_row += 6) {
	for (block_column = 0; block_column < 60; block_column += 6) {
	for (i = block_row; i < block_row + 6; i++) {
	for (j = block_column; j < block_column + 6; j++) {
	    
	  B[j][i] = A[i][j];}}}}
	  
	for (j = 0; j <= 60; j++) {
	  B[j][66] = A[66][j];}
	    
    }
	
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

