#include "defines_of_ncurses.h"

const char *bg_objects(int j, int i) {
  const char *object = NULL;

  static const char *info[7] = {"HIGSCORE", "SCORE", "LEVEL",     "SPEED",
                                "SPEED UP", "NEXT",  "YOUR SCORE"};
  static const char *f_screen[10] = {
      "S     - START",    "P     - PAUSE",  ">     - RIGHT", "<     - LEFT",
      "v     - PUT DOWN", "SPACE - ROTATE", "Q     - QUIT",  "1   -   TETRIS",
      "2   -   SNAKE",    "3   -   EXIT"};

  static const char *line[10] = {"═", "╔", "╚", "╗", "╝",
                                 "",  "║", "╩", " ", "╦"};

  static const char *helpers[5] = {"0", "CONTROL:", "0000", "00", "00 %%"};

  static const char *combinations[18] = {"╔═╗ ╔═╗ ╗ ╔ ╔═╗ ╔═╗",
                                         "╠═╝ ╠═╣ ║ ║ ╚═╗ ╠═",
                                         "╝   ╝ ╚ ╚═╝ ╚═╝ ╚═╝",
                                         "╔═╗",
                                         "╚═╝",
                                         "                   ",
                                         "╗ ╔ ╔═╗ ╗ ╔",
                                         "╚═╣ ║ ║ ║ ║",
                                         "╚═╝ ╚═╝ ╚═╝",
                                         "╗   ╔═╗ ╔═╗ ╔═╗",
                                         "║   ║ ║ ╚═╗ ╠═",
                                         "╚═╝ ╚═╝ ╚═╝ ╚═╝",
                                         "╗   ╔ ╔═╗ ╔╗ ╔",
                                         "║ ║ ║ ║ ║ ║╚╗║",
                                         "╚═╩═╝ ╚═╝ ╝ ╚╝",
                                         "╔═╦═╗╔═╗╔╗ ╔╗ ╔",
                                         "║ ║ ║╠═ ║╚╗║║ ║ ",
                                         "╝   ╚╚═╝╝ ╚╝╚═╝"};

  static const char *you_lose[14] = {
      "______¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶_______", "___¶¶¶¶¶¶¶¶________¶¶¶¶¶¶¶¶____",
      "_¶¶¶¶___________________¶¶¶¶¶__", "¶¶¶¶____¶¶¶¶_____¶¶¶¶_____¶¶¶__",
      "¶¶¶____¶¶¶¶¶¶___¶¶¶¶¶¶____¶¶¶¶_", "¶¶¶____¶¶¶¶¶¶___¶¶¶¶¶¶_____¶¶¶_",
      "¶¶______¶¶¶¶_____¶¶¶¶______¶¶¶¶", "¶¶__________________________¶¶¶",
      "¶¶___________¶¶¶___________¶¶¶¶", "¶¶¶_______¶¶¶¶¶¶¶¶¶________¶¶¶_",
      "¶¶¶_____¶¶¶¶¶___¶¶¶¶¶_____¶¶¶¶_", "¶¶¶____¶¶¶_________¶¶¶___¶¶¶¶__",
      "__¶¶¶_________________¶¶¶¶¶____", "_____¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶_______"};

  static const char *you_win[14] = {
      "⠄⠄⠄⢀⣠⡶⠞⠛⠛⠛⠶⣤⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄", "⠄⠄⣰⠟⠁⠄⠄⠄⠄⠛⠄⣀⠙⣦⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄",
      "⠄⢰⡏⠄⠄⠄⠄⠄⠄⠄⠄⠘⣷⣘⣧⣤⣤⣤⣀⠄⠄⠄⠄⠄", "⠄⣼⠁⠄⠄⠄⠄⠄⠄⠄⠄⣤⠞⠋⠁⠄⢀⣤⡉⠻⢦⡀⠄⠄",
      "⠄⣿⠄⠄⠄⠄⠄⠄⠄⢀⡾⠁⠄⠄⠄⠄⠄⠄⠄⢶⡄⢻⡆⠄", "⠄⢸⡆⢠⡀⠄⠄⠄⠄⢸⠇⠄⠄⠄⠄⠄⠄⠄⠄⠄⢻⡄⣷⠄",
      "⠄⠘⣧⠘⣷⡀⠄⠄⠄⣾⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠸⡇⢻⠄", "⠄⠄⠘⣧⡈⠳⣄⠄⠄⢻⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⣿⠄",
      "⠄⠄⠄⠈⠻⣦⣉⠄⠄⣸⡇⢰⡄⠄⠄⠄⠄⠄⠄⠄⠄⢠⡟⠄", "⠄⠄⠄⠄⠄⠄⠉⣿⣻⡏⢻⡄⢻⣄⠄⠄⠄⠄⠄⠄⠄⣼⠃⠄",
      "⠄⠄⠄⠄⠄⠄⠄⢹⡏⠁⠄⠻⣦⡙⠷⠄⠄⠄⠄⣠⡾⠁⠄⠄", "⠄⠄⠄⠄⠄⠄⠄⢸⡇⠄⠄⠄⠈⠛⢦⣤⣤⡴⠞⠋⠄⠄⠄⠄",
      "⠄⠄⠄⠄⠄⠄⠄⢸⡇⠄⠄⠄⠄⠄⠄⣿⣼⠇⠄⠄⠄⠄⠄⠄", "⠄⠄⠄⠄⠄⠄⠄⠸⡇⠄⠄⠄⠄⠄⠄⠸⡇⠄⠄⠄⠄⠄⠄⠄"};

  if (j == INFO)
    object = info[i];
  else if (j == F_SCREEN)
    object = f_screen[i];
  else if (j == LINE)
    object = line[i];
  else if (j == HELPERS)
    object = helpers[i];
  else if (j == COMBS)
    object = combinations[i];
  else if (j == YOU_WIN)
    object = you_win[i];
  else if (j == YOU_LOSE)
    object = you_lose[i];

  return object;
}
