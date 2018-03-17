#include <cstdio>
#include <cstdlib>
#include <string>
#include "matrix.h"

void rand_gen(const Matrix &a)
{
	for (int i = 0; i < a.row; i++)
		for (int j = 0; j < a.col; j++)
			a[i][j] = rand() % 10;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage : ./a.out [cmd]\n");
		exit(0);
	}
	std::string cmd(argv[1]);

	if (cmd == "construct")
	{
		{
			Matrix a(3, 4);
			Matrix b(2, 8);
			Matrix c(a);
			Matrix d(b);
		}
		puts("end");
	}
	else if (cmd == "index")
	{
		Matrix a(3, 4);
		Matrix b(2, 8);
		rand_gen(a);
		rand_gen(b);
		Matrix c(a);
		Matrix d(b);
		a.print();
		b.print();
		c.print();
		d.print();
	}
	else if (cmd == "assign")
	{
		Matrix a(7, 3);
		Matrix b(11, 5);
		Matrix c(a);
		rand_gen(a);
		rand_gen(c);
		b = a;
		b.print();
		b = c;
		b.print();
		c = b = a;
		b.print();
		c.print();
	}
	else if (cmd == "unary")
	{
		Matrix a(3, 7);
		Matrix b(a);
		rand_gen(a);
		b = -a;
		a.print();
		b.print();
		Matrix c(+b);
		a.print();
		b.print();
		c.print();
	}
	else if (cmd == "add")
	{
		Matrix a(11, 6);
		Matrix b(a);
		Matrix c(b);
		rand_gen(a);
		rand_gen(c);
		a.print();
		c.print();
		b = a + c;
		b.print();
		a = a + b;
		a.print();
		c = a + b + c;
		c.print();
	}
	else if (cmd == "subtract")
	{
		Matrix a(14, 3);
		Matrix b(a);
		Matrix c(b);
		rand_gen(a);
		rand_gen(c);
		a.print();
		c.print();
		b = a - c;
		b.print();
		a = a - b;
		a.print();
		c = a - b - c;
		c.print();
	}
	else if (cmd == "mult")
	{
		Matrix a(7, 8);
		Matrix b(8, 7);
		Matrix c(a);
		Matrix d(b);
		rand_gen(a);
		rand_gen(b);
		rand_gen(c);
		rand_gen(d);
		a.print();
		b.print();
		c.print();
		d.print();
		Matrix e(a * b);
		e.print();
		d = b * c * d;
		d.print();
		a = e * a * d;
		a.print();
	}
	else if (cmd == "division")
	{
		Matrix a(5, 5);
		Matrix b(a);
		rand_gen(a);
		rand_gen(b);
		a.print();
		b.print();
		a = a / b;
		a.print();
	}
	else if (cmd == "io")
	{
		Matrix a(7, 2);
		Matrix b(3, 4);
		std::string str = "itisamatrix";
		rand_gen(a);
		a.print();
		b.print();
		a.write(str.data());
		b.read(str.data());
		b.print();
	}
	else
		puts("argument error");
}