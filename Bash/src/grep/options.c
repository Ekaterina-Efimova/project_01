#include "s21_grep.h"
void parser(struct options *opt, char *argv[], int argc,
            char ***array_found_str, int *len_found_str,
            char ***array_found_file, int *len_found_file) {
  int var;
  while ((var = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    if (var == 'e') {
      opt->e = 1;
      (*len_found_str)++;
      *array_found_str =
          *array_found_str == NULL
              ? (char **)malloc(1 * sizeof(char *))
              : (char **)realloc(*array_found_str,
                                 ((*len_found_str) * sizeof(char *)));
      (*array_found_str)[*len_found_str - 1] = malloc(strlen(optarg) + 1);
      strcpy((*array_found_str)[*len_found_str - 1], optarg);
    } else if (var == 'i') {
      opt->i = 1;
    } else if (var == 'v') {
      opt->v = 1;
    } else if (var == 'c') {
      opt->c = 1;
    } else if (var == 'l') {
      opt->l = 1;
    } else if (var == 'n') {
      opt->n = 1;
    } else if (var == 'h') {
      opt->h = 1;
    } else if (var == 's') {
      opt->s = 1;
    } else if (var == 'f') {
      opt->f = 1;
      (*len_found_file)++;
      *array_found_file =
          *array_found_file == NULL
              ? (char **)malloc(1 * sizeof(char *))
              : (char **)realloc(*array_found_file,
                                 ((*len_found_file) * sizeof(char *)));
      (*array_found_file)[*len_found_file - 1] = malloc(strlen(optarg) + 1);
      strcpy((*array_found_file)[*len_found_file - 1], optarg);
    } else if (var == 'o') {
      opt->o = 1;
    } else {
      printf("Неизвестный параметр");
      exit(1);
    }
  }
  if (opt->c == 1 || opt->l == 1) {
    opt->o = 0;
  }
}
int opt_e(const struct options *opt, char *array_found[], int len_found,
          const char *str, int count_files, char *file_name, int count_n,
          char **mega_str) {
  int answer = 0;
  for (int i = 0; i < len_found; i++) {
    if (opt->o == 1) {
      create_mega_string(mega_str, array_found[i]);
    } else if (reg(opt, array_found[i], str, count_files, file_name, count_n) ==
               1) {
      answer = 1;
    }
  }
  return answer;
}

int opt_f(const struct options *opt, char *file_name, int count_files,
          char *array_found[], int len_found, int count_n, char *str,
          char **mega_str) {
  char pat;
  int answer = 0;
  int flag = 0;
  for (int i = 0; i < len_found; i++) {
    pat = ' ';
    FILE *f = fopen(array_found[i], "r");
    while (pat != EOF) {
      char *found_str = NULL;
      create_string(f, &found_str, &pat);
      if (found_str == NULL) {
        break;
      }
      if (opt->o == 1) {
        create_mega_string(mega_str, found_str);
      } else {
        if (reg(opt, found_str, str, count_files, file_name, count_n) == 1 &&
            opt->o != 1) {
          answer = 1;
          flag = 1;
          free(found_str);
          break;
        }
      }
      if (found_str != NULL) {
        free(found_str);
      }
    }
    fclose(f);
    if (flag == 1) {
      break;
    }
  }
  return answer;
}
void opt_o(const struct options *opt, const char *str, regex_t *regex,
           int count_files, char *file_name, int count_n) {
  regmatch_t ovector[1];
  int ret;
  while ((ret = regexec(regex, str, 1, ovector, 0)) == 0) {
    int start = ovector[0].rm_so;
    int end = ovector[0].rm_eo;
    if (count_files > 1 && opt->h != 1) {
      printf("%s:", file_name);
    }
    if (opt->n == 1) {
      printf("%d:", count_n);
    }
    if (opt->l != 1) {
      printf("%.*s\n", end - start, str + start);
    }
    str += end;
  }
}
int reg(const struct options *opt, char *reg_str, const char *str,
        int count_files, char *file_name, int count_n) {
  regex_t regex;
  int options = 0;
  int answer = 0;
  options |= REG_EXTENDED;
  if (opt->i == 1) {
    options |= REG_ICASE;
  }
  int ret = regcomp(&regex, reg_str, options);
  if (ret != 0) {
    return 0;
  } else {
    if (opt->o && opt->v != 1 && opt->c != 1 && opt->l != 1) {
      opt_o(opt, str, &regex, count_files, file_name, count_n);
    } else {
      ret = regexec(&regex, str, 0, NULL, 0);
      if (ret == 0) {
        answer = 1;
      } else {
        answer = 0;
      }
    }
  }
  regfree(&regex);
  return answer;
}