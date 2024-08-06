#include "s21_grep.h"
int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "ru_RU.UTF-8");
  struct options opt = {0};
  char **array_found_str = NULL;
  char **array_found_file = NULL;
  int len_found_str = 0;
  int len_found_file = 0;
  parser(&opt, argv, argc, &array_found_str, &len_found_str, &array_found_file,
         &len_found_file);
  int n;
  if (opt.e == 1 || opt.f == 1) {
    n = optind;
  } else {
    n = optind + 1;
  }
  int count_files = argc - n;
  while (n < argc) {
    my_grep(&opt, argv, optind, n, count_files, array_found_str, len_found_str,
            array_found_file, len_found_file);
    n++;
  }
  if (array_found_str != NULL) {
    for (int i = 0; i < len_found_str; i++) {
      free(array_found_str[i]);
    }
    free(array_found_str);
  }
  if (array_found_file != NULL) {
    for (int i = 0; i < len_found_file; i++) {
      free(array_found_file[i]);
    }
    free(array_found_file);
  }
  return 0;
}