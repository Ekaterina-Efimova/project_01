#ifndef TETRIS_BACKEND_H
#define TTETRIS_BACKEND_H

#include <stdio.h>
#include <string.h>

#include "../../common/bg_objects.h"
#include "tetris_defines.h"
#include "tetris_objects.h"

void init_tetris(params_t *prms);
void init_game_info(GameInfo_t *game_info);
void init_field(int **field, int **next);
void tetris_malloc(params_t *prms);
void tetris_free(params_t *prms);
void init_figure(tetramino_position *tetramino);
void init_next_figure(next_tetramino *next_tetr);
void update_figure(tetramino_position *tetramino, next_tetramino *next_tetr);
void change_tetramino(tetramino_position *tetramino, tetramino_position *temp);
void update_next_field(params_t *prms);
void update_field(params_t *prms);
void remove_temp(int **field);
void add_figure(int **field, const tetramino_position *figure,
                const field_t value);
void remove_lines(int **field, int line);
void update_current_state(params_t *prms);

void read_highscore(const char *filename, int *highscore);
void write_highscore(const char *filename, int *highscore);
void result(GameInfo_t *game_info, const char *file);

#endif