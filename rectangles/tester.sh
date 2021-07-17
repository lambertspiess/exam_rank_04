#! /bin/bash
gcc -Wall -Wextra -fsanitize=address,undefined main.c -o our;
gcc -Wall -Wextra -fsanitize=address,undefined ref.c -o ref;
OURRET=0
REFRET=0

RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
PURP='\033[0;35m'
NC='\033[0m' # No Color

for FILE in {0..8};
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
	DIFF=$(diff reflog$FILE.txt ourlog$FILE.txt)
	diff reflog$FILE.txt ourlog$FILE.txt > difflog$FILE.txt
	if [[ $DIFF -ne "" ]];
	then
		echo -e "${RED}KO :${NC}";
		echo -e "reflog$FILE.txt :${PURP}";
		cat -e reflog$FILE.txt;
		echo -e "${NC}========== VS ==========";
		echo -e "ourlog$FILE.txt :${CYAN}";
		cat -e ourlog$FILE.txt;
		echo -e "${NC}~~~~~~~~~~ DIFF ~~~~~~~~~~";
		echo $DIFF;
	else
		echo -e "${GREEN}OK : no diff";
	fi

done
