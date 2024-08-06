#include "tetris_controller.h"

void updateCurrentStateTetris(params_t *prms, UserAction_t action) {
  srand(time(NULL));
  update_next_field(prms);

  if (action != Pause) {
    prms->game_info->pause = 0;
    if (time_action(prms->game_info->speed)) prms->tetris_state = SHIFTING;
  } else {
    prms->game_info->pause = 1;
    prms->tetris_state = PAUSE;
  }

  while (prms->tetris_state != EXIT_STATE) sigact(prms);
  result(prms->game_info, FILE_SCORE);
}

int userInputTetris(UserAction_t action) {
  int state;
  if (action == Start)
    state = START;
  else if (action == Pause)
    state = PAUSE;
  else if (action == Left)
    state = MOVING;
  else if (action == Right)
    state = MOVING;
  else if (action == Up)
    state = MOVING;
  else if (action == Down)
    state = MOVING;
  else if (action == Terminate)
    state = GAMEOVER;
  else if (action == Action)
    state = MOVING;

  return state;
}

void return_tetris(params_t *prms) {
  tetris_malloc(prms);
  init_tetris(prms);
}

int time_action(int speed) {
  static int t = 0;
  int result = 0;
  t++;
  if (t == NEW_SPEED) {
    result = 1;
    t = 0;
  }

  return result;
}