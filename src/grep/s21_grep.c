#include "s21_grep.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_position(struct patterns_array *pattern_storage, int position) {
  if ((*pattern_storage).number_of_source_files == 0) {
    (*pattern_storage).number_of_source_files = 1;
    (*pattern_storage).positions_of_source_files = (int *)malloc(sizeof(int));
    (*pattern_storage).positions_of_source_files[0] = position;
  } else {
    (*pattern_storage).number_of_source_files++;
    (*pattern_storage).positions_of_source_files =
        (int *)realloc(pattern_storage->positions_of_source_files,
                       (*pattern_storage).number_of_source_files * sizeof(int));
    (*pattern_storage)
        .positions_of_source_files[(*pattern_storage).number_of_source_files -
                                   1] = position;
  }
}

int check_position(struct patterns_array pattern_storage, int position) {
  int is_pattern_file = 0;
  for (int i = 0;
       i < (int)pattern_storage.number_of_source_files && is_pattern_file != 1;
       i++)
    if (position == pattern_storage.positions_of_source_files[i])
      is_pattern_file = 1;
  return is_pattern_file;
}

void add_pattern(struct patterns_array *pattern_storage, char *pattern_to_add) {
  if ((*pattern_storage).current_size == 0) {
    (*pattern_storage).current_size = 1;
    (*pattern_storage).my_patterns = (char **)malloc(sizeof(char *));
    (*pattern_storage).my_patterns[0] =
        (char *)malloc(sizeof(char) * strlen(pattern_to_add) + 1);
    strcpy((*pattern_storage).my_patterns[0], pattern_to_add);
  } else {
    (*pattern_storage).current_size++;
    (*pattern_storage).my_patterns =
        (char **)realloc(pattern_storage->my_patterns,
                         (*pattern_storage).current_size * sizeof(char *));
    (*pattern_storage).my_patterns[(*pattern_storage).current_size - 1] =
        (char *)malloc(sizeof(char) * strlen(pattern_to_add) + 1);
    strcpy((*pattern_storage).my_patterns[(*pattern_storage).current_size - 1],
           pattern_to_add);
  }
}

int check_pattern(struct patterns_array pattern_storage,
                  char *pattern_to_search) {
  // Если 0, не паттерн. Если 1, то паттерн
  int is_pattern = 0;
  for (int i = 0; i < (int)pattern_storage.current_size && is_pattern != 1;
       i++) {
    if (strcmp(pattern_storage.my_patterns[i], pattern_to_search) == 0)
      is_pattern = 1;
  }
  return is_pattern;
}

int init_flags(struct search_flags *searchers, struct output_flags *outputters,
               struct pattern_flags *patterns, int arg_num, char **arguments) {
  int res = 0;
  if (arg_num > 2) {
    for (int i = 0; i < arg_num; i++) {
      if (res == 0) {
        if (arguments[i][0] == '-') {
          for (int j = 1; j < (int)strlen(arguments[i]); j++) {
            switch (arguments[i][j]) {
              case 'i':
                (*searchers).flag_i = 1;
                break;
              case 'v':
                (*searchers).flag_v = 1;
                break;
              case 'h':
                (*outputters).flag_h = 1;
                break;
              case 's':
                (*outputters).flag_s = 1;
                break;
              case 'l':
                (*outputters).flag_l = 1;
                (*outputters).flag_n = 0;
                (*outputters).flag_o = 0;
                break;
              case 'c':
                (*outputters).flag_c = 1;
                (*outputters).flag_n = 0;
                (*outputters).flag_o = 0;
                break;
              case 'n':
                if ((*outputters).flag_l != 1 && (*outputters).flag_c != 1)
                  (*outputters).flag_n = 1;
                break;
              case 'o':
                if ((*outputters).flag_l != 1 && (*outputters).flag_c != 1)
                  (*outputters).flag_o = 1;
                break;
              case 'e':
                (*patterns).flag_e = 1;
                break;
              case 'f':
                (*patterns).flag_f = 1;
                break;
              default:
                res = 1;
                printf("grep: invalid option -- %c\n", arguments[i][j]);
                printf(
                    "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B "
                    "num] [-C[num]]\n\t");
                printf(
                    "[-e pattern] [-f file] [--binary-files=value] "
                    "[--color=when]\n\t");
                printf("[--null] [pattern] [file ...]\n");
                break;
            }
          }
        }
      }
    }
  } else
    res = 1;
  return res;
}

