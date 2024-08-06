#ifndef TETRIS_MATRIX_H
#define TETRIS_MATRIX_H

#include "../../common/bg_objects.h"
#include "tetris_backend.h"
#include "tetris_check.h"
#include "tetris_objects.h"

void sigact(params_t *prms);

void shifting(params_t *prms);
void check(params_t *prms);
void spawn(params_t *prms);
void moveright(params_t *prms);
void moveleft(params_t *prms);
void rotate(params_t *prms);
void distroy(params_t *prms);
void conection(params_t *prms);
void gameover(params_t *prms);
void exitstate(params_t *prms);
void pauses(params_t *prms);

#endif