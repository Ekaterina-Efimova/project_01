#ifndef S21_GREP_H
#define S21_GREP_H
#include <ctype.h>
#include <getopt.h>
#include <locale.h>
#include <malloc.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
struct options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
};

void parser(struct options *opt, char *argv[], int argc, char ***array_found,
            int *len_found, char ***array_found_file, int *len_found_file);
int opt_f(const struct options *opt, char *file_name, int count_files,
          char *array_found[], int len_found, int count_n, char *str,
          char **mega_str);
int opt_e(const struct options *opt, char *array_found[], int len_found,
          const char *str, int count_files, char *file_name, int count_n,
          char **mega_str);
void opt_o(const struct options *opt, const char *str, regex_t *regex,
           int count_files, char *file_name, int count_n);
int reg(const struct options *opt, char *reg_str, const char *str,
        int count_files, char *file_name, int count_n);
int open_file(char *argv[], int n, const struct options *opt, char *found_str,
              int count_files);
void output(const struct options *opt, FILE *f, char *found_str,
            char *file_name, int count_files);
void output_c(const struct options *opt, const char *file_name, int count_c,
              int count_files);
void output_l(const struct options *opt, const char *file_name);
void create_string(FILE *f, char **str, char *cur);
void create_mega_string(char **mega_str, char *found_str);
void my_grep(const struct options *opt, char *argv[], int optind, int n,
             int count_files, char *array_found[], int len_found,
             char *array_found_file[], int len_found_file);
void print(const struct options *opt, const char *str, const char *file_name,
           int count_files, int count_n);
#endif