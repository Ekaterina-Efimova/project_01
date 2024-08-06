#include "interface.h"

#include <unistd.h>

WINDOW *init_ncurses() {
  WINDOW *brick_game_window = newwin(42, 70, 0, 0);
  if (brick_game_window) {
    PRINT();
    wattrset(brick_game_window, COLOR_PAIR(DEFAULT));
  }
  return brick_game_window;
}

void print_display(WINDOW *brick_game_window) {
  print_backgarund(brick_game_window);
  print_box(brick_game_window);

  wattrset(brick_game_window, COLOR_PAIR(UNACTIVE));
  for (int i = 1; i < 41; ++i)
    for (int j = 2; j < 41; ++j) print_square(brick_game_window, i, j);

  for (int i = 18; i < 26; ++i)
    for (int j = 51; j < 66; ++j) print_active_next(brick_game_window, i, j);

  reset_info(brick_game_window, 1);
  print_helpers(brick_game_window);

  for (int i = 29; i < 36; ++i) {
    int j = i - 29;
    mvwprintw(brick_game_window, i, 47, "%s", bg_objects(F_SCREEN, j));
  }

  wrefresh(brick_game_window);
}

void print_backgarund(WINDOW *brick_game_window) {
  wattrset(brick_game_window, COLOR_PAIR(UNACTIVE));
  for (int i = 0; i < 42; ++i)
    for (int j = 0; j < 70; ++j) mvwprintw(brick_game_window, i, j, " ");
}

void print_square(WINDOW *brick_game_window, int i, int j) {
  wattrset(brick_game_window, COLOR_PAIR(UNACTIVE));
  const char *ch = !((j + 1) % 4)   ? bg_objects(LINE, ELEM1)  // "═"
                   : !((j + 2) % 4) ? i & 1
                                          ? bg_objects(LINE, ELEM2)
                                          : bg_objects(LINE, ELEM3)  //"╔" : "╚"
                   : !(j % 4)       ? i & 1 ? bg_objects(LINE, ELEM4)
                                            : bg_objects(LINE, ELEM5)  //"╗" : "╝"
                                    : bg_objects(LINE, ELEM9);               //""

  mvwprintw(brick_game_window, i, j, "%s", ch);
}

void print_active_next(WINDOW *brick_game_window, int i, int j) {
  wattrset(brick_game_window, COLOR_PAIR(UNACTIVE));
  const char *ch =
      !(j % 4)         ? bg_objects(LINE, ELEM1)  // "═"
      : !((j + 1) % 4) ? i & 1 ? bg_objects(LINE, ELEM3)
                               : bg_objects(LINE, ELEM2)  //"╔" : "╚"
      : !((j - 1) % 4) ? i & 1 ? bg_objects(LINE, ELEM5)
                               : bg_objects(LINE, ELEM4)  //"╗" : "╝"
                       : bg_objects(LINE, ELEM6);
  mvwprintw(brick_game_window, i, j, "%s", ch);
}

void print_box(WINDOW *brick_game_window) {
  wattrset(brick_game_window, COLOR_PAIR(UNACTIVE));
  for (int i = 0; i < 70; ++i) {
    const char *ch1 = (!i        ? bg_objects(LINE, ELEM2)
                       : i == 42 ? bg_objects(LINE, ELEM10)
                       : i == 69 ? bg_objects(LINE, ELEM4)
                                 : bg_objects(LINE, ELEM1));
    mvwprintw(brick_game_window, 0, i, "%s", ch1);

    const char *ch2 = !i        ? bg_objects(LINE, ELEM3)
                      : i == 42 ? bg_objects(LINE, ELEM8)
                      : i == 69 ? bg_objects(LINE, ELEM5)
                                : bg_objects(LINE, ELEM1);
    mvwprintw(brick_game_window, 41, i, "%s", ch2);
  }

  for (int i = 1; i < 41; ++i) {
    mvwprintw(brick_game_window, i, 0, "%s", bg_objects(LINE, ELEM7));
    mvwprintw(brick_game_window, i, 42, "%s", bg_objects(LINE, ELEM7));
    mvwprintw(brick_game_window, i, 69, "%s", bg_objects(LINE, ELEM7));
  }
}

