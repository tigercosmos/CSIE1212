all:
	g++ main.cpp -std=c++11 -O2

run:
	make
	./a.out

test:
	make
	./a.out < test.in > tmp.out
	diff tmp.out test.out