#!/bin/bash

make
if [ ! -e output ]
then
	mkdir output
fi

./a.out construct > output/construct.output
./a.out index > output/index.output
./a.out assign > output/assign.output
./a.out unary > output/unary.output
./a.out add > output/add.output
./a.out subtract > output/subtract.output
./a.out mult > output/mult.output
./a.out division > output/division.output
./a.out io > output/io.output

diff outputStd/construct.output output/construct.output
diff outputStd/index.output output/index.output
diff outputStd/assign.output output/assign.output
diff outputStd/unary.output output/unary.output
diff outputStd/add.output output/add.output
diff outputStd/subtract.output output/subtract.output
diff outputStd/mult.output output/mult.output
diff outputStd/division.output output/division.output
diff outputStd/io.output output/io.output