#include "s21_cat.h"

#include <string.h>

void handle_long_flags(struct flag_struct *flags_to_init, char *str_to_map) {
  if (strcmp(str_to_map, "--squeeze-blank") == 0) {
    (*flags_to_init).flag_s = 1;
  } else if (strcmp(str_to_map, "--number-nonblank") == 0) {
    (*flags_to_init).flag_b = 1;
  } else if (strcmp(str_to_map, "--number") == 0) {
    if ((*flags_to_init).flag_b != 1) (*flags_to_init).flag_n = 1;
  }
}

void handle_single_flag(struct flag_struct *flags_to_init, char *str_to_map,
                        int *res) {
  for (int j = 1; j < (int)strlen(str_to_map); j++) {
    if (*res == 0) {
      switch (str_to_map[j]) {
        case 's':
          (*flags_to_init).flag_s = 1;
          break;
        case 'e':
          (*flags_to_init).flag_e = 1;
          if ((*flags_to_init).flag_E == 1) (*flags_to_init).flag_E = 0;
          break;
        case 'E':
          if ((*flags_to_init).flag_e != 1) (*flags_to_init).flag_E = 1;
          break;
        case 't':
          (*flags_to_init).flag_t = 1;
          if ((*flags_to_init).flag_T == 1) (*flags_to_init).flag_T = 0;
          break;
        case 'T':
          if ((*flags_to_init).flag_t != 1) (*flags_to_init).flag_T = 1;
          break;
        case 'b':
          (*flags_to_init).flag_b = 1;
          if ((*flags_to_init).flag_n == 1) (*flags_to_init).flag_n = 0;
          break;
        case 'n':
          if ((*flags_to_init).flag_b != 1) (*flags_to_init).flag_n = 1;
          break;
        default:
          *res = 1;
          printf("cat: invalid option -- '%c'\n", str_to_map[j]);
          printf("Try 'cat --help' for more information.\n");
          break;
      }
    }
  }
}

int init_flags(struct flag_struct *flags_to_init, int arg_num,
               char **arguments) {
  int res = 0;
  if (arg_num > 1) {
    for (int i = 0; i < arg_num; i++) {
      if (res == 0) {
        if (arguments[i][0] == '-') {
          if (arguments[i][1] == '-')
            handle_long_flags(flags_to_init, arguments[i]);
          else
            handle_single_flag(flags_to_init, arguments[i], &res);
        }
      }
    }
  } else
    res = 1;
  return res;
}

void rewrite_file(FILE *file_to_rewrite, FILE *source_file) {
  file_to_rewrite = fopen("tmp.txt", "w");
  source_file = fopen("tmp_tmp.txt", "r");
  char c;
  while ((c = fgetc(source_file)) != EOF) fputc(c, file_to_rewrite);
  fclose(source_file);
  fclose(file_to_rewrite);
  remove("tmp_tmp.txt");
}

FILE *cat(FILE *file_to_read) {
  FILE *tmp_file = fopen("tmp.txt", "w");
  char c;
  while ((c = fgetc(file_to_read)) != EOF) fputc(c, tmp_file);
  fclose(file_to_read);
  fclose(tmp_file);
  return tmp_file;
}

void cat_s(FILE *file_to_read) {
  FILE *tmp_file = fopen("tmp_tmp.txt", "w");
  file_to_read = fopen("tmp.txt", "r");
  char str[4096];
  int count_empty = 0;
  while (fgets(str, sizeof(str), file_to_read) != NULL) {
    if (strcmp(str, "\n") != 0) {
      count_empty = 0;
      fprintf(tmp_file, "%s", str);
    } else {
      if (count_empty == 0) {
        fprintf(tmp_file, "%s", str);
        count_empty++;
      } else
        continue;
    }
  }
  fclose(file_to_read);
  fclose(tmp_file);
  rewrite_file(file_to_read, tmp_file);
}

void cat_e(FILE *file_to_read) {
  FILE *tmp_file = fopen("tmp_tmp.txt", "w");
  file_to_read = fopen("tmp.txt", "r");
  int c;
  while ((c = getc(file_to_read)) != EOF) {
    if (c == '\n')
      fprintf(tmp_file, "$\n");
    else if (c <= 8 || (c >= 11 && c <= 31))
      fprintf(tmp_file, "^%c", c + 64);
    else if (c == 127)
      fprintf(tmp_file, "^?");
    else if ((c >= 32 && c <= 126) || c == 9)
      fputc(c, tmp_file);
    else
      fprintf(tmp_file, "M-%d", c - 128);
  }
  fclose(file_to_read);
  fclose(tmp_file);
  rewrite_file(file_to_read, tmp_file);
}

