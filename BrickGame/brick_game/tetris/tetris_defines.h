#ifndef DEFINES_H
#define DEFINES_H

#define GET_USER_INPUT getch()

#define GAME prms.activity != Terminate
#define NO_PAUSE (prms.activity != PAUSE)

#define FILE_SCORE "brick_game/tetris/score/tetris_highscore.txt"

// максимальный уровень
#define LEVEL_CNT 10
#define LEVEL_UP_SCORE 600
#define MAX_SCORE 6000

// циклы
#define BLOCKS for (int i = 0; i < 4; i++)
#define CHECK for (int i = 0; i < 4 && !res; i++)
#define FIELD                        \
  for (int i = 0; i < F_HEIGHT; i++) \
    for (int j = 0; j < F_WIDTH; j++)

// координаты фигуры
#define X_FIGURE tetramino->tetramino_state[i][X]
#define Y_FIGURE tetramino->tetramino_state[i][Y]

// скорость
#define SPEED 300
#define SPEED_UP1 40
#define SPEED_UP2 15
#define NEW_SPEED                           \
  (SPEED - (speed < 5 ? (speed * SPEED_UP1) \
                      : (5 * SPEED_UP1 + (speed - 5) * SPEED_UP2)))
#endif