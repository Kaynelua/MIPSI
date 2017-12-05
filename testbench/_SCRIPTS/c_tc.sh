#!/bin/bash
#Run this in terminal
#+ Command to compile c++ program.

TESTCASE_GEN_CPP=($(ls testbench/testcase_generator/*/*.cpp))

if [ "$1" = "ALL" ]; 
	then
	rm -f testbench/testcases/*
	for f in testbench/testcase_generator/*/*.cpp
	do
		d=${f%/*}
		instr_name=$(basename $d)

		g++ $f -o $d/gen 
		
		mkdir -p testbench/"$instr_name"_tc
		rm -f testbench/"$instr_name"_tc/*
		
		./$d/gen
		./testbench/_SCRIPTS/s_to_bin testbench/"$instr_name"_tc
	done
	for f in testbench/_c_code/_confirmed/*.c
	do
		c_code_filename=$(basename $f)
		fn_no_ext=$(echo $c_code_filename | cut -f 1 -d '.')
		echo "$fn_no_ext"
		make testbench/_c_code/_confirmed/"$fn_no_ext".mips.bin -B
		cp testbench/_c_code/_confirmed/"$fn_no_ext".mips.bin testbench/testcases
		cp testbench/_c_code/_confirmed/"$fn_no_ext".mips.gld testbench/testcases
		rm -f testbench/_c_code/_confirmed/"$fn_no_ext".mips.bin
	done

elif [ "$1" = "C" ]; 
	then
	rm -f testbench/testcases/C_*
	for f in testbench/_c_code/_confirmed/*.c
	do
		c_code_filename=$(basename $f)
		fn_no_ext=$(echo $c_code_filename | cut -f 1 -d '.')
		echo "$fn_no_ext"
		make testbench/_c_code/_confirmed/"$fn_no_ext".mips.bin -B
		cp testbench/_c_code/_confirmed/"$fn_no_ext".mips.bin testbench/testcases
		cp testbench/_c_code/_confirmed/"$fn_no_ext".mips.gld testbench/testcases
		rm -f testbench/_c_code/_confirmed/"$fn_no_ext".mips.bin
	done
else
	if [ -z "$1" ]
		then
		echo "Error : No input"
	
	else
		instr_name=$1
		rm testbench/testcases/"$instr_name"_*
		g++ testbench/testcase_generator/"$instr_name"/*.cpp -o testbench/testcase_generator/"$instr_name"/gen
		#need to exit if error
		mkdir -p testbench/"$instr_name"_tc
		rm testbench/"$instr_name"_tc/*
		./testbench/testcase_generator/"$instr_name"/gen
		./testbench/_SCRIPTS/s_to_bin  testbench/"$instr_name"_tc
	fi
fi





exit 0