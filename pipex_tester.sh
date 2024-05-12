#!/bin/bash

echo "Hello"

rm file_out_mine file_out_bash file_in_nopermis file_in diff_file
 
make clean > /dev/null 2>&1
make

# ANSI escape codes for colors
RED='\033[0;31m'
NC='\033[0m' # No Color

#function to compare output of program and bash
check_diff() {
    diff "$1" "$2" > diff_file
    if [ -s "diff_file" ]; then
        echo "File is not empty. Failed"
        cat "diff_file"
    else
        echo "File is empty. Success"
    fi
}

#create two files for output
touch file_out_mine file_out_bash

#execute the app
#no arguments
echo -e "${RED}Test 1:${NC}"
./pipex

#more arguments
echo -e "${RED}Test 2:${NC}" 
./pipex file_in "ls -l" "wc -l" "cat" file_out_mine

#lists files in long format and counts the number of lines
echo -e "${RED}Test 3:${NC}"
./pipex file_in "ls -l" "wc -l" file_out_mine
< file_in ls -l | wc -l > file_out_bash
diff file_out_mine file_out_bash >> diff_file
check_diff file_out_mine file_out_bash

#sorts the lines in file_in and removes duplicate lines.
echo -e "${RED}Test 4:${NC}"
./pipex  /var/log/bootstrap.log "sort" "uniq" file_out_mine
< /var/log/bootstrap.log sort | uniq > file_out_bash
diff file_out_mine file_out_bash >> diff_file
check_diff file_out_mine file_out_bash

#reads the contents of file_in and searches for a specific pattern
echo -e "${RED}Test 5:${NC}"
./pipex  /var/log/bootstrap.log "cat" "grep -w warning" file_out_mine
< /var/log/bootstrap.log cat | grep -w warning > file_out_bash
diff file_out_mine file_out_bash >> diff_file
check_diff file_out_mine file_out_bash

#file_in not exist
echo -e "${RED}Test 6:${NC}"
./pipex	no_file_in "ls -l" "wc -l" file_out_mine
< no_file_in ls -l | wc -l > file_out_bash
diff file_out_mine file_out_bash >> diff_file
check_diff file_out_mine file_out_bash

#cmd1 not valid
echo -e "${RED}Test 7:${NC}"
./pipex file_in "lsdf" "wc -l" file_out_mine
< file_in lsdf | wc -l > file_out_bash
diff file_out_mine file_out_bash >> diff_file
check_diff file_out_mine file_out_bash

#file_in not exist, cmd1 not valid
echo -e "${RED}Test 8:${NC}"
./pipex no_file_in "lsdf" "wc -l" file_out_mine
< no_file_in lsdf | wc -l > file_out_bash
diff file_out_mine file_out_bash >> diff_file
check_diff file_out_mine file_out_bash

#cmd1 and cmd2 not valid
echo -e "${RED}Test 9:${NC}"
./pipex file_in "lsdf" "wcsaf" file_out_mine
< file_in lsdf | wcsaf > file_out_bash
diff file_out_mine file_out_bash >> diff_file
check_diff file_out_mine file_out_bash

#file_in not exist, cmd1 and cmd2 not valid
echo -e "${RED}Test 10:${NC}"
./pipex	no_file_in "lsdf" "wcsaf" file_out_mine
< no_file_in lsdf | wcsaf file_out_bash
diff file_out_mine file_out_bash >> diff_file
check_diff file_out_mine file_out_bash

#file_in and file_out_mine not exist, cmd1 and cmd2 not valid
echo -e "${RED}Test 11:${NC}"
./pipex	file_in_2 "lsdf" "wcsaf" file_out_mine_2
< file_in lsdf | wcsaf > file_out_bash_2
diff file_out_mine_2 file_out_bash_2 >> diff_file
check_diff file_out_mine_2 file_out_bash_2

#empty strings
echo -e "${RED}Test 12:${NC}"
./pipex file_in "" "" file_out_mine
< file_in "" | "" > file_out_bash
diff file_out_mine file_out_bash >> diff_file
check_diff file_out_mine file_out_bash

#file_in permissions denied: do chmod 777 file_in_4"
touch file_in_nopermis
chmod 777 file_in_nopermis
./pipex file_in_nopermis "ls -l" "wc -l" file_out_mine
< file_in_nopermis ls -l | wc -l > file_out_bash
diff file_out_mine file_out_bash >> diff_file
check_diff file_out_mine file_out_bash

#valgrind tests

echo -e "${RED}Test 1:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex
echo -e "${RED}Test 2:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex file_in "ls -l" "wc -l" "cat" file_out_mine
echo -e "${RED}Test 3:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex file_in "ls -l" "wc -l" file_out_mine
echo -e "${RED}Test 4:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex  /var/log/bootstrap.log "sort" "uniq" file_out_mine
echo -e "${RED}Test 5:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex  /var/log/bootstrap.log "cat" "grep -w warning" file_out_mine
echo -e "${RED}Test 6:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex	no_file_in "ls -l" "wc -l" file_out_mine
echo -e "${RED}Test 7:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex file_in "lsdf" "wc -l" file_out_mine
echo -e "${RED}Test 8:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex no_file_in "lsdf" "wc -l" file_out_mine
echo -e "${RED}Test 9:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex file_in "lsdf" "wcsaf" file_out_mine
echo -e "${RED}Test 10:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex	no_file_in "lsdf" "wcsaf" file_out_mine
echo -e "${RED}Test 11:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex file_in "" "" file_out_mine
echo -e "${RED}Test 12:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex file_in_nopermis "ls -l" "wc -l" file_out_mine

exit 0