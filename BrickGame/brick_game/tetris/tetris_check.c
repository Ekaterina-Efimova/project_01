#include "tetris_check.h"

int check_distroy(int **field, int line) {
  int j = 0;
  for (; j < F_WIDTH && field[line][j] == CONSTANT; j++)
    ;

  return j == F_WIDTH;
}

int check_fallen(int **field, const tetramino_position *tetramino) {
  int res = 0;

  CHECK res = Y_FIGURE == 19;
  CHECK res = field[Y_FIGURE + 1][X_FIGURE] == CONSTANT;

  return res;
}

int check_loss(int **field) {
  int loss = 0;

  for (int j = 0; j < 10 && !loss; ++j) loss = field[0][j] == CONSTANT;

  return loss;
}

int check_intersection(int **field, const tetramino_position *tetramino) {
  int res = 0;

  CHECK {
    if (Y_FIGURE >= 0) res = (field[Y_FIGURE][X_FIGURE] == CONSTANT);
  }
  return res;
}

int check_frame_left(const tetramino_position *tetramino) {
  int res = 0;

  CHECK {
    if (X_FIGURE < 0) res = 1;
  }
  return res;
}

int check_frame_rigth(const tetramino_position *tetramino) {
  int res = 0;

  CHECK {
    if (X_FIGURE > 9) res = 1;
  }

  return res;
}