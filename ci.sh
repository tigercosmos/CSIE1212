#!/bin/sh
ROOT=$PWD
for i in Leetcode/* ; do
  if [ -d "$i" ]; then
    echo "Testing make $i ...."
    cd "$i" && make
    cd $ROOT
  fi
done
cd Course/HW1
echo "Testing make HW1 ...."
make
cd "$ROOT/Course/HW2"
echo "Testing make HW2 ...."
time -f "%Us %MkB" make test
cd "$ROOT/Course/HW3"
echo "Testing make HW3 ...."
make test1