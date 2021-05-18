#include "include/matrix.h"

Matrix::Matrix(const unsigned rows, const unsigned cols){
	m_rows = rows;
	m_cols = cols;
	/* initialize all elements with 0s */
	for(unsigned i = 0; i < m_rows; ++i){
		p.push_back(std::vector<double>());
		for(unsigned j = 0; j < m_cols; ++j)
			p[i].push_back(0);
	}
}

Matrix::~Matrix(){
}

void Matrix::print() const {
	for(unsigned i = 0; i < m_rows; ++i){
		for(unsigned j = 0; j < m_cols; ++j)
			std::cout << p[i][j] << " ";
		std::cout << std::endl;
	}
}

void Matrix::set(const unsigned x, const unsigned y, const double val){
	assert( x < m_rows && y < m_cols);
	p[x][y] = val;
}

void Matrix::transpose(){
	/* swap row and column numbers*/
	unsigned temp = m_rows;
	m_rows = m_cols;
	m_cols = temp;

	/* swap elements in the matrix */
	std::vector< std::vector <double> > p_old = p;	
	p.clear();
	for(unsigned i = 0; i < m_rows; ++i){
		p.push_back(std::vector<double>());
		for(unsigned j = 0; j < m_cols; ++j)
			p[i].push_back(p_old[j][i]);
	}
}

Matrix& Matrix::T(){
	transpose();
	return (*this);
}

Matrix& Matrix::operator+=(const Matrix& m){
	for(unsigned i = 0; i < m_rows; ++i)
		for(unsigned j = 0; j < m_cols; ++j)
			p[i][j] += m.p[i][j];
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& m){
	for(unsigned i = 0; i < m_rows; ++i)
		for(unsigned j = 0; j < m_cols; ++j)
			p[i][j] -= m.p[i][j];
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& m){
	assert( m_cols == m.m_rows);
	Matrix temp(m_rows, m.m_cols);
	for(unsigned i = 0; i < m_rows; ++i)
		for(unsigned j = 0; j < m_cols; ++j)
			for( unsigned k = 0; k < m_cols; ++k)
				temp.p[i][j] += p[i][k]*m.p[k][j];
	return (*this = temp);
}

Matrix& Matrix::operator*=(double num){
	for(unsigned i = 0; i < m_rows; ++i)
		for(unsigned j = 0; j < m_cols; ++j)
			p[i][j] *= num;
	return *this;
}

Matrix& Matrix::operator/=(double num){
	assert(num != 0.0);
	for(unsigned i = 0; i < m_rows; ++i)
		for(unsigned j = 0; j < m_cols; ++j)
			p[i][j] /= num;
	return *this;
}

Matrix operator+(const Matrix& m1, const Matrix& m2){
	Matrix temp(m1);
	return (temp += m2);
}

Matrix operator-(const Matrix& m1, const Matrix& m2){
	Matrix temp(m1);
	return (temp -= m2);
}

Matrix operator*(const Matrix& m1, const Matrix& m2){
	Matrix temp(m1);
	return (temp *= m2);
}

Matrix operator*(const Matrix& m1, double num){
	Matrix temp(m1);
	return (temp *= num);
}


Matrix operator/(const Matrix& m1, double num){
	Matrix temp(m1);
	return (temp /= num);
}
