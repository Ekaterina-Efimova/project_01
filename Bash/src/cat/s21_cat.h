#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct options {
  int b;
  int n;
  int s;
  int v;
  int T;
  int E;
};

int parser(struct options *opt, char *argv[], int argc);

void opt_b(char cur, int *count, int *str_num);
void opt_n(char cur, int *count, int *all_str);
void opt_T(char cur);
void opt_E(char cur);
void opt_v(int cur);
int opt_s(char cur, int *count);

int open_file(const struct options *opt, char *argv[], int n);
void output(const struct options *opt, FILE *f);

#endif