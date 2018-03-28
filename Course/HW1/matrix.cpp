#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <new>
#include "matrix.h"

Matrix::Matrix(const int &r, const int &c) //constructor
{
	row = r;
	col = c;
	array = new double *[row];
	for (int i = 0; i < row; ++i)
	{
		array[i] = new double[col];
		for (int j = 0; j < col; ++j)
		{
			array[i][j] = 0;
		}
	}
}

Matrix::Matrix(const Matrix &m) //copy constructor
{
	row = m.row;
	col = m.col;
	array = new double *[m.row];
	for (int r = 0; r < m.row; r++)
	{
		array[r] = new double[m.col];
		for (int c = 0; c < m.col; c++)
		{
			array[r][c] = m.array[r][c];
		}
	}
}

Matrix::~Matrix() //destructor
{
	for (int i = 0; i < row; ++i)
	{
		delete[] array[i];
	}
	delete[] array;
}

double *&Matrix::operator[](const int &idx) const // Enable the use of A[i][j] instead of m.array[i][j]
{
	return array[idx];
}

Matrix Matrix::operator=(const Matrix &m) // assignment operator
{
	row = m.row;
	col = m.col;
	array = new double *[m.row];
	for (int r = 0; r < m.row; r++)
	{
		array[r] = new double[m.col];
		for (int c = 0; c < m.col; c++)
		{
			array[r][c] = m.array[r][c];
		}
	}
	return *this;
}

Matrix Matrix::operator-() const
{
	Matrix tmp(*this);
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			tmp[r][c] = -array[r][c];
		}
	}
	return tmp;
}

Matrix Matrix::operator+() const
{
	return *this;
}

Matrix Matrix::operator-(const Matrix &m) const
{
	Matrix tmp(*this);
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			tmp[r][c] = array[r][c] - m[r][c];
		}
	}
	return tmp;
}

Matrix Matrix::operator+(const Matrix &m) const
{
	Matrix tmp(*this);
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			tmp[r][c] = array[r][c] + m[r][c];
		}
	}
	return tmp;
}

Matrix Matrix::operator*(const Matrix &m) const
{
	Matrix temp(row, m.col);
	for (int i = 0; i < temp.row; i++)
	{
		for (int j = 0; j < temp.col; j++)
		{
			for (int k = 0; k < col; k++)
			{
				temp.array[i][j] += (array[i][k] * m.array[k][j]);
			}
		}
	}
	return temp;
}

Matrix Matrix::operator/(const Matrix &m) const
{
	return *this * m.inverse();
}

Matrix Matrix::inverse() const
{
	// Gauss-Jordan Elimination
	if (row != col)
	{
		throw "Cannot get inverse if not N x N!";
	}
	int matrixSize = row;
	// Step 1. Make [A] to [A|I]
	Matrix temp(matrixSize, 2 * matrixSize);
	for (int r = 0; r < matrixSize; r++)
	{
		for (int c = 0; c < matrixSize; c++)
		{
			temp[r][c] = array[r][c];
		}
		temp[r][matrixSize + r] = 1;
	}

	// Step 2. Create upper triangular matrix
	for (int i = 0; i < matrixSize - 1; i++)
	{
		for (int r = i + 1; r < matrixSize; r++)
		{
			if (temp[r][i] != 0)
			{
				double coefficient = temp[i][i] / temp[r][i];
				for (int c = 0; c < matrixSize * 2; c++)
				{
					temp[r][c] = temp[i][c] - coefficient * temp[r][c];
				}
			}
		}
	}

	// Normolize left part
	for (int r = 0; r < matrixSize; r++)
	{
		double coefficient = temp[r][r];
		for (int c = 0; c < matrixSize * 2; c++)
		{
			temp[r][c] /= coefficient;
		}
	}

	// Step 3. From upper triangular matrix get [I|B]
	for (int i = matrixSize - 1; i > 0; i--)
	{
		for (int r = i - 1; r >= 0; r--)
		{
			double coefficient = -temp[r][i];
			for (int c = 0; c < matrixSize * 2; c++)
			{
				temp[r][c] += coefficient * temp[i][c];
			}
		}
	}

	// Step 4. Get B
	Matrix result(matrixSize, matrixSize);
	for (int r = 0; r < matrixSize; r++)
	{
		for (int c = 0; c < matrixSize; c++)
		{
			result[r][c] = temp[r][matrixSize + c];
		}
	}
	return result;
}

void Matrix::read(const char *fn)
{
	int r, c;
	FILE *fp = fopen(fn, "r");
	if (fp == NULL)
	{
		printf("read file [%s] error\n", fn);
		exit(0);
	}
	fscanf(fp, "%d%d", &r, &c);
	Matrix tmp(r, c);
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			fscanf(fp, "%lf", &tmp.array[i][j]);
	fclose(fp);
	*this = tmp;
}

void Matrix::write(const char *fn)
{
	FILE *fp = fopen(fn, "w");
	if (fp == NULL)
	{
		printf("write file [%s] error\n", fn);
		exit(0);
	}
	fprintf(fp, "%d %d\n", row, col);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			fprintf(fp, "%lf%c", array[i][j], " \n"[j == col - 1]);
	fclose(fp);
}

void Matrix::print() const
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			printf("%lf%c", array[i][j], " \n"[j == col - 1]);
}