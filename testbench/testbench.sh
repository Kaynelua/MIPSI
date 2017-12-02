#!/bin/bash
shopt -s nullglob
#TEST_CASE_PATH=(testbench/testcases/*.bin)
#GOLDEN_PATH=(testbench/testcases/*.gld)

TEST_CASE_PATH=($(ls -t testbench/testcases/*.bin ))
GOLDEN_PATH=($(ls -t testbench/testcases/*.gld ))

#echo ${TEST_CASE_PATH[@]}
#echo ${GOLDEN_PATH[@]}


for ((i=0;i<${#TEST_CASE_PATH[@]};i++))
	do	
		Curr_test_path=${TEST_CASE_PATH[i]}
		Curr_golden_path=${GOLDEN_PATH[i]}
		while read Instruction Golden Author;
		do
			true
		done < $Curr_golden_path
		$1 $Curr_test_path
		Output=$?
		if [ "$Output" = "$Golden" ]; then Status="\e[32m Pass\e[0m"; else Status="\e[31m Fail\e[0m"; fi
		echo -e "$i,\t $Instruction,\t $Status,\t $Author,\t $(basename $Curr_test_path)"
	done

#NUM_TEST_CASES=$(ls -1 testbench/testcases | grep '\.bin$' | wc -l)
