#!/bin/bash


#NUM_TEST_CASES=$(ls -1 testbench/testcases | grep '\.bin$' | wc -l)

shopt -s nullglob
TEST_CASE_PATH=(testbench/testcases/*.bin)
GOLDEN_PATH=(testbench/testcases/*.gld)
Instruction=""
Author=""
Golden=""

for ((i=0;i<${#TEST_CASE_PATH[@]};i++))
	do	
		#echo ${GOLDEN_PATH[i]}
		while read Instruction Golden Author;
		do
			true
		done < ${GOLDEN_PATH[i]}
		$1 ${TEST_CASE_PATH[i]}
		Output=$?
		if [ "$Output" = "$Golden" ]; then Status="Pass"; else Status="Fail"; fi
		echo "$i,$Instruction,$Status,$Author"

	done
	#	echo ${TEST_CASE_PATH[i]}
	#	$1 ${TEST_CASE_PATH[i]} #to run case
	#	echo $(($? == 7))
	




