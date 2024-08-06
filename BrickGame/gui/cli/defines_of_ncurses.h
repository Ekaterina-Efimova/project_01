#ifndef DEFINE_OF_NCURSES_H
#define DEFINE_OF_NCURSES_H

#include <stdlib.h>

#define WIN_INIT() \
  {                \
    initscr();     \
    noecho();      \
    curs_set(0);   \
  }

#define WIN_END()                                     \
  {                                                   \
    wattroff(brick_game_window, COLOR_PAIR(DEFAULT)); \
    delwin(brick_game_window);                        \
    endwin();                                         \
  }

#define PRINT()                                     \
  {                                                 \
    keypad(brick_game_window, TRUE);                \
    nodelay(brick_game_window, TRUE);               \
    start_color();                                  \
    init_pair(DEFAULT, COLOR_BLUE, COLOR_WHITE);    \
    init_pair(UNACTIVE, COLOR_YELLOW, COLOR_WHITE); \
    init_pair(WORDS, COLOR_MAGENTA, COLOR_WHITE);   \
  }

// массивы-объекты
enum objects { INFO, F_SCREEN, LINE, HELPERS, COMBS, YOU_WIN, YOU_LOSE };
enum elem {
  ELEM1,
  ELEM2,
  ELEM3,
  ELEM4,
  ELEM5,
  ELEM6,
  ELEM7,
  ELEM8,
  ELEM9,
  ELEM10
};
enum help { HELP1, HELP2, HELP3, HELP4, HELP5 };
enum combinations {
  PAUSE1,
  PAUSE2,
  PAUSE3,
  SQUARE1,
  SQUARE2,
  NOPAUSE1,
  YOU1,
  YOU2,
  YOU3,
  YOU_LOSE1,
  YOU_LOSE2,
  YOU_LOSE3,
  YOU_WIN1,
  YOU_WIN2,
  YOU_WIN3,
  MENU1,
  MENU2,
  MENU3
};
enum info_word { HIGHSCORE, SCORE, LEVEL, SPEED, SPEED_UP, NEXT, YOUR_SCORE };

const char *bg_objects(int j, int i);

#endif