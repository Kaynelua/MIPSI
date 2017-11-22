#!/bin/bash
for f in $1/*.s
 do 
 	fname=$(basename "$f" .s)
 	make "$1/$fname.mips.bin" -B
 done