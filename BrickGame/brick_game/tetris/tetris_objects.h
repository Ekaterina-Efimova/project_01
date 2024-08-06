#ifndef TETRIS_OBJECTS_H
#define TETRIS_OBJECTS_H

#include "../../common/bg_objects.h"
#include "tetris_defines.h"

// подсчет очков
typedef enum {
  ZERO = 0,
  ONE_LINE = 100,
  TWO_LINES = 300,
  THREE_LINES = 700,
  FOUR_LINES = 1500
} score_t;

// позиция фигуры
typedef struct {
  int type;
  int state;
  int tetramino_state[4][2];
  int count_width;
  int count_down;
  int rotate;
} tetramino_position;

typedef struct {
  int type;
  int state;
  int tetramino_state[4][2];
} next_tetramino;

// состояния игры
typedef enum {
  START,
  PAUSE,
  SPAWN,
  SHIFTING,
  MOVING,
  CONECTION,
  CHECKING,
  DISTROY,
  GAMEOVER,
  EXIT_STATE
} tetris_state_t;

typedef struct game_params {
  GameInfo_t *game_info;
  int tetris_state;
  int activity;
  tetramino_position *tetramino;
  next_tetramino *next_tetr;
  int line_counter;
  int flag;
} params_t;

typedef void (*action)(params_t *prms);

// enumы для матриы состяний фигур
typedef enum { I, J, L, O, S, Z, T } tetramino_t;
typedef enum { FIRST, SECOND, THIRD, FOURTH } tetromino_state_t;
typedef enum { ONE, TWO, THREE, FOUR } block_t;
typedef enum { X, Y } coordinate_t;

// состояние клетки
typedef enum { EMPTY, TEMPORARY, CONSTANT } field_t;

// матрица состояний фигур
void tetraminoes(int tetramino, int state, int tetr[4][2]);

#endif