	/*no arguments*/
	
	/*more arguments*/
	file1 "ls -l" "wc -l" file2 "cat" file2
	/*lists files in long format and counts the number of lines.*/
	file1 "ls -l" "wc -l" file2
	/*reads the contents of file1 and searches for a specific pattern.*/
	file1 "cat file1" "grep -w pattern" file2
    /*sorts the lines in file1 and removes duplicate lines.*/
	file1 "sort file1" "uniq" file2
	/*sorts the lines in file1 and removes duplicate lines.*/
	file1 "ls -l" "grep .txt" file2
	/*file1 not exist*/
	file3 "ls -l" "wc -l" file2 
	/*file1 not exist, first command not valid*/
	file3 "lsdf" "wc -l" file2 
	/*file1 not exist, first and second command not valid*/
	file3 "lsdf" "wcsaf" file2 
	/*file1 not exist, first and second command not valid, file2 not exist*/
	file3 "lsdf" "wcsaf" file4 
	/*first command not valid*/
	file1 "lsdf" "wc -l" file2
	/*first and second command not valid*/
	file1 "lsdf" "wcsaf" file2
	/*first and second command not valid, file2 not exist*/
	file1 "lsdf" "wcsaf" file5
	/*file1 and file2 not exist*/
	file3 "ls -l" "wc -l" file6
	/*checks for segmentation fault*/
	file1 "" "" file2
	/*file1 permissions denied: do chmod 777 file1"*/
	file0 "ls -l" "wc -l" file2
	/*2 commands in one process*/
	file1 "cat" "grep -w pattern echo" file2