void cat_E(FILE *file_to_read) {
  FILE *tmp_file = fopen("tmp_tmp.txt", "w");
  file_to_read = fopen("tmp.txt", "r");
  int c;
  while ((c = getc(file_to_read)) != EOF) {
    if (c == '\n')
      fprintf(tmp_file, "$\n");
    else
      fputc(c, tmp_file);
  }
  fclose(file_to_read);
  fclose(tmp_file);
  rewrite_file(file_to_read, tmp_file);
}

void cat_t(FILE *file_to_read) {
  FILE *tmp_file = fopen("tmp_tmp.txt", "w");
  file_to_read = fopen("tmp.txt", "r");
  int c;
  while ((c = getc(file_to_read)) != EOF) {
    if (c == '\t')
      fprintf(tmp_file, "^I");
    else if (c <= 8 || (c >= 11 && c <= 31))
      fprintf(tmp_file, "^%c", c + 64);
    else if (c == 127)
      fprintf(tmp_file, "^?");
    else if ((c >= 32 && c <= 126) || c == 10)
      fputc(c, tmp_file);
    else
      fprintf(tmp_file, "M-%d", c - 128);
  }
  fclose(file_to_read);
  fclose(tmp_file);
  rewrite_file(file_to_read, tmp_file);
}

void cat_T(FILE *file_to_read) {
  FILE *tmp_file = fopen("tmp_tmp.txt", "w");
  file_to_read = fopen("tmp.txt", "r");
  int c;
  while ((c = getc(file_to_read)) != EOF) {
    if (c == '\t')
      fprintf(tmp_file, "^I");
    else
      fputc(c, tmp_file);
  }
  fclose(file_to_read);
  fclose(tmp_file);
  rewrite_file(file_to_read, tmp_file);
}

void cat_b(FILE *file_to_read, int *counter,
           struct flag_struct flags_to_check) {
  FILE *tmp_file = fopen("tmp_tmp.txt", "w");
  file_to_read = fopen("tmp.txt", "r");
  char str[4095];
  while (fgets(str, sizeof(str), file_to_read) != NULL) {
    if (!((flags_to_check.flag_e == 1 || flags_to_check.flag_t == 1) &&
          strcmp(str, "$\n") == 0)) {
      if (strcmp(str, "\n") != 0) {
        fprintf(tmp_file, "%6d\t%s", *counter, str);
        (*counter)++;
      } else
        fputc('\n', tmp_file);
    } else
      fprintf(tmp_file, "$\n");
  }
  fclose(file_to_read);
  fclose(tmp_file);
  rewrite_file(file_to_read, tmp_file);
}

void cat_n(FILE *file_to_read, int *counter) {
  FILE *tmp_file = fopen("tmp_tmp.txt", "w");
  file_to_read = fopen("tmp.txt", "r");
  char str[4095];
  while (fgets(str, sizeof(str), file_to_read) != NULL) {
    fprintf(tmp_file, "%6d\t%s", *counter, str);
    (*counter)++;
  }
  fclose(file_to_read);
  fclose(tmp_file);
  rewrite_file(file_to_read, tmp_file);
}

void process_files(struct flag_struct flags_to_use, int arg_num,
                   char **arguments) {
  int counter = 1;
  for (int i = 1; i < arg_num; i++) {
    if (arguments[i][0] != '-') {
      FILE *init_file;
      if (strchr(arguments[i], '.') != NULL) {
        init_file = fopen(arguments[i], "r");
        if (init_file != NULL) {
          // Проверяем, пустой ли файл
          FILE *temp_file = cat(init_file);
          if (flags_to_use.flag_s == 1) cat_s(temp_file);
          if (flags_to_use.flag_e == 1) cat_e(temp_file);
          if (flags_to_use.flag_E == 1) cat_E(temp_file);
          if (flags_to_use.flag_t == 1) cat_t(temp_file);
          if (flags_to_use.flag_T == 1) cat_T(temp_file);
          if (flags_to_use.flag_b == 1)
            cat_b(temp_file, &counter, flags_to_use);
          if (flags_to_use.flag_n == 1) cat_n(temp_file, &counter);
          temp_file = fopen("tmp.txt", "r");
          char c;
          while ((c = fgetc(temp_file)) != EOF) putchar(c);
          fclose(temp_file);
          remove("tmp.txt");
        }
      } else
        printf("cat: %s: No such file or directory\n", arguments[i]);
    }
  }
}

int main(int argc, char **argv) {
  if (init_flags(&flags, argc, argv) == 0) process_files(flags, argc, argv);
}
