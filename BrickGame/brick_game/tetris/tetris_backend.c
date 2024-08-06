#include "tetris_backend.h"

#include <stdlib.h>
void init_tetris(params_t *prms) {
  init_game_info(prms->game_info);
  prms->tetris_state = PAUSE;
  prms->activity = Pause;
  init_figure(prms->tetramino);
  init_next_figure(prms->next_tetr);
  read_highscore(FILE_SCORE, &prms->game_info->highscore);
  prms->line_counter = 0;
  prms->flag = SPAWN;
}

void init_game_info(GameInfo_t *game_info) {
  init_field(game_info->field, game_info->next);
  game_info->score = 0;
  game_info->highscore = 0;
  game_info->level = 1;
  game_info->speed = 1;
  game_info->pause = 1;
}

void init_field(int **field, int **next) {
  FIELD field[i][j] = EMPTY;

  for (int i = 0; i < NEXT_HEIGHT; i++)
    for (int j = 0; j < NEXT_WIDTH; j++) next[i][j] = EMPTY;
}

void tetris_malloc(params_t *prms) {
  prms->game_info = (GameInfo_t *)malloc(sizeof(GameInfo_t));
  prms->game_info->field = (int **)malloc(F_HEIGHT * sizeof(int *));
  for (int i = 0; i < F_HEIGHT; ++i)
    prms->game_info->field[i] = (int *)calloc(F_WIDTH, sizeof(int));

  prms->game_info->next = (int **)malloc(NEXT_HEIGHT * sizeof(int *));
  for (int i = 0; i < NEXT_HEIGHT; ++i)
    prms->game_info->next[i] = (int *)calloc(NEXT_WIDTH, sizeof(int));

  prms->tetramino = (tetramino_position *)malloc(sizeof(tetramino_position));
  prms->next_tetr = (next_tetramino *)malloc(sizeof(next_tetramino));
}

void tetris_free(params_t *prms) {
  for (int i = 0; i < F_HEIGHT; ++i) {
    free(prms->game_info->field[i]);
    prms->game_info->field[i] = NULL;
  }
  free(prms->game_info->field);
  prms->game_info->field = NULL;

  for (int i = 0; i < NEXT_HEIGHT; ++i) {
    free(prms->game_info->next[i]);
    prms->game_info->next[i] = NULL;
  }
  free(prms->game_info->next);
  prms->game_info->next = NULL;

  free(prms->tetramino);
  prms->tetramino = NULL;

  free(prms->next_tetr);
  prms->next_tetr = NULL;

  free(prms->game_info);
  prms->game_info = NULL;
}

void init_figure(tetramino_position *tetramino) {
  int cur_tetramino = rand() % 7;
  int cur_state = rand() % 4;

  tetramino->type = cur_tetramino;
  tetramino->state = cur_state;
  tetraminoes(cur_tetramino, cur_state, tetramino->tetramino_state);
  tetramino->count_width = 0;
  tetramino->count_down = 0;
  tetramino->rotate = 0;
}

void init_next_figure(next_tetramino *next_tetr) {
  int next_tetramino = rand() % 7;
  int next_state = rand() % 4;

  next_tetr->type = next_tetramino;
  next_tetr->state = next_state;
  tetraminoes(next_tetramino, next_state, next_tetr->tetramino_state);
}

void update_figure(tetramino_position *tetramino, next_tetramino *next_tetr) {
  tetramino->type = next_tetr->type;
  tetramino->state = next_tetr->state;

  BLOCKS {
    X_FIGURE = next_tetr->tetramino_state[i][X];
    Y_FIGURE = next_tetr->tetramino_state[i][Y];
  }

  tetramino->count_width = 0;
  tetramino->count_down = 0;
  tetramino->rotate = 0;

  init_next_figure(next_tetr);
}

void change_tetramino(tetramino_position *tetramino, tetramino_position *temp) {
  BLOCKS {
    X_FIGURE = temp->tetramino_state[i][X];
    Y_FIGURE = temp->tetramino_state[i][Y];
  }
}

void update_next_field(params_t *prms) {
  for (int i = 0; i < NEXT_HEIGHT; i++)
    for (int j = 0; j < NEXT_WIDTH; j++) prms->game_info->next[i][j] = EMPTY;

  BLOCKS {
    prms->game_info->next[prms->next_tetr->tetramino_state[i][Y]]
                         [prms->next_tetr->tetramino_state[i][X] - 3] =
        TEMPORARY;
  }
}

void update_field(params_t *prms) {
  remove_temp(prms->game_info->field);
  if (prms->flag != CONECTION)
    add_figure(prms->game_info->field, prms->tetramino, TEMPORARY);
}

void remove_temp(int **field) {
  FIELD field[i][j] = field[i][j] == TEMPORARY ? EMPTY : field[i][j];
}

void add_figure(int **field, const tetramino_position *figure,
                const field_t value) {
  BLOCKS
  if (figure->tetramino_state[i][Y] >= 0)
    field[figure->tetramino_state[i][Y]][figure->tetramino_state[i][X]] = value;
}

void remove_lines(int **field, int line) {
  for (int i = line; i > 0; i--)
    for (int j = 0; j < F_WIDTH; j++) field[i][j] = field[i - 1][j];
}

void update_current_state(params_t *prms) {
  prms->game_info->score += prms->line_counter == 1   ? ONE_LINE
                            : prms->line_counter == 2 ? TWO_LINES
                            : prms->line_counter == 3 ? THREE_LINES
                            : prms->line_counter == 4 ? FOUR_LINES
                                                      : ZERO;
  if (prms->game_info->score < MAX_SCORE) {
    prms->game_info->level = prms->game_info->score / LEVEL_UP_SCORE + 1;
    prms->game_info->speed = prms->game_info->level;
  }
}

void read_highscore(const char *filename, int *highscore) {
  FILE *file = fopen(filename, "r");
  if (file) {
    fscanf(file, "%d", highscore);
    fclose(file);
  }
}

void write_highscore(const char *filename, int *highscore) {
  FILE *file = fopen(filename, "w");
  if (file) {
    fprintf(file, "%d", *highscore);
    fclose(file);
  }
}

// long long get_time_ms() {
//   struct timeval tv;
//   gettimeofday(&tv, NULL);
//   return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
// }

// int timer(long long *prev_time, long long curr_time, int delay) {
//   int res = 0;
//   if (curr_time - *prev_time >= delay) {
//     *prev_time = curr_time;
//     res = 1;
//   }
//   return res;
// }

void result(GameInfo_t *game_info, const char *file) {
  if (game_info->score > game_info->highscore) {
    write_highscore(file, &game_info->score);
    game_info->highscore = game_info->score;
  }
}