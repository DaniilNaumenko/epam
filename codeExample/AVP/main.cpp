#include <stdio.h>
#include <Windows.h>
#include <cstdint>

#include "Matrix.h"
#include "MatrixMultiplier.h"
#include "SSE2MatrixMultiplier.h"
#include "VectorizedMatrixMultiplier.h"
#include "WithoutVectorizedMatrixMultiplier.h"
#include "MatrixFunctions.h"

#define BIG_COLUMN 200
#define BIG_LINE 200

#define SMALL_COLUMN 2
#define SMALL_LINE 4

typedef float MatrixType;

int main() {
	LONGLONG start, end, noVectorizedTime, vectorizedTime, sse2Time;

	auto a = Matrix<MatrixType>(BIG_COLUMN, BIG_LINE, SMALL_COLUMN, SMALL_LINE);
	auto b = Matrix<MatrixType>(BIG_COLUMN, BIG_LINE, SMALL_LINE, SMALL_COLUMN);

	auto utils = new MatrixFunctions<MatrixType>;

	utils->RandomizeMatrix(a);
	utils->RandomizeMatrix(b);


	start = GetTickCount64();
	auto nonVectorizedResult = (new WithoutVectorizedMatrixMultiplier<MatrixType>())->Multiply(a, b);
	end = GetTickCount();

	noVectorizedTime = end - start;

	printf("Time without vectorization: %d milliseconds.\n", noVectorizedTime);



	start = GetTickCount64();
	auto vectorizedResult = (new VectorizedMatrixMultiplier<MatrixType>())->Multiply(a, b);
	end = GetTickCount();

	vectorizedTime = end - start;

	printf("\nTime with vectorization: %d milliseconds.\n", vectorizedTime);
	printf("Vectorized equals without vectorized: %s.\n", utils->Equals(*nonVectorizedResult, *vectorizedResult) ? "true" : "false");



	start = GetTickCount64();
	auto sseResult = (new SseMatrixMultiplier<MatrixType>())->Multiply(a, b);
	end = GetTickCount();

	sse2Time = end - start;

	printf("\nTime SSE2 (Intrinsics): %d milliseconds.\n", sse2Time);
	printf("SSE2 equals to vectorized: %s.\n", utils->Equals(*sseResult, *vectorizedResult) ? "true" : "false" );


	system("pause");
}