void print_helpers(WINDOW *brick_game_window) {
  wattrset(brick_game_window, COLOR_PAIR(WORDS));
  for (int i = 3; i <= 15; i += 3) {
    int j = (i == 3    ? HIGHSCORE
             : i == 6  ? SCORE
             : i == 9  ? LEVEL
             : i == 12 ? SPEED
                       //  : i == 15 ? SPEED_UP
                       : NEXT);
    mvwprintw(brick_game_window, i, 44, "%s", bg_objects(INFO, j));
  }

  mvwprintw(brick_game_window, 3, 63, "%s", bg_objects(HELPERS, HELP1));
  mvwprintw(brick_game_window, 6, 63, "%s", bg_objects(HELPERS, HELP1));
  mvwprintw(brick_game_window, 9, 62, "%s", bg_objects(HELPERS, HELP1));
  mvwprintw(brick_game_window, 12, 62, "%s", bg_objects(HELPERS, HELP1));
}

void update_display(WINDOW *brick_game_window, GameInfo_t *game_info) {
  reset_info(brick_game_window, game_info->pause);
  printf_info(brick_game_window, game_info);
  print_field(brick_game_window, game_info->field);
  wrefresh(brick_game_window);
}

void reset_info(WINDOW *brick_game_window, int pause) {
  wattrset(brick_game_window, COLOR_PAIR(UNACTIVE));
  mvwprintw(brick_game_window, 3, 60, "%s", bg_objects(HELPERS, HELP3));
  mvwprintw(brick_game_window, 6, 62, "%s", bg_objects(HELPERS, HELP4));
  mvwprintw(brick_game_window, 9, 62, "%s", bg_objects(HELPERS, HELP4));
  mvwprintw(brick_game_window, 12, 62, "%s", bg_objects(HELPERS, HELP4));

  for (int i = 18; i < 26; ++i)
    for (int j = 51; j < 66; ++j) print_active_next(brick_game_window, i, j);

  print_pause(brick_game_window, pause);

  wattrset(brick_game_window, COLOR_PAIR(WORDS));
}

void print_pause(WINDOW *brick_game_window, int pause) {
  wattrset(brick_game_window, COLOR_PAIR(WORDS));

  if (pause) {
    mvwprintw(brick_game_window, 37, 46, "%s", bg_objects(COMBS, PAUSE1));
    mvwprintw(brick_game_window, 38, 46, "%s", bg_objects(COMBS, PAUSE2));
    mvwprintw(brick_game_window, 39, 46, "%s", bg_objects(COMBS, PAUSE3));

  } else {
    mvwprintw(brick_game_window, 37, 46, "%s", bg_objects(COMBS, NOPAUSE1));
    mvwprintw(brick_game_window, 38, 46, "%s", bg_objects(COMBS, NOPAUSE1));
    mvwprintw(brick_game_window, 39, 46, "%s", bg_objects(COMBS, NOPAUSE1));
  }

  wattrset(brick_game_window, COLOR_PAIR(UNACTIVE));
}

void printf_info(WINDOW *brick_game_window, GameInfo_t *game_info) {
  print_score(brick_game_window, game_info->score, game_info->highscore);
  print_level(brick_game_window, game_info->level);
  print_speed(brick_game_window, game_info->speed);

  for (int i = 0; i < NEXT_HEIGHT; i++) {
    for (int j = 0; j < NEXT_WIDTH; j++)
      if (game_info->next[i][j]) print_next(brick_game_window, i, j);

    print_pause(brick_game_window, game_info->pause);
  }
}

void print_score(WINDOW *brick_game_window, int score, int highscore) {
  int left = highscore / 1000  ? 60
             : highscore / 100 ? 61
             : highscore / 10  ? 62
                               : 63;
  mvwprintw(brick_game_window, 3, left, "%d", highscore);

  left = score / 1000 ? 60 : score / 100 ? 61 : score / 10 ? 62 : 63;
  mvwprintw(brick_game_window, 6, left, "%d", score);
}

void print_level(WINDOW *brick_game_window, int level) {
  int left = level / 10 ? 62 : 63;
  mvwprintw(brick_game_window, 9, left, "%d", level);
}

void print_speed(WINDOW *brick_game_window, int speed) {
  int left = speed / 10 ? 62 : 63;
  mvwprintw(brick_game_window, 12, left, "%d", speed);
}

void print_next(WINDOW *brick_game_window, int i, int j) {
  wattrset(brick_game_window, COLOR_PAIR(DEFAULT));
  mvwprintw(brick_game_window, i * 2 + 18, j * 4 + 51, "%s",
            bg_objects(COMBS, SQUARE1));
  mvwprintw(brick_game_window, i * 2 + 19, j * 4 + 51, "%s",
            bg_objects(COMBS, SQUARE2));
  wattrset(brick_game_window, COLOR_PAIR(UNACTIVE));
}

void print_field(WINDOW *brick_game_window, int **field) {
  for (int i = 0; i < F_HEIGHT; i++) {
    for (int j = 0; j < F_WIDTH; j++) {
      int right = i * 2 + 1;
      int left = j * 4 + 2;
      if (field[i][j]) wattrset(brick_game_window, COLOR_PAIR(DEFAULT));
      mvwprintw(brick_game_window, right, left, "%s",
                bg_objects(COMBS, SQUARE1));
      mvwprintw(brick_game_window, right + 1, left, "%s",
                bg_objects(COMBS, SQUARE2));
      wattrset(brick_game_window, COLOR_PAIR(UNACTIVE));
    }
  }
}

void print_result(WINDOW *brick_game_window, GameInfo_t *game_info) {
  for (int i = 16; i < 28; ++i)
    for (int j = 12; j < 31; ++j) print_final_frame(brick_game_window, i, j);

  print_final_info(brick_game_window, game_info);

  wrefresh(brick_game_window);
}

void print_final_frame(WINDOW *brick_game_window, int i, int j) {
  const char *ch = (i == 16 || i == 24   ? j == 12   ? bg_objects(LINE, ELEM2)
                                           : j == 30 ? bg_objects(LINE, ELEM4)
                                                     : bg_objects(LINE, ELEM1)
                      : i == 23 || i == 27 ? j == 12   ? bg_objects(LINE, ELEM3)
                                             : j == 30 ? bg_objects(LINE, ELEM5)
                                                       : bg_objects(LINE, ELEM1)
                      : j == 12 || j == 30 ? bg_objects(LINE, ELEM7)
                                         : bg_objects(LINE, ELEM9));

  mvwprintw(brick_game_window, i, j, "%s", ch);
}

void print_final_info(WINDOW *brick_game_window, GameInfo_t *game_info) {
  if (game_info->score == game_info->highscore)
    print_win(brick_game_window);
  else
    print_lose(brick_game_window);

  mvwprintw(brick_game_window, 25, 14, "%s", bg_objects(INFO, YOUR_SCORE));
  mvwprintw(brick_game_window, 25, 25, "%4d", game_info->score);
  mvwprintw(brick_game_window, 26, 14, "%s", bg_objects(INFO, HIGHSCORE));
  mvwprintw(brick_game_window, 26, 25, "%4d", game_info->highscore);
}

void print_lose(WINDOW *brick_game_window) {
  wattrset(brick_game_window, COLOR_PAIR(DEFAULT));

  for (int i = 0; i < 14; i++)
    mvwprintw(brick_game_window, i, 39, "%s", bg_objects(YOU_LOSE, i));

  for (int i = 14; i < 28; i++)
    mvwprintw(brick_game_window, i, 39, "%s", bg_objects(YOU_LOSE, i - 14));

  for (int i = 28; i < 42; i++)
    mvwprintw(brick_game_window, i, 39, "%s", bg_objects(YOU_LOSE, i - 28));

  mvwprintw(brick_game_window, 17, 16, "%s", bg_objects(COMBS, YOU1));
  mvwprintw(brick_game_window, 18, 16, "%s", bg_objects(COMBS, YOU2));
  mvwprintw(brick_game_window, 19, 16, "%s", bg_objects(COMBS, YOU3));
  mvwprintw(brick_game_window, 20, 14, "%s", bg_objects(COMBS, YOU_LOSE1));
  mvwprintw(brick_game_window, 21, 14, "%s", bg_objects(COMBS, YOU_LOSE2));
  mvwprintw(brick_game_window, 22, 14, "%s", bg_objects(COMBS, YOU_LOSE3));
}

