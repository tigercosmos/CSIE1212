all:
	clang++ main.cpp -std=c++11 -O2

run1:
	make
	./a.out < ./test/1.in

run2:
	make
	./a.out < ./test/2.in

run3:
	make
	./a.out < ./test/3.in

test1:
	make
	./a.out < ./test/1.in > tmp.out
	diff tmp.out ./test/1.out

test2:
	make
	time -f "%Us %MkB" ./a.out < ./test/2.in > tmp.out
	diff tmp.out ./test/2.out

test3:
	make
	time -f "%Us %MkB" ./a.out < ./test/3.in > tmp.out
	diff tmp.out ./test/3.out
	