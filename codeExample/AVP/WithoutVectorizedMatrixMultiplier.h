#pragma once

#include "MatrixMultiplier.h"

#include <stdlib.h>

template <typename T> class WithoutVectorizedMatrixMultiplier : public MatrixMultiplier<T> {
	void mul(Matrix<T>& firstMatrix, Matrix<T>& secondMatrix, Matrix<T>* resultMatrix, int m, int n, int l) {
		for (auto i = 0; i < firstMatrix.smallColumn; i++) {
			T* __restrict temp = resultMatrix->matrix[m][n][i];

			for (auto j = 0; j < secondMatrix.smallLine; j++) {
				T* __restrict temp2 = secondMatrix.matrix[l][n][j];

#pragma loop(no_vector)
				for (auto k = 0; k < secondMatrix.smallLine; k++) {
					temp[k] += firstMatrix.matrix[m][l][i][j] * temp2[k];
				}
			}
		}
	}

public:
	Matrix<T>* Multiply(Matrix<T>& firstMatrix, Matrix<T>& secondMatrix) override {
		Matrix<T>* resultMatrix = new Matrix<T>(firstMatrix.bigColumn, secondMatrix.bigLine, firstMatrix.smallColumn, secondMatrix.smallLine);

		for (auto m = 0; m < firstMatrix.bigColumn; m++) {
			for (auto n = 0; n < secondMatrix.bigLine; n++) {
				for (auto l = 0; l < firstMatrix.bigLine; l++) {
					mul(firstMatrix, secondMatrix, resultMatrix, m, n, l);
				}
			}
		}

		return resultMatrix;
	}
};