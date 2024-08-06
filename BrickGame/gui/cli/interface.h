#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncursesw/curses.h>

#include "../../common/bg_objects.h"
#include "defines_of_ncurses.h"

#define DEFAULT 1
#define UNACTIVE 2
#define WORDS 3
#define TEMP 4

WINDOW *init_ncurses();
void print_display(WINDOW *brick_game_window);
void print_square(WINDOW *brick_game_window, int i, int j);
void print_box(WINDOW *brick_game_window);
void print_backgarund(WINDOW *brick_game_window);
void print_helpers(WINDOW *brick_game_window);

void update_display(WINDOW *brick_game_window, GameInfo_t *game_info);
void reset_info(WINDOW *brick_game_window, int pause);
void print_active_next(WINDOW *brick_game_window, int i, int j);
void print_pause(WINDOW *brick_game_window, int pause);
void printf_info(WINDOW *brick_game_window, GameInfo_t *game_info);
void print_score(WINDOW *brick_game_window, int score, int highscore);
void print_level(WINDOW *brick_game_window, int level);
void print_speed(WINDOW *brick_game_window, int speed);
void print_next(WINDOW *brick_game_window, int i, int j);
void print_field(WINDOW *brick_game_window, int **field);
void print_result(WINDOW *brick_game_window, GameInfo_t *game_info);
void print_final_frame(WINDOW *brick_game_window, int i, int j);
void print_final_info(WINDOW *brick_game_window, GameInfo_t *game_info);
void print_lose(WINDOW *brick_game_window);
void print_win(WINDOW *brick_game_window);

void user_input(WINDOW *brick_game_window, int *user_action, int *tetris);

void print_menu(WINDOW *brick_game_window);
void user_menu(WINDOW *brick_game_window, int *user_action);
void clear_menu(WINDOW *brick_game_window);

#endif