#!/bin/bash
shopt -s nullglob
#TEST_CASE_PATH=(testbench/testcases/*_*.bin)
#GOLDEN_PATH=(testbench/testcases/*_*.gld)


TEST_CASE_PATH=($(env LC_COLLATE=C ls testbench/testcases/*.bin ))
GOLDEN_PATH=($(env LC_COLLATE=C ls testbench/testcases/*.gld ))



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
		

		if [[ $(basename $Curr_test_path) =   *_getc_* ]];
			then echo "$Golden" | awk '{printf("%c",$1)}' | $1 $Curr_test_path
		else
			$1 $Curr_test_path #$1 is the input simulator
		fi


		Output=$?
		if [ "$Output" = "$Golden" ]; 
			then Status="Pass"; 
			printf  "%-5s %-10s \e[32m %-10s \e[0m %-15s %-30s\n" $i, $Instruction, $Status, $Author, $(basename $Curr_test_path)
		else 
			Status="Fail";
			printf  "%-5s %-10s \e[31m %-10s \e[0m %-15s %-30s\n" $i, $Instruction, $Status, $Author, $(basename $Curr_test_path)
		fi
		done

#NUM_TEST_CASES=$(ls -1 testbench/testcases | grep '\.bin$' | wc -l)
