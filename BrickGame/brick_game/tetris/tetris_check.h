#ifndef TETRIS_CHECK_H
#define TETRIS_CHECK_H

#include "../../common/bg_objects.h"
#include "tetris_objects.h"

int check_distroy(int **field, int line);
int check_fallen(int **field, const tetramino_position *tetramino);
int check_loss(int **field);
int check_intersection(int **field, const tetramino_position *tetramino);
int check_frame_left(const tetramino_position *tetramino);
int check_frame_rigth(const tetramino_position *tetramino);

#endif