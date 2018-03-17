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
	if (cmd == "inverse")
	{
		Matrix a(4, 4);
		rand_gen(a);
		printf("== a ==\n");
		a.print();
		a = a.inverse();
		printf("== a.inverse() ==\n");
		a.print();

		Matrix b(3, 3);
		rand_gen(b);
		printf("== b ==\n");
		b.print();
		b = b.inverse();
		printf("== b.inverse() ==\n");
		b.print();
	}
	else if (cmd == "construct")
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
		rand_gen(a);
		Matrix b(a);
		printf("== a ==\n");
		a.print();
		printf("== b ==\n");
		b.print();
	}
	else if (cmd == "unary")
	{
		Matrix a(3, 7);
		Matrix b(a);
		rand_gen(a);
		b = -a;
		printf("== a ==\n");
		a.print();
		printf("== -a ==\n");
		b.print();
	}
	else if (cmd == "add")
	{
		Matrix a(11, 6);
		rand_gen(a);
		Matrix b(a);
		Matrix c(a);
		c = a + b;
		printf("== a ==\n");
		a.print();
		printf("== b ==\n");
		b.print();
		printf("== a + b ==\n");
		c.print();
	}
	else if (cmd == "subtract")
	{
		Matrix a(11, 6);
		rand_gen(a);
		Matrix b(a);
		rand_gen(b);
		Matrix c(a);
		c = a - b;
		a.print();
		b.print();
		printf("== a - b ==\n");
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
		c = a * b;
		d = b * a;
		c.print();
		d.print();
	}
	else if (cmd == "division")
	{
		Matrix a(5, 5);
		rand_gen(a);
		Matrix b(a);
		b = a / a;
		b.print();
	}
	else if (cmd == "io")
	{
		Matrix a(7, 2);
		Matrix b(3, 4);
		std::string str = "itisamatrix.output";
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