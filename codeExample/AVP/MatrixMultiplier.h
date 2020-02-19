#pragma once

template <typename T> class MatrixMultiplier {
public:
	virtual Matrix<T>* Multiply(Matrix<T>& firstMatrix, Matrix<T>& secondMatrix) = 0;
};