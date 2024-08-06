#include "tetris_matrix.h"

void sigact(params_t *prms) {
  const action fsm_table[10][8] = {
      {exitstate, exitstate, exitstate, exitstate, exitstate, exitstate,
       exitstate, exitstate},
      {pauses, pauses, pauses, pauses, pauses, pauses, pauses, pauses},
      {spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn},
      {shifting, shifting, shifting, shifting, shifting, shifting, shifting,
       shifting},
      {exitstate, exitstate, exitstate, moveleft, moveright, exitstate,
       shifting, rotate},
      {conection, conection, conection, conection, conection, conection,
       conection, conection},
      {check, check, check, check, check, check, check, check},
      {distroy, distroy, distroy, distroy, distroy, distroy, distroy, distroy},
      {gameover, gameover, gameover, gameover, gameover, gameover, gameover,
       gameover},
      {exitstate, exitstate, exitstate, exitstate, exitstate, exitstate,
       exitstate, exitstate}};

  action act = fsm_table[prms->tetris_state][prms->activity];

  if (act) act(prms);
}

void check(params_t *prms) {
  if (check_fallen(prms->game_info->field, prms->tetramino)) {
    if (prms->flag == SPAWN) {
      prms->tetris_state = EXIT_STATE;
      prms->activity = Start;
      prms->flag++;

    } else if (prms->flag != CONECTION) {
      prms->tetris_state = CONECTION;
    }

    else if (check_loss(prms->game_info->field) || prms->flag == SPAWN) {
      prms->tetris_state = GAMEOVER;

    } else {
      prms->tetris_state = DISTROY;
    }

  } else {
    prms->tetris_state = EXIT_STATE;
    prms->activity = Start;
    prms->flag = SPAWN;
  }
}

void pauses(params_t *prms) {
  prms->game_info->pause = 1;
  prms->tetris_state = EXIT_STATE;
}

void spawn(params_t *prms) {
  update_figure(prms->tetramino, prms->next_tetr);
  add_figure(prms->game_info->field, prms->tetramino, TEMPORARY);
  update_next_field(prms);
  prms->tetris_state = CHECKING;
  prms->flag = SPAWN;
}

void shifting(params_t *prms) {
  if (prms->flag == SPAWN) {
    BLOCKS prms->Y_FIGURE++;
    prms->tetramino->count_down++;
  }

  update_field(prms);
  prms->tetris_state = CHECKING;
}

void moveright(params_t *prms) {
  tetramino_position temp = {
      .type = 0,
      .state = 0,
      .tetramino_state = {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
      .count_width = 0,
      .count_down = 0,
      .rotate = 0};
  change_tetramino(&temp, prms->tetramino);
  BLOCKS temp.tetramino_state[i][X]++;

  if (!check_frame_rigth(&temp) &&
      !check_intersection(prms->game_info->field, &temp)) {
    BLOCKS prms->X_FIGURE++;
    prms->tetramino->count_width++;
  }

  update_field(prms);
  prms->tetris_state = CHECKING;
}

void moveleft(params_t *prms) {
  tetramino_position temp = {
      .type = 0,
      .state = 0,
      .tetramino_state = {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
      .count_width = 0,
      .count_down = 0,
      .rotate = 0};
  change_tetramino(&temp, prms->tetramino);
  BLOCKS temp.tetramino_state[i][X]--;

  if (!check_frame_left(&temp) &&
      !check_intersection(prms->game_info->field, &temp)) {
    BLOCKS prms->X_FIGURE--;
    prms->tetramino->count_width--;
  }

  update_field(prms);
  prms->tetris_state = CHECKING;
}

void rotate(params_t *prms) {
  prms->tetramino->state++;
  if (prms->tetramino->state >= 4) prms->tetramino->state %= 4;

  tetramino_position temp;
  tetraminoes(prms->tetramino->type, prms->tetramino->state,
              temp.tetramino_state);

  BLOCKS {
    temp.tetramino_state[i][X] += prms->tetramino->count_width;
    temp.tetramino_state[i][Y] += prms->tetramino->count_down;
  }

  if (!check_intersection(prms->game_info->field, &temp) &&
      !check_frame_rigth(&temp) && !check_frame_left(&temp))
    change_tetramino(prms->tetramino, &temp);

  update_field(prms);
  prms->tetris_state = CHECKING;
}

void distroy(params_t *prms) {
  prms->line_counter = 0;

  for (int i = 0; i < F_HEIGHT; i++) {
    if (check_distroy(prms->game_info->field, i)) {
      ++prms->line_counter;
      remove_lines(prms->game_info->field, i);
      remove_temp(prms->game_info->field);

    } else {
      prms->tetris_state = SPAWN;
      prms->flag = SPAWN;
    }
  }

  if (prms->line_counter) update_current_state(prms);
}

void conection(params_t *prms) {
  BLOCKS prms->game_info->field[prms->Y_FIGURE][prms->X_FIGURE] = CONSTANT;
  remove_temp(prms->game_info->field);
  prms->flag = CONECTION;
  prms->tetris_state = CHECKING;
}

void gameover(params_t *prms) {
  remove_temp(prms->game_info->field);
  prms->flag = GAMEOVER;
  prms->tetris_state = EXIT_STATE;
}

void exitstate(params_t *prms) {
  // prms->flag = SPAWN;
  prms->tetris_state = EXIT_STATE;
}
