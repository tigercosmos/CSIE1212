all:
	g++ main.cpp -std=c++11 -O2

run:
	make
	./a.out

test:
	make
	./a.out < test/1.in > tmp.out
	diff tmp.out test/1.out

test2:
	make
	gtime -f "%Us %MkB" ./a.out < test/2.in > tmp.out
	diff tmp.out test/2.out
	