#!/bin/bash

# 1. Build the compiler.
#
# You *MUST* provide a build.sh script in the root directory
# to build your compiler. If you do not produce a binary
# (i.e. something like python), then the build.sh script
# will be empty.

echo "*****************************"
echo "  Building compiler"
echo "*****************************"

make

# 2. Run script checking
#
# You *MUST* provide a run.sh script in the root directory
# to run your compiler. The run.sh script must take a single
# argument, the filename, and pass the contents to your compiler.

if [ ! -f run.sh ]
then
	echo "ERROR: Missing run.sh script"
	exit
fi

# 2. Run all valid programs
#
# For valid programs, your compiler *MUST*
#   (a) output only: VALID
#   (b) exit with status code 0
# A log of the output is written to valid.log

VALID_DIR=./programs/valid/*.min

echo
echo "*****************************"
echo "  Valid programs"
echo "*****************************"

if [ -f valid.log ]
then
	rm valid.log
fi

VALID=0
VALID_CORRECT=0
for PROG in $VALID_DIR
do
	((VALID++))

	echo -n "$PROG: " | tee -a valid.log
	./run.sh $PROG 2>&1 | tee -a valid.log | tr -d '\n'
	if [ ${PIPESTATUS[0]} -eq 0 ]
	then
		echo -e -n " \033[0;32m[pass]"
		((VALID_CORRECT++))
	else
		echo -e -n " \033[0;31m[fail]"
	fi
	echo -e "\033[0m"
done
echo
echo ">>>>> # valid programs handled: ${VALID_CORRECT}/${VALID}"

# 3. Run all invalid programs
#
# For invalid programs, your compiler *MUST*
#   (a) output: INVALID: <error>
#   (b) exit with status code 1
# A log of the output is written to invalid.log

INVALID_DIR=./programs/invalid/*.min

echo
echo "*****************************"
echo "  Invalid programs"
echo "*****************************"

if [ -f invalid.log ]
then
	rm invalid.log
fi

INVALID=0
INVALID_CORRECT=0
for PROG in $INVALID_DIR
do
	((INVALID++))

	echo -n "$PROG: " | tee -a invalid.log
	./run.sh $PROG 2>&1 | tee -a invalid.log | tr -d '\n'
	if [ ${PIPESTATUS[0]} -eq 1 ]
	then
		echo -e -n " \033[0;32m[pass]"
		((INVALID_CORRECT++))
	else
		echo -e -n " \033[0;31m[fail]"
	fi
	echo -e "\033[0m"
done
echo
echo ">>>>> # invalid programs handled: ${INVALID_CORRECT}/${INVALID}"

# 4. Run all invalid type programs
#
# For invalid programs, your compiler *MUST*
#   (a) output: INVALID: <error>
#   (b) exit with status code 1
# A log of the output is written to invalidtype.log

INVALID_TYPE_DIR=./programs/invalidtype/*.min

echo
echo "*****************************"
echo "  Invalid Typecheck programs"
echo "*****************************"

if [ -f invalidtype.log ]
then
	rm invalidtype.log
fi

INVALID_TYPE=0
INVALID_TYPE_CORRECT=0
for PROG in $INVALID_TYPE_DIR
do
	((INVALID_TYPE++))

	echo -n "$PROG: " | tee -a invalidtype.log
	./run.sh $PROG 2>&1 | tee -a invalidtype.log | tr -d '\n'
	if [ ${PIPESTATUS[0]} -eq 1 ]
	then
		echo -e -n " \033[0;32m[pass]"
		((INVALID_TYPE_CORRECT++))
	else
		echo -e -n " \033[0;31m[fail]"
	fi
	echo -e "\033[0m"
done
echo
echo ">>>>> # invalid programs handled: ${INVALID_TYPE_CORRECT}/${INVALID_TYPE}"

TOTAL=$(($VALID+$INVALID+$INVALID_TYPE))
TOTAL_CORRECT=$(($VALID_CORRECT+$INVALID_CORRECT+$INVALID_TYPE_CORRECT))
echo
echo -e "\033[1;33mtotal tests handled: ${TOTAL_CORRECT}/${TOTAL}\033[0m"

if [[ $# = 1 && $1 = "-c" || $1 = "--clean" ]]
then
	make clean -C ./src > /dev/null
fi
