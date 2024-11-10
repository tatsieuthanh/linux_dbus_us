#!/bin/bash

#make clean
#make

# export the library path
export LD_LIBRARY_PATH=../lib:$LD_LIBRARY_PATH

# execute the program
cd ../out && chmod +x ./main && ./main