int find_regexs(struct patterns_array *pat_array, int arg_num, char **arguments,
                struct pattern_flags patterns) {
  int res = 0;
  if (patterns.flag_e == 1 || patterns.flag_f == 1) {
    for (int i = 1; i < arg_num; i++) {
      if (res == 0) {
        if (arguments[i][0] == '-') {
          for (int j = 1; j < (int)strlen(arguments[i]); j++) {
            if (arguments[i][j] == 'e') {
              if (j == (int)strlen(arguments[i]) - 1) {
                if (arguments[i + 1] != NULL)
                  add_pattern(pat_array, arguments[i + 1]);
                else {
                  res = 1;
                  printf("grep: option requires an argument -- e\n");
                  printf(
                      "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] "
                      "[-B "
                      "num] [-C[num]]\n\t");
                  printf(
                      "[-e pattern] [-f file] [--binary-files=value] "
                      "[--color=when]\n\t");
                  printf("[--null] [pattern] [file ...]\n");
                }
              } else {
                char tmp[1];
                tmp[0] = arguments[i][j + 1];
                add_pattern(pat_array, tmp);
              }
            }
            if (arguments[i][j] == 'f') {
              if (j == (int)strlen(arguments[i]) - 1) {
                if (arguments[i + 1] != NULL) {
                  FILE *source_file = fopen(arguments[i + 1], "r");
                  // Сохраняем строки в массив паттернов
                  if (source_file != NULL) {
                    char line[4095];
                    add_position(pat_array, i + 1);
                    while (fgets(line, sizeof(line), source_file))
                      add_pattern(pat_array, line);
                  } else {
                    res = 1;
                    printf("grep: %s: No such file or directory\n",
                           arguments[i + 1]);
                  }
                  fclose(source_file);
                } else {
                  res = 1;
                  printf("grep: option requires an argument -- f\n");
                  printf(
                      "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] "
                      "[-B "
                      "num] [-C[num]]\n\t");
                  printf(
                      "[-e pattern] [-f file] [--binary-files=value] "
                      "[--color=when]\n\t");
                  printf("[--null] [pattern] [file ...]\n");
                }
              } else {
                res = 1;
                printf("grep: %c: No such file or directory\n",
                       arguments[i][j + 1]);
              }
            }
          }
        }
      }
    }
  } else {
    int is_pattern = 0;
    for (int i = 1; i < arg_num && is_pattern != 1; i++) {
      if (arguments[i][0] != '-') {
        add_pattern(pat_array, arguments[i]);
        is_pattern = 1;
      }
    }
  }
  return res;
}

