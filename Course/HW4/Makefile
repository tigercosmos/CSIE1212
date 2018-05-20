all:
	g++ main.cpp -std=c++11 -O2

run:
	make
	./a.out < ./test/1.in

test1:
	make
	./a.out < ./test/1.in > tmp.out
	diff tmp.out ./test/1.out

test2:
	make
	gtime -f "%Us %MkB" ./a.out < ./test/2.in > tmp.out
	diff tmp.out ./test/2.out

test3:
	make
	gtime -f "%Us %MkB" ./a.out < ./test/3.in > tmp.out
	diff tmp.out ./test/3.out

test4:
	make
	gtime -f "%Us %MkB" ./a.out < ./test/4.in > tmp.out
	diff tmp.out ./test/4.out
	