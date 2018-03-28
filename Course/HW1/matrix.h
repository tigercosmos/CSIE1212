#ifndef __MATRIX_H__
#define __MATRIX_H__

class Matrix{
	public:
		double **array;
		int row;
		int col;

		Matrix(const int&, const int&); 	//constuctor
		Matrix(const Matrix&); 				//copy constructor
		~Matrix();							//destructor

		double* & operator [](const int&) const;
		Matrix operator =(const Matrix&);
		//unary operators
		Matrix operator -() const;
		Matrix operator +() const;
		//binary operators
		Matrix operator -(const Matrix&) const;
		Matrix operator +(const Matrix&) const;
		Matrix operator *(const Matrix&) const;
		Matrix operator /(const Matrix&) const;
		
		void read(const char*);
		void write(const char*);
		void print() const;
		Matrix inverse() const;
};

#endif