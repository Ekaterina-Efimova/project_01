#include "s21_cat.h"
void output(const struct options *opt, FILE *f) {
  static int cur = 0;
  static int all_str = 1;
  static int str_num = 1;
  static int count = 0;
  static int count_n = 1;

  while (fread(&cur, 1, 1, f) > 0) {
    if (opt->s == 1) {
      if (opt_s(cur, &count_n) == 1) {
        continue;
      }
    }
    if (opt->b == 1) {
      opt_b(cur, &count, &str_num);
    }
    if (opt->n == 1) {
      opt_n(cur, &count, &all_str);
    }
    if (opt->T == 1) {
      opt_T(cur);
      if (cur == '\t') {
        continue;
      }
    }
    if (opt->E == 1) {
      opt_E(cur);
    }

    if (opt->v == 1) {
      opt_v(cur);
      continue;
    }

    printf("%c", cur);
  }
}

int open_file(const struct options *opt, char *argv[], int n) {
  FILE *f;
  if (n == 0 || *argv[n] == '-') {
    f = stdin;
    if (f == NULL) {
      printf("Файл не найден\n");
      return 2;
    }
    output(opt, f);
  } else {
    f = fopen(argv[n], "r");
    if (f == NULL) {
      printf("Файл не найден\n");
      return 2;
    }
    output(opt, f);
  }
  return 1;
}
