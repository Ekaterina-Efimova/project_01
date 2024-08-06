#pragma once

#define FINAL_SCORE 200
#define SNAKE_LENGTH 4

#define LEVEL_UP 5
#define FINAL_LEVEL 10
#define NEW_LEVEL (info->score % LEVEL_UP == 0 && info->level < FINAL_LEVEL)
#define SPEED 300
#define SPEED_UP1 40
#define SPEED_UP2 15
#define NEW_SPEED                           \
  (SPEED - (speed < 5 ? (speed * SPEED_UP1) \
                      : (5 * SPEED_UP1 + (speed - 5) * SPEED_UP2)))

#define SNAKE_FILE "brick_game/snake/score/snake.txt"

typedef enum { UP, DOWN, LEFT, RIGHT } direction;
typedef enum { SNAKE_EMPTY, SNAKE, APPLE, SNAKE_HEAD } field;
typedef enum {
  SNAKE_START,
  SNAKE_PAUSE,
  SNAKE_SPAWN,
  SNAKE_SHIFTING,
  SNAKE_MOVING,
  SNAKE_CONECTION,
  SNAKE_CHECKING,
  SNAKE_GROW,
  SNAKE_GAME_OVER,
  SNAKE_EXIT_STATE
} snake_state_t;
