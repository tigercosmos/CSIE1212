#!/bin/sh
ROOT=$PWD
for i in Leetcode/* ; do
  if [ -d "$i" ]; then
    echo "Testing make $i ...."
    cd "$i" && make
    cd $ROOT
  fi
done
for i in Course/* ; do
  if [ -d "$i" ]; then
    echo "Testing make $i ...."
    cd "$i" && make
    cd $ROOT
  fi
done