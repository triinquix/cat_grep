flags=-Wall -Wextra -Werror -std=c11

s21_grep: com_build clean

com_build:
	gcc $(flags) -c s21_grep.c
	gcc $(flags) *.o -o s21_grep
clean:
	rm -rf *.o

.PHONY: s21_grep