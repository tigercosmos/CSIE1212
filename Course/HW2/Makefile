all:
	g++ main.cpp -std=c++11 -O2
run:
	make
	./a.out test_data/short_data.txt < test_data/short.in > tmp.out
	diff test_data/short.out  tmp.out
	./a.out test_data/public_data.txt < test_data/1.in > tmp.out
	diff test_data/1.out  tmp.out
	./a.out test_data/public_data.txt < test_data/2.in > tmp.out
	diff test_data/2.out  tmp.out
	./a.out test_data/public_data.txt < test_data/3.in > tmp.out
	diff test_data/3.out  tmp.out
	./a.out test_data/public_data.txt < test_data/4.in > tmp.out
	diff test_data/4.out  tmp.out
test: 
	make
	./a.out test_data/short_data.txt < test_data/short.in > tmp.out
	diff test_data/short.out  tmp.out