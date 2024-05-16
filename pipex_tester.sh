#!/bin/bash

echo "Hello"

rm output_file_mine output_file_bash input_file_nopermis input_file diff_file
 
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
touch output_file_mine output_file_bash

#execute the app
#no arguments
echo -e "${RED}Test 1:${NC}"
./pipex

#more arguments
echo -e "${RED}Test 2:${NC}" 
./pipex input_file "ls -l" "wc -l" "cat" output_file_mine

#lists files in long format and counts the number of lines
echo -e "${RED}Test 3:${NC}"
./pipex input_file "ls -l" "wc -l" output_file_mine
< input_file ls -l | wc -l > output_file_bash
diff output_file_mine output_file_bash >> diff_file
check_diff output_file_mine output_file_bash

#sorts the lines in input_file and removes duplicate lines.
echo -e "${RED}Test 4:${NC}"
./pipex  /var/log/bootstrap.log "sort" "uniq" output_file_mine
< /var/log/bootstrap.log sort | uniq > output_file_bash
diff output_file_mine output_file_bash >> diff_file
check_diff output_file_mine output_file_bash

#reads the contents of input_file and searches for a specific pattern
echo -e "${RED}Test 5:${NC}"
./pipex  /var/log/bootstrap.log "cat" "grep -w warning" output_file_mine
< /var/log/bootstrap.log cat | grep -w warning > output_file_bash
diff output_file_mine output_file_bash >> diff_file
check_diff output_file_mine output_file_bash

#input_file not exist
echo -e "${RED}Test 6:${NC}"
./pipex	no_input_file "ls -l" "wc -l" output_file_mine
< no_input_file ls -l | wc -l > output_file_bash
diff output_file_mine output_file_bash >> diff_file
check_diff output_file_mine output_file_bash

#cmd1 not valid
echo -e "${RED}Test 7:${NC}"
./pipex input_file "lsdf" "wc -l" output_file_mine
< input_file lsdf | wc -l > output_file_bash
diff output_file_mine output_file_bash >> diff_file
check_diff output_file_mine output_file_bash

#input_file not exist, cmd1 not valid
echo -e "${RED}Test 8:${NC}"
./pipex no_input_file "lsdf" "wc -l" output_file_mine
< no_input_file lsdf | wc -l > output_file_bash
diff output_file_mine output_file_bash >> diff_file
check_diff output_file_mine output_file_bash

#cmd1 and cmd2 not valid
echo -e "${RED}Test 9:${NC}"
./pipex input_file "lsdf" "wcsaf" output_file_mine
< input_file lsdf | wcsaf > output_file_bash
diff output_file_mine output_file_bash >> diff_file
check_diff output_file_mine output_file_bash

#input_file not exist, cmd1 and cmd2 not valid
echo -e "${RED}Test 10:${NC}"
./pipex	no_input_file "lsdf" "wcsaf" output_file_mine
< no_input_file lsdf | wcsaf output_file_bash
diff output_file_mine output_file_bash >> diff_file
check_diff output_file_mine output_file_bash

#input_file and output_file_mine not exist, cmd1 and cmd2 not valid
echo -e "${RED}Test 11:${NC}"
./pipex	input_file_2 "lsdf" "wcsaf" output_file_mine_2
< input_file lsdf | wcsaf > output_file_bash_2
diff output_file_mine_2 output_file_bash_2 >> diff_file
check_diff output_file_mine_2 output_file_bash_2

#empty strings
echo -e "${RED}Test 12:${NC}"
./pipex input_file "" "" output_file_mine
< input_file "" | "" > output_file_bash
diff output_file_mine output_file_bash >> diff_file
check_diff output_file_mine output_file_bash

#input_file permissions denied: do chmod 0 input_file_4"
touch input_file_nopermis
chmod 0 input_file_nopermis
./pipex input_file_nopermis "ls -l" "wc -l" output_file_mine
< input_file_nopermis ls -l | wc -l > output_file_bash
diff output_file_mine output_file_bash >> diff_file
check_diff output_file_mine output_file_bash

#/dev/stdin
#/dev/stdout
#/dev/random
#/dev/null

#valgrind tests

echo -e "${RED}Test 1:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex
echo -e "${RED}Test 2:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex input_file "ls -l" "wc -l" "cat" output_file_mine
echo -e "${RED}Test 3:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex input_file "ls -l" "wc -l" output_file_mine
echo -e "${RED}Test 4:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex  /var/log/bootstrap.log "sort" "uniq" output_file_mine
echo -e "${RED}Test 5:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex  /var/log/bootstrap.log "cat" "grep -w warning" output_file_mine
echo -e "${RED}Test 6:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex	no_input_file "ls -l" "wc -l" output_file_mine
echo -e "${RED}Test 7:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex input_file "lsdf" "wc -l" output_file_mine
echo -e "${RED}Test 8:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex no_input_file "lsdf" "wc -l" output_file_mine
echo -e "${RED}Test 9:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex input_file "lsdf" "wcsaf" output_file_mine
echo -e "${RED}Test 10:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex	no_input_file "lsdf" "wcsaf" output_file_mine
echo -e "${RED}Test 11:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex input_file "" "" output_file_mine
echo -e "${RED}Test 12:${NC}" 
valgrind -s --show-leak-kinds=all --error-exitcode=5 --exit-on-first-error=no --leak-check=full ./pipex input_file_nopermis "ls -l" "wc -l" output_file_mine

exit 0

-fsanitize=address



