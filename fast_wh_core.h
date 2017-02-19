#include <math.h>
#include <stdlib.h>

/* Min, max functions */
#define MIN(X, Y)           (((X) < (Y)) ?  (X):(Y))
#define MAX(X, Y)           (((X) > (Y)) ?  (X):(Y))

#define COLUMNS 	0
#define ROWS 		1

#define TRUE 		1
#define FALSE 		0

/* Computes log to base 2 */
double log2(double n);

/* Base implementation of hadamard transform. WARNING: this function 
 * modifies the entries of work variable */
void _fast_wh(double *work, int N, double *output, unsigned char scale_output);

/* Computes Hadamard transform for vectors */
void fast_wh_vec(double *input, int N, double *output,
	   			 unsigned char scale_output);

/* Computes Hadamard transform for matrices. Storage is row major */
void fast_wh_mat(double *input, int M, int N, double *output, unsigned char dir,
				 unsigned char scale_output);
