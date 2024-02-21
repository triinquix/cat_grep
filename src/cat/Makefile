flags=-Wall -Wextra -Werror -std=c11 -g

s21_cat: com_build clean

com_build:
	gcc $(flags) -c s21_cat.c
	gcc $(flags) *.o -o s21_cat
clean:
	rm -rf *.o

.PHONY: s21_cat