#include "s21_grep.h"

void my_grep(const struct options *opt, char *argv[], int optind, int n,
             int count_files, char *array_found_str[], int len_found_str,
             char *array_found_file[], int len_found_file) {
  if (opt->v && opt->o) return;
  FILE *f = fopen(argv[n], "r");
  if (f == NULL) {
    if (opt->s != 1) {
      printf("Файл не найден\n");
    }
    return;
  }
  char cur = ' ';
  int count_n = 0;
  int count_c = 0;
  while (cur != EOF) {
    char *mega_str = NULL;
    char *str = NULL;
    create_string(f, &str, &cur);
    if (str == NULL) {
      break;
    }
    if (opt->n == 1) {
      count_n++;
    }
    int answer_e = 0;
    int answer_f = 0;
    int answer_another = 0;
    if (opt->e == 1) {
      answer_e = opt_e(opt, array_found_str, len_found_str, str, count_files,
                       argv[n], count_n, &mega_str);
    }
    if (opt->f == 1) {
      answer_f = opt_f(opt, argv[n], count_files, array_found_file,
                       len_found_file, count_n, str, &mega_str);
    }
    if (opt->e != 1 && opt->f != 1) {
      if (opt->o) {
        create_mega_string(&mega_str, argv[optind]);
      } else {
        answer_another =
            reg(opt, argv[optind], str, count_files, argv[n], count_n);
      }
    }
    if (opt->o == 1) {
      reg(opt, mega_str, str, count_files, argv[n], count_n);
    }
    if (opt->l == 1) {
      if ((opt->v != 1 && ((opt->e && answer_e > 0) ||
                           (opt->e != 1 && opt->f != 1 && answer_another > 0) ||
                           (opt->f && answer_f > 0))) ||
          (opt->v == 1 &&
           ((opt->e && answer_e == 0) ||
            (opt->e != 1 && opt->f != 1 && answer_another == 0) ||
            (opt->f && answer_f == 0)))) {
        output_l(opt, argv[n]);
        free(str);
        break;
      }
    }
    if ((opt->c == 1 && opt->v != 1 &&
         ((opt->e && answer_e > 0) ||
          (opt->e != 1 && opt->f != 1 && answer_another > 0) ||
          (opt->f && answer_f > 0))) ||
        (opt->c == 1 && opt->v == 1 && answer_e == 0 && answer_another == 0 &&
         answer_f == 0)) {
      count_c++;
    }
    if (opt->v == 1 && opt->c != 1 && opt->l != 1 && answer_e == 0 &&
        answer_another == 0 && answer_f == 0) {
      print(opt, str, argv[n], count_files, count_n);
    } else if (opt->v != 1 && opt->c != 1 && opt->l != 1 &&
               ((opt->e && answer_e > 0) ||
                (opt->e != 1 && opt->f != 1 && answer_another > 0) ||
                (opt->f && answer_f > 0))) {
      print(opt, str, argv[n], count_files, count_n);
    }
    if (mega_str != NULL) {
      free(mega_str);
    }
    free(str);
  }
  if (opt->l != 1) {
    output_c(opt, argv[n], count_c, count_files);
  }
  fclose(f);
}
void create_mega_string(char **mega_str, char *found_str) {
  if (found_str[0] != '\0') {
    if (*mega_str == NULL) {
      *mega_str = (char *)malloc((int)strlen(found_str) + 3 * sizeof(char));
      sprintf(*mega_str, "(%s)", found_str);
    } else {
      int len = (int)strlen(*mega_str);
      *mega_str = (char *)realloc(
          *mega_str, (int)strlen(found_str) + len + 5 * sizeof(char));
      sprintf(*mega_str + len, "|(%s)", found_str);
    }
  }
}
void create_string(FILE *f, char **str, char *cur) {
  int i = 0;
  while ((*cur = fgetc(f)) != EOF) {
    (*str) = (*str == NULL) ? (char *)malloc(sizeof(char))
                            : (char *)realloc(*str, sizeof(char) * (i + 1));
    if (*str == NULL) {
      free(str);
      printf("Ошибка выделения памяти\n");
      return;
    }
    (*str)[i] = *cur;
    i++;
    if (*cur == '\n' || *cur == EOF) break;
  }
  if (*str != NULL) {
    if ((*str)[i - 1] == '\n' || (*str)[i - 1] == EOF) {
      (*str)[i - 1] = '\0';
    } else {
      *str = (char *)realloc(*str, sizeof(char) * (i + 1));
      (*str)[i] = '\0';
    }
  }
}
void print(const struct options *opt, const char *str, const char *file_name,
           int count_files, int count_n) {
  if (count_files > 1 && opt->h != 1 && opt->o != 1) {
    printf("%s:", file_name);
  }
  if (opt->n == 1 && opt->o != 1) {
    printf("%d:", count_n);
  }
  if (opt->o != 1) {
    printf("%s\n", str);
  }
}
void output_c(const struct options *opt, const char *file_name, int count_c,
              int count_files) {
  if (opt->c == 1) {
    if (count_files > 1 && opt->h != 1) {
      printf("%s:", file_name);
      printf("%d\n", count_c);
    } else {
      if (count_files > 1 && opt->h == 1) {
        printf("%d\n", count_c);
      } else if (count_c > 0) {
        printf("%d\n", count_c);
      }
    }
  }
}
void output_l(const struct options *opt, const char *file_name) {
  if (opt->l == 1) {
    printf("%s\n", file_name);
  }
}