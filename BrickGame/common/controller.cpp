#include "controller.h"
void s21::userInput(UserAction_t action, bool hold) {
  int *game = s21::get_game();
  if (*game == -1) {
    *game = rand() % 2;
  }

  if (*game == 1) {
    s21::Snake_controller *s = s21::get_snake_game();
    s->userInputSnake(action, hold);

  } else if (*game == 2) {
    params_t *t = s21::get_tetris_game();
    if (t->tetris_state != 3) t->tetris_state = userInputTetris(action);
    t->activity = action;
  }
}

GameInfo_t s21::updateCurrentState() {
  GameInfo_t info;
  int *game = s21::get_game();
  if (*game == -1) {
    *game = rand() % 2;
  }
  bool *flag = s21::gameOver();

  if (*game == 1) {
    Snake_controller *s = s21::get_snake_game();
    info = s->updateCurrentStateSnake();
    if (s->get_gameover()) {
      *flag = true;
      s->clear();
    }

  } else if (*game == 2) {
    params_t *t = s21::get_tetris_game();
    if (!t->next_tetr) return_tetris(t);
    updateCurrentStateTetris(t, (UserAction_t)t->activity);

    info = *t->game_info;

    if (t->flag == 8) {
      *flag = true;
      tetris_free(t);
    }
  }

  return info;
}

int *s21::get_game() {
  static int game = -1;
  return &game;
}

s21::Snake_controller *s21::get_snake_game() {
  static s21::Snake_controller s;
  return &s;
}

params_t *s21::get_tetris_game() {
  static params_t t = {NULL, 0, 0, NULL, NULL, 0, 0};
  return &t;
}

bool *s21::gameOver() {
  static bool res = false;
  return &res;
}
