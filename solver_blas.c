/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"
#include "cblas.h"

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");
	int i, j;
	double *C = (double *) calloc(N * N, sizeof(double));
	if (C == NULL) 
		return NULL;

	double *D = (double *) calloc(N * N, sizeof(double));
	if (D == NULL) 
		return NULL;

	double *A_2 = (double *) calloc(N * N, sizeof(double));
	if (A_2 == NULL) 
		return NULL;

	// copiez matricele A si B in matrice auxiliare
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			int index = i * N + j;

			A_2[index] = A[index];
			C[index] = B[index];
			D[index] = B[index];
		}
	}

	// A^2
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit,
				N, N, 1, A, N, A_2, N);

	// B * At
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans, CblasNonUnit,
				N, N, 1, A, N, C, N);
	
	// A_2 * B
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit,
				N, N, 1, A_2, N, D, N);

	// rezultatul final
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			C[i * N + j] += D[i * N + j];
		}
	}

	free(D);
	free(A_2);

	return C;
}
