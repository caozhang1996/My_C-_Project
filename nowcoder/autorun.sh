#!/bin/bash

cppname=$1
outname=practice".out"
g++ $cppname -o $outname -std=c++11      # 编译标准为c++11
./$outname