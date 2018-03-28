#!/bin/bash

make
if [ ! -e output ]
then
	mkdir output
fi
./a.out inverse 
./a.out inverse > output/inverse.output
./a.out construct > output/construct.output
./a.out index > output/index.output
./a.out assign > output/assign.output
./a.out unary > output/unary.output
./a.out add > output/add.output
./a.out subtract > output/subtract.output
./a.out mult > output/mult.output
./a.out division > output/division.output
./a.out io > output/io.output
