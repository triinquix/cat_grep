#!/bin/bash
RED=$'\e[0;31m'
White=$'\033[0;37m'

#Script for testing cat

#Tests with a single flag
echo "Tests with a single flag"

#Test 1
echo -e "Test 1\nInput: -b test_files/test.txt${RED}"
diff <(cat -b test_files/test.txt) <(./s21_cat -b test_files/test.txt) -s

#Test 2
echo -e "${White}Test 2\nInput: -e test_files/test2.txt${RED}"
diff <(cat -e  test_files/test2.txt) <(./s21_cat -e  test_files/test2.txt) -s

#Test 3
echo -e "${White}Test 3\nInput: -n test_files/test2.txt${RED}"
diff <(cat -n test_files/test2.txt) <(./s21_cat -n test_files/test2.txt) -s

#Test 4
echo -e "${White}Test 4\nInput: -s  test_files/test2.txt${RED}"
diff <(cat -s  test_files/test2.txt) <(./s21_cat -s  test_files/test2.txt) -s

#Test 5
echo -e "${White}Test 5\nInput: -t  test_files/test2.txt${RED}"
diff <(cat -t  test_files/test2.txt) <(./s21_cat -t  test_files/test2.txt) -s

#Tests with multiple flags
echo "${White}Tests with multiple flags flag"

#Test1
echo -e "${White}Test 1\nInput: -b -s -e test_files/test.txt${RED}"
diff <(cat -b -s -e test_files/test.txt) <(./s21_cat -b -s -e test_files/test.txt) -s

#Tests2
echo -e "${White}Test 2\nInput: -etn test_files/test2.txt${RED}"
diff <(cat -etn test_files/test2.txt) <(./s21_cat -etn test_files/test2.txt) -s

#Tests3
echo -e "${White}Test 3\nInput: -est test_files/test2.txt test_files/test.txt${RED}"
diff <(cat -est test_files/test2.txt test_files/test.txt) <(./s21_cat -est test_files/test2.txt test_files/test.txt) -s

#Tests4
echo -e "${White}Test 4\nInput: -tn test_files/test2.txt${RED}"
diff <(cat -tn test_files/test2.txt) <(./s21_cat -tn test_files/test2.txt) -s

#Tests5
echo -e "${White}Test 5\nInput: -bnset test_files/test2.txt ${RED}"
diff <(cat -bnset test_files/test2.txt) <(./s21_cat -bnset test_files/test2.txt) -s