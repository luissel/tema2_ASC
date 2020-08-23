/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("OPT SOLVER\n");
	int i, j, k;
	register double sum = 0;
	register double *res, *orig_pa, *pa, *pb, *pat, *orig_pb, *orig_pa2, *pa2, *pbb;
	
	double *A_2 = (double *) calloc(N * N, sizeof(double));
	if (A_2 == NULL) 
		return NULL;

	double *result = (double *) calloc(N * N, sizeof(double));
	if (result == NULL) 
		return NULL;

	// A^2
	for (i = 0; i < N; ++i) {
		orig_pa = A + i * N;
		res = A_2 + i * N + i;

		for (j = i; j < N; ++j, ++res) {
			sum = 0;
			pa = orig_pa;
    		pb = A + j;

			for (k = 0; k <= j; ++k, ++pa, pb += N) {
				sum += *pa * *pb;
			}

			*res = sum;
		}
	}

	// B * At
	for (i = 0; i < N; ++i) {
		orig_pb = B + i * N;
		res = result + i * N;
		
		for (j = 0; j < N; ++j, ++res) {
			sum = 0;
			pb = orig_pb + j;
			pat = A + j * N + j;
			
			for (k = j; k < N; ++k, ++pb, ++pat) {
				sum += *pb * *pat;
			}

			*res += sum;
		}
	}
	
	// A^2 * B
	for (i = 0; i < N; ++i) {
		orig_pa2 = A_2 + i * N + i;
		res = result + i * N;
		
		for (j = 0; j < N; ++j, ++res) {
			sum = 0;
			pa2 = orig_pa2;
			pbb = B + i * N + j;
			
			for (k = i; k < N; ++k, ++pa2, pbb += N) {
				sum += *pa2 * *pbb;
			}

			*res += sum;
		}
	}

	free(A_2);
	return result;	
}
