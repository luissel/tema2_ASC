/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("NEOPT SOLVER\n");
	int i, j, k;
	
	double *A_2 = (double *) calloc(N * N, sizeof(double));
	if (A_2 == NULL) 
		return NULL;

	double *At = (double *) calloc(N * N, sizeof(double));
	if (At == NULL) 
		return NULL;

	double *C = (double *) calloc(N * N, sizeof(double));
	if (C == NULL) 
		return NULL;

	double *D = (double *) calloc(N * N, sizeof(double));
	if (D == NULL) 
		return NULL;

	double *result = (double *) calloc(N * N, sizeof(double));
	if (result == NULL) 
		return NULL;

	// A^2 
	for (i = 0; i < N; ++i) {
		for (j = i; j < N; ++j) {
			for (k = 0; k <= j; ++k) {
				A_2[i * N + j] += A[i * N + k] * A[k * N + j];
			}
		}
	}

	// At
	for (i = 0; i < N; ++i) {
		for (j = i; j < N; ++j) {
			At[j * N + i] = A[i * N + j];
		}
	}

	// B * At 
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = j; k < N; k++) {				
				C[i * N + j] += B[i * N + k] * At[k * N + j];
			}

		}
	}

	// A^2 * B
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = i; k < N; k++) {				
				D[i * N + j] += A_2[i * N + k] * B[k * N + j];
			}

		}
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {	
			result[i * N + j] = C[i * N + j] + D[i * N + j];
		}
	}
	
	free(A_2);
	free(At);
	free(C);
	free(D);
	return result;
}
