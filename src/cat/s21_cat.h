#include <stdio.h>
struct flag_struct {
  int flag_s;
  int flag_e;
  int flag_E;
  int flag_t;
  int flag_T;
  int flag_b;
  int flag_n;
} flags = {0, 0, 0, 0, 0, 0, 0};

void handle_long_flags(struct flag_struct *flags_to_init, char *str_to_map);
void handle_single_flag(struct flag_struct *flags_to_init, char *str_to_map,
                        int *res);
int init_flags(struct flag_struct *flags_to_init, int arg_num,
               char **arguments);
void rewrite_file(FILE *file_to_rewrite, FILE *source_file);
FILE *cat(FILE *file_to_read);
void cat_s(FILE *file_to_read);
void cat_e(FILE *file_to_read);
void cat_E(FILE *file_to_read);
void cat_t(FILE *file_to_read);
void cat_T(FILE *file_to_read);
void cat_b(FILE *file_to_read, int *counter, struct flag_struct flags_to_check);
void cat_n(FILE *file_to_read, int *counter);
void process_files(struct flag_struct flags_to_use, int arg_num,
                   char **arguments);