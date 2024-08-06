#include "s21_cat.h"
int parser(struct options *opt, char *argv[], int argc) {
  int var;
  int opt_index;
  static struct option long_options[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
      {0, 0, 0, 0},
  };
  while ((var = getopt_long(argc, argv, "+benstvTE", long_options,
                            &opt_index)) != -1) {
    if (var == 'b') {
      opt->b = 1;
    } else if (var == 'e') {
      opt->E = 1;
      opt->v = 1;
    } else if (var == 'n') {
      opt->n = 1;
    } else if (var == 's') {
      opt->s = 1;
    } else if (var == 't') {
      opt->T = 1;
      opt->v = 1;
    } else if (var == 'v') {
      opt->v = 1;
    } else if (var == 'T') {
      opt->T = 1;
    } else if (var == 'E') {
      opt->E = 1;
    } else {
      printf("Неизвестный параметр");
      exit(1);
    }
  }
  if (opt->b == 1) {
    opt->n = 0;
  }
  return 0;
}
void opt_b(char cur, int *count, int *str_num) {
  if (cur != '\n') {
    if (*count == 0) {
      printf("%6d\t", *str_num);
      (*str_num)++;
      *count = 1;
    }
  } else {
    *count = 0;
  }
}
void opt_n(char cur, int *count, int *all_str) {
  if (*count == 0) {
    printf("%6d\t", *all_str);
    (*all_str)++;
    *count = 1;
  }
  if (cur == '\n') {
    *count = 0;
  }
}
void opt_T(char cur) {
  if (cur == '\t') {
    printf("^I");
  }
}
void opt_E(char cur) {
  if (cur == '\n') {
    printf("$");
  }
}
void opt_v(int cur) {
  if (cur == '\n' || cur == '\t' || (cur >= 32 && cur <= 126)) {
    printf("%c", cur);
  } else if (cur < 32) {
    printf("^%c", cur + 64);
  } else if (cur == 127) {
    printf("^?");
  } else if (cur < 160) {
    printf("M-^%c", cur + 192);
  } else if (cur <= 255) {
    if (cur == 255) {
      printf("M-^?");
    } else {
      printf("M-%c", cur + 128);
    }
  }
}
int opt_s(char cur, int *count_n) {
  if (cur != '\n') {
    *count_n = 0;
  }
  if (cur == '\n' && *count_n > 1) {
    return 1;
  } else if (cur == '\n' && *count_n < 2) {
    (*count_n)++;
  }
  return 0;
}
