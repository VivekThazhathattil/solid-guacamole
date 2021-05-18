#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <vector>
#include <iostream>
#include <cassert>

class Matrix{
	public:
		Matrix(const unsigned rows, const unsigned cols);
		~Matrix();

		double& operator()(const unsigned x, const unsigned y) { return p[x][y]; }
		void set(const unsigned x, const unsigned y, const double val);
		void print() const;
		void transpose(); // transpose in place
		Matrix& T(); // transpose in place and return pointer to  matrix

		Matrix& operator += (const Matrix&);
		Matrix& operator -= (const Matrix&);
		Matrix& operator *= (const Matrix&); // matrix mult
		Matrix& operator *= (double); // scalar mult
		Matrix& operator /= (double); // scalar div

		unsigned getRows() const{ return m_rows; }
		unsigned getCols() const{ return m_cols; }
	private:
		unsigned m_rows;
		unsigned m_cols;
		std::vector< std::vector <double> > p;
};

Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, double num);
Matrix operator/(const Matrix&, double num);

#endif
