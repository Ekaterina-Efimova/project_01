#ifndef TETRIS_H
#define TETRIS_H

#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "../../common/bg_objects.h"
#include "tetris_backend.h"
#include "tetris_defines.h"
#include "tetris_matrix.h"
#include "tetris_objects.h"

void updateCurrentStateTetris(params_t *prms, UserAction_t action);
int userInputTetris(UserAction_t action);
void return_tetris(params_t *prms);

int time_action(int speed);
#endif
