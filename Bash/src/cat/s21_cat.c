#include "s21_cat.h"

int main(int argc, char *argv[]) {
  struct options opt = {0};
  if (argc == 1) {
    open_file(&opt, argv, 0);
  }
  parser(&opt, argv, argc);
  int n = optind;
  if (argc - n == 0) {
    open_file(&opt, argv, 0);
  }
  while (n < argc) {
    open_file(&opt, argv, n);
    n++;
  }
  return 0;
}