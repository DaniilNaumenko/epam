#pragma once

template <typename T> class Matrix {
public:
	T**** matrix; 

	const int bigColumn;
	const int bigLine;
	const int smallColumn;
	const int smallLine;
	
	Matrix(int bigColumn, int bigLine, int smallColumn, int smallLine) 
		: bigColumn(bigColumn), bigLine(bigLine), smallColumn(smallColumn), smallLine(smallLine) {
		this->matrix = new T***[bigColumn];
		for (int i = 0; i < bigColumn; i++) {
			this->matrix[i] = new T**[bigLine];
			for (int j = 0; j < bigLine; j++) {
				this->matrix[i][j] = new T*[smallColumn];
				for (int k = 0; k < smallColumn; k++) {
					this->matrix[i][j][k] = new T[smallLine];
					for (int m = 0; m < smallLine; m++) {
						matrix[i][j][k][m] = 0;
					}
				}
			}
		}
	}

	~Matrix() {
		for (auto i = 0; i < bigColumn; i++) {
			for (auto j = 0; j < bigLine; j++) {
				for (auto k = 0; k < smallColumn; k++) {
					delete[] matrix[i][j][k];
				}
				delete[] matrix[i][j];
			}
			delete[] matrix[i];
		}
		delete[] matrix;
	}
};