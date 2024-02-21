#include <stddef.h>

struct search_flags {
  int flag_i;
  int flag_v;
} searchers_flags = {0, 0};

struct output_flags {
  int flag_h;
  int flag_s;
  int flag_l;
  int flag_c;
  int flag_n;
  int flag_o;
} outputters_flags = {0, 0, 0, 0, 0, 0};

struct pattern_flags {
  int flag_e;
  int flag_f;
} patterns_flags = {0, 0};

struct patterns_array {
  size_t current_size;
  char **my_patterns;
  size_t number_of_source_files;
  int *positions_of_source_files;
} my_patterns = {0, NULL, 0, NULL};

void add_position(struct patterns_array *pattern_storage, int position);
int check_position(struct patterns_array pattern_storage, int position);
void add_pattern(struct patterns_array *pattern_storage, char *pattern_to_add);
int check_pattern(struct patterns_array pattern_storage,
                  char *pattern_to_search);
int init_flags(struct search_flags *searchers, struct output_flags *outputters,
               struct pattern_flags *patterns, int arg_num, char **arguments);
int find_regexs(struct patterns_array *pat_array, int arg_num, char **arguments,
                struct pattern_flags patterns);
void grep(struct search_flags searchers, struct output_flags outputters,
          char *file_name, struct patterns_array array_with_patterns);
void process_files(int arg_num, char **arguments,
                   struct output_flags outputters,
                   struct search_flags searchers,
                   struct patterns_array array_with_patterns);