void print_win(WINDOW *brick_game_window) {
  wattrset(brick_game_window, COLOR_PAIR(WORDS));

  for (int i = 0; i < 14; i++)
    mvwprintw(brick_game_window, i, 44, "%s", bg_objects(YOU_WIN, i));

  for (int i = 14; i < 28; i++)
    mvwprintw(brick_game_window, i, 44, "%s", bg_objects(YOU_WIN, i - 14));

  for (int i = 28; i < 42; i++)
    mvwprintw(brick_game_window, i, 44, "%s", bg_objects(YOU_WIN, i - 28));

  mvwprintw(brick_game_window, 17, 16, "%s", bg_objects(COMBS, YOU1));
  mvwprintw(brick_game_window, 18, 16, "%s", bg_objects(COMBS, YOU2));
  mvwprintw(brick_game_window, 19, 16, "%s", bg_objects(COMBS, YOU3));
  mvwprintw(brick_game_window, 20, 15, "%s", bg_objects(COMBS, YOU_WIN1));
  mvwprintw(brick_game_window, 21, 15, "%s", bg_objects(COMBS, YOU_WIN2));
  mvwprintw(brick_game_window, 22, 15, "%s", bg_objects(COMBS, YOU_WIN3));
}

void user_input(WINDOW *brick_game_window, int *user_action, int *tetris) {
  int c = wgetch(brick_game_window);

  if (c == 's' || c == 'S') {
    *user_action = Start;
    *tetris = 0;
  } else if (c == 'p' || c == 'P') {
    *user_action = Pause;
    *tetris = 1;
  } else if (c == 'q' || c == 'Q') {
    *user_action = Terminate;
    *tetris = 8;
  } else if (c == KEY_LEFT) {
    *user_action = Left;
    *tetris = 4;
  } else if (c == KEY_RIGHT) {
    *user_action = Right;
    *tetris = 4;
  } else if (c == KEY_UP) {
    *user_action = Up;
    *tetris = 4;
  } else if (c == KEY_DOWN) {
    *user_action = Down;
    *tetris = 4;
  } else if (c == ' ') {
    *user_action = Action;
    *tetris = 4;
  }
}

void print_menu(WINDOW *brick_game_window) {
  for (int i = 16; i < 28; ++i)
    for (int j = 12; j < 31; ++j) print_final_frame(brick_game_window, i, j);

  mvwprintw(brick_game_window, 17, 14, "%s", bg_objects(COMBS, MENU1));
  mvwprintw(brick_game_window, 18, 14, "%s", bg_objects(COMBS, MENU2));
  mvwprintw(brick_game_window, 19, 14, "%s", bg_objects(COMBS, MENU3));
  mvwprintw(brick_game_window, 20, 14, "%s", bg_objects(F_SCREEN, 7));
  mvwprintw(brick_game_window, 21, 14, "%s", bg_objects(F_SCREEN, 8));
  mvwprintw(brick_game_window, 22, 14, "%s", bg_objects(F_SCREEN, 9));
}

void clear_menu(WINDOW *brick_game_window) {
  for (int i = 16; i < 28; ++i)
    for (int j = 12; j < 31; ++j) mvwprintw(brick_game_window, i, j, "%s", " ");
}

void user_menu(WINDOW *brick_game_window, int *user_action) {
  int c = wgetch(brick_game_window);

  if (c == '1')
    *user_action = 1;
  else if (c == '2')
    *user_action = 2;
  else if (c == '3' || c == 'q' || c == 'Q')
    *user_action = 3;
}
