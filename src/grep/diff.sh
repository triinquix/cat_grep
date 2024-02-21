#!/bin/bash
RED=$'\e[0;31m'
White=$'\033[0;37m'
#Script for testing grep

#Tests with single flag
echo "Tests with a single flag"

#Test1
echo -e "${White}Test 1\nInput: -e pi -e ro -e ds test_files/test.txt test_files/test4.txt${RED}"
diff <(grep  -e pi -e ro -e ds test_files/test.txt test_files/test4.txt) <(./s21_grep  -e pi -e ro -e ds test_files/test.txt test_files/test4.txt) -s

#Test2
echo -e "${White}Test 2\nInput: -i ro test_files/test.txt test_files/test4.txt${RED}"
diff <(grep -i ro test_files/test.txt test_files/test4.txt) <(./s21_grep -i ro test_files/test.txt test_files/test4.txt) -s

#Test3
echo -e "${White}Test 3\nInput: -v pi test_files/test.txt test_files/test4.txt${RED}"
diff <(grep -v pi test_files/test.txt test_files/test4.txt) <(./s21_grep -v pi test_files/test.txt test_files/test4.txt) -s

#Test4
echo -e "${White}Test 4\nInput: -c rob test_files/test.txt test_files/test4.txt${RED}"
diff <(grep -c rob test_files/test.txt test_files/test4.txt) <(./s21_grep -c rob test_files/test.txt test_files/test4.txt) -s

#Test5
echo -e "${White}Test 5\nInput: -l pir test_files/test.txt test_files/test4.txt${RED}"
diff <(grep -l pir test_files/test.txt test_files/test4.txt) <(./s21_grep -l pir test_files/test.txt test_files/test4.txt) -s

#Test6
echo -e "${White}Test 6\nInput: -n bot test_files/test.txt test_files/test4.txt${RED}"
diff <(grep -n bot test_files/test.txt test_files/test4.txt) <(./s21_grep -n bot test_files/test.txt test_files/test4.txt) -s

#Test7
echo -e "${White}Test 7\nInput: -h bot test_files/test.txt test_files/test4.txt${RED}"
diff <(grep -h bot test_files/test.txt test_files/test4.txt) <(./s21_grep -h bot test_files/test.txt test_files/test4.txt) -s

#Test8
echo -e "${White}Test 8\nInput: -s pir test_files/test.txt test_files/test4.txt no_file.txt${RED}"
diff <(grep -s pir test_files/test.txt test_files/test4.txt no_file.txt) <(./s21_grep -s pir test_files/test.txt test_files/test4.txt no_file.txt) -s

#Test9
echo -e "${White}Test 9\nInput: -f test_files/patterns.txt test_files/test.txt test_files/test4.txt${RED}"
diff <(grep -f test_files/patterns.txt test_files/test.txt test_files/test4.txt) <(./s21_grep -f test_files/patterns.txt test_files/test.txt test_files/test4.txt) -s

#Test10
echo -e "${White}Test 10\nInput: -o rob test_files/test.txt test_files/test4.txt${RED}"
diff <(grep -o rob test_files/test.txt test_files/test4.txt) <(./s21_grep -o rob test_files/test.txt test_files/test4.txt) -s

#Tests with multiple flags
echo "${White}Tests with multiple flags"


#Test1
echo -e "Test 1\nInput: -e pi -e robot -i test_files/test.txt${RED}"
diff <(grep -e pi -e robot -i test_files/test.txt) <(./s21_grep -e pi -e robot -i test_files/test.txt) -s

#Test2
echo -e "${White}Test 2\nInput: -e pi -e robot -n test_files/test.txt -f test_files/patterns.txt${RED}"
diff <(grep -e pi -e robot -n test_files/test.txt -f test_files/patterns.txt) <(./s21_grep -e pi -e robot -n test_files/test.txt -f test_files/patterns.txt) -s

#Test3
echo -e "${White}Test 3\nInput: -n pi test_files/test.txt test_files/test4.txt -h${RED}"
diff <(grep -n pi test_files/test.txt test_files/test4.txt -h) <(./s21_grep -n pi test_files/test.txt test_files/test4.txt -h) -s

#Test4
echo -e "${White}Test 4\nInput: -cv robot test_files/test.txt test_files/test4.txt -i${RED}"
diff <(grep -cv robot test_files/test.txt test_files/test4.txt -i) <(./s21_grep -cv robot test_files/test.txt test_files/test4.txt -i) -s

#Test5
echo -e "${White}Test 5\nInput: -cl robot test_files/test.txt -v test_files/test4.txt -i${RED}"
diff <(grep -cl robot test_files/test.txt -v test_files/test4.txt -i) <(./s21_grep -cl robot test_files/test.txt -v test_files/test4.txt -i) -s

#Test6
echo -e "${White}Test 6\nInput: -ivn pi test_files/test.txt -hs test_files/test4.txt no_file.txt${RED}"
diff <(grep -ivn pi test_files/test.txt -hs test_files/test4.txt no_file.txt) <(./s21_grep -ivn pi test_files/test.txt -hs test_files/test4.txt no_file.txt) -s

#Test7
echo -e "${White}Test 7\nInput: -n robo test_files/test.txt -oh test_files/test4.txt no_file.txt -s${RED}"
diff <(grep -n robo test_files/test.txt -oh test_files/test4.txt no_file.txt -s) <(./s21_grep -n robo test_files/test.txt -oh test_files/test4.txt no_file.txt -s) -s

#Test8
echo -e "${White}Test 8\nInput: -nf test_files/patterns.txt -i test_files/test.txt -s test_files/test4.txt no_file.txt${RED}"
diff <(grep -nf test_files/patterns.txt -i test_files/test.txt -s test_files/test4.txt no_file.txt) <(./s21_grep -nf test_files/patterns.txt -i test_files/test.txt -s test_files/test4.txt no_file.txt) -s

#Test9
echo -e "${White}Test 9\nInput: -e robo -e pir -in test_files/test.txt -s test_files/test4.txt no_file.txt${RED}"
diff <(grep -e robo -e pir -ni test_files/test.txt -s test_files/test4.txt no_file.txt) <(./s21_grep -e robo -e pir -ni test_files/test.txt -s test_files/test4.txt no_file.txt) -s

#Test10
echo -e "${White}Test 10\nInput: -h robo test_files/test.txt -cl test_files/test4.txt${RED}"
diff <(grep -h robo test_files/test.txt -cl test_files/test4.txt) <(./s21_grep -h robo test_files/test.txt -cl test_files/test4.txt) -s
