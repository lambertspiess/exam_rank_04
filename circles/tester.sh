#! /bin/bash
rm -f *log*.txt
gcc -Wall -Wextra -fsanitize=address,undefined main.c -o our;
gcc -Wall -Wextra -fsanitize=address,undefined ref.c -o ref;
OURRET=0
REFRET=0

RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
PURP='\033[0;35m'
NC='\033[0m' # No Color

for FILE in {1..2};
do
	echo -e "${NC}------------------------------------------------------------------";
	echo -e "Test file examples/$FILE :";
	./ref examples/$FILE > "reflog$FILE.txt";
	REFRET=$?
	./our examples/$FILE > "ourlog$FILE.txt";
	OURRET=$?
	echo "For test $FILE :";
	if [ ${REFRET} -ne ${OURRET} ];
	then
		echo -e "${RED}KO : refret = $REFRET VS ourret = $OURRET${NC}";
	else
		echo -e "${GREEN}OK :refret = $REFRET VS ourret = $OURRET${NC}";
	fi
	diff reflog$FILE.txt ourlog$FILE.txt > difflog$FILE.txt
	if [[ $? -ne 0 ]];
	then
		echo -e "${RED}KO : difflog$FILE.txt${NC}";
	else
		echo -e "${GREEN}OK : no diff";
	fi

done