void grep(struct search_flags searchers, struct output_flags outputters,
          char *file_name, struct patterns_array array_with_patterns) {
  FILE *where_to_search = fopen(file_name, "r");
  if (where_to_search != NULL) {
    char line[4095];
    int line_counter = 1;
    int to_stop = 0;
    // Для флага с
    int matches_counter = 0;
    int pattern_counter = 0;
    int value;
    // Итерация по строкам файла
    while (fgets(line, sizeof(line), where_to_search) != NULL && to_stop != 1) {
      // Итерация по всем найденным паттернам
      pattern_counter = 0;
      for (int i = 0; i < (int)array_with_patterns.current_size && to_stop != 1;
           i++) {
        regmatch_t regmatch;
        regex_t regex;
        if (searchers.flag_i == 0)
          value = regcomp(&regex, array_with_patterns.my_patterns[i], 0);
        else
          value =
              regcomp(&regex, array_with_patterns.my_patterns[i], REG_ICASE);
        value = regexec(&regex, line, 1, &regmatch, 0);
        // Если только l
        if (outputters.flag_l == 1) {
          if ((searchers.flag_v == 0 && value == 0) ||
              (searchers.flag_v == 1 && value == REG_NOMATCH)) {
            to_stop = 1;
            printf("%s\n", file_name);
          }
        }
        // Если только с
        else if (outputters.flag_c == 1 && outputters.flag_l == 0) {
          if ((searchers.flag_v == 0 && value == 0) ||
              (searchers.flag_v == 1 && value == REG_NOMATCH))
            matches_counter++;
        }
        // Оставшиеся случаи
        else {
          if (((value == 0 && searchers.flag_v == 0) ||
               (value == REG_NOMATCH && searchers_flags.flag_v == 1)) &&
              pattern_counter == 0 &&
              !(searchers.flag_v == 1 && outputters.flag_o == 1)) {
            if (outputters.flag_h == 0) printf("%s:", file_name);
            if (outputters.flag_n == 1) printf("%d:", line_counter);
            if (outputters.flag_o == 0) {
              if (strchr(line, '\n') != NULL)
                printf("%s", line);
              else
                printf("%s\n", line);
            } else
              printf("%s\n", array_with_patterns.my_patterns[i]);
            pattern_counter = 1;
            // Если -о
            if (outputters.flag_o == 1) {
              int offset = regmatch.rm_eo;
              char *sub_string = line + offset;
              int sub_value = 0;
              while (sub_string != NULL && sub_value == 0) {
                sub_value = regexec(&regex, sub_string, 1, &regmatch, 0);
                if (sub_value == 0) {
                  if (outputters.flag_h == 0) printf("%s:", file_name);
                  if (outputters.flag_n == 1) printf("%d:", line_counter);
                  printf("%s\n", array_with_patterns.my_patterns[i]);
                  offset = regmatch.rm_eo;
                  sub_string += offset;
                }
              }
            }
          }
        }
        regfree(&regex);
      }
      line_counter++;
    }
    if (outputters.flag_c == 1 && outputters.flag_l == 0) {
      if (outputters.flag_h == 0) printf("%s:", file_name);
      printf("%d\n", matches_counter);
    }
    fclose(where_to_search);
  } else if (outputters.flag_s == 0)
    printf("grep: %s: No such file or directory\n", file_name);
}

// Попробовать переделать через массив
void process_files(int arg_num, char **arguments,
                   struct output_flags outputters,
                   struct search_flags searchers,
                   struct patterns_array array_with_patterns) {
  int files_counter = 0;
  for (int i = 1; i < arg_num; i++) {
    if (arguments[i][0] != '-' &&
        check_pattern(array_with_patterns, arguments[i]) == 0 &&
        check_position(array_with_patterns, i) == 0)
      files_counter++;
  }
  if (files_counter == 1) outputters.flag_h = 1;
  for (int i = 1; i < arg_num; i++) {
    if (arguments[i][0] != '-' &&
        check_pattern(array_with_patterns, arguments[i]) == 0 &&
        check_position(array_with_patterns, i) == 0)
      grep(searchers, outputters, arguments[i], array_with_patterns);
  }
}

int main(int argc, char **argv) {
  if (init_flags(&searchers_flags, &outputters_flags, &patterns_flags, argc,
                 argv) == 0) {
    if (find_regexs(&my_patterns, argc, argv, patterns_flags) == 0) {
      process_files(argc, argv, outputters_flags, searchers_flags, my_patterns);
    }
  }
  if (my_patterns.current_size > 0) {
    for (int i = 0; i < (int)my_patterns.current_size; i++)
      free(my_patterns.my_patterns[i]);
    free(my_patterns.my_patterns);
  }
  if (my_patterns.number_of_source_files > 0)
    free(my_patterns.positions_of_source_files);
}
