#include <locale.h>
#include <math.h>
#include <stdlib.h>

#include "../gui/cli/interface.h"
#include "snake/snake_controller.h"
#include "tetris/tetris_controller.h"

using namespace s21;

int tetris(WINDOW *brick_game_window) {
  srand(time(NULL));

  params_t prms = {NULL, 0, 0, NULL, NULL, 0, 0};
  tetris_malloc(&prms);

  init_tetris(&prms);

  update_next_field(&prms);
  update_display(brick_game_window, prms.game_info);

  while (prms.activity != Start && prms.activity != Terminate)
    user_input(brick_game_window, &prms.activity, &prms.tetris_state);

  spawn(&prms);

  while (GAME) {
    user_input(brick_game_window, &prms.activity, &prms.tetris_state);
    updateCurrentStateTetris(&prms, (UserAction_t)prms.activity);
    update_display(brick_game_window, prms.game_info);

    if (prms.flag == GAMEOVER) {
      while (prms.activity != Terminate) {
        print_result(brick_game_window, prms.game_info);
        user_input(brick_game_window, &prms.activity, &prms.tetris_state);
      }
    }
  }

  tetris_free(&prms);
  return 0;
}

void snake(WINDOW *brick_game_window) {
  Snake_controller s;
  GameInfo_t info = s.updateCurrentStateSnake();
  update_display(brick_game_window, &info);
  int state, action;

  while (action != Start && action != Terminate)
    user_input(brick_game_window, &action, &state);

  while (action != Terminate) {
    user_input(brick_game_window, &action, &state);

    s.userInputSnake((UserAction_t)action, false);

    info = s.updateCurrentStateSnake();
    if (action != Pause) {
      info.pause = 0;
      action = Action;
    }
    result(&info, SNAKE_FILE);
    update_display(brick_game_window, &info);

    if (s.get_gameover()) {
      while (action != Terminate) {
        print_result(brick_game_window, &info);
        user_input(brick_game_window, &action, &state);
      }
    }
  }
}

void menu(WINDOW *brick_game_window) {
  int choice;
  print_menu(brick_game_window);
  while (choice < 1 || choice > 3) user_menu(brick_game_window, &choice);
  clear_menu(brick_game_window);
  if (choice == 1)
    tetris(brick_game_window);
  else if (choice == 2)
    snake(brick_game_window);
  else if (choice == 3)
    return;
}

int main() {
  setlocale(LC_ALL, "");
  WIN_INIT();
  WINDOW *brick_game_window = init_ncurses();
  print_display(brick_game_window);
  menu(brick_game_window);
  WIN_END();
  return 0;
}