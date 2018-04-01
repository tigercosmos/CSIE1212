all:
	g++ main.cpp -std=c++11 -O2
run:
	make
	gtime -f "%Us %MkB" ./a.out test_data/short_data.txt < test_data/short.in > tmp.out
	diff test_data/short.out  tmp.out
	gtime -f "%Us %MkB" ./a.out test_data/public_data.txt < test_data/1.in > tmp.out
	diff test_data/1.out  tmp.out
	gtime -f "%Us %MkB" ./a.out test_data/public_data.txt < test_data/2.in > tmp.out
	diff test_data/2.out  tmp.out
	gtime -f "%Us %MkB" ./a.out test_data/public_data.txt < test_data/3.in > tmp.out
	diff test_data/3.out  tmp.out
	gtime -f "%Us %MkB" ./a.out test_data/public_data.txt < test_data/4.in > tmp.out
	diff test_data/4.out  tmp.out
test: 
	make
	gtime -f "%Us %MkB" ./a.out test_data/short_data.txt < test_data/short.in 

test2:
	make
	gtime -f "%Us %MkB" ./a.out test_data/public_data.txt < test_data/short.in > tmp.out

test3:
	g++ test.cpp -std=c++11 -O2
	gtime -f "%Us %MkB" ./a.out