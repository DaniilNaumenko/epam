#pragma once

#include "MatrixMultiplier.h"

#include <Windows.h>

#include "immintrin.h"

template <typename T> class SseMatrixMultiplier : public MatrixMultiplier<T> {
public:
	Matrix<T>* Multiply(Matrix<T>& firstMatrix, Matrix<T>& secondMatrix) override {
		Matrix<T>* resultMatrix = new Matrix<T>(firstMatrix.bigColumn, secondMatrix.bigLine, firstMatrix.smallColumn, secondMatrix.smallLine);

		for (auto m = 0; m < firstMatrix.bigColumn; m++) {
			for (auto n = 0; n < secondMatrix.bigLine; n++) {
				for (auto l = 0; l < resultMatrix->bigLine; l++) {
					for (auto i = 0; i < resultMatrix->smallColumn; i++) {
						T *__restrict temp = resultMatrix->matrix[m][n][i];
						for (auto j = 0; j < secondMatrix.smallLine; j++) {
							T *__restrict temp2 = secondMatrix.matrix[l][n][j];

							const __m128 buff = { 
								firstMatrix.matrix[m][l][i][j],
								firstMatrix.matrix[m][l][i][j],
								firstMatrix.matrix[m][l][i][j],
								firstMatrix.matrix[m][l][i][j]
							};

							for (auto k = 0; k < resultMatrix->smallLine; k += 4) { 
								__m128 res = _mm_add_ps(_mm_mul_ps(buff, *reinterpret_cast<__m128*>(temp2 + k)), *reinterpret_cast<__m128*>(temp + k));
								//_mm_store_ps(temp + k, res);
								memcpy(temp + k, &res, sizeof(res));
							}
						}
					}
				}
			}
		}

		return resultMatrix;
	}
};