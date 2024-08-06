#ifndef BG_OBJECTS_H
#define BG_OBJECTS_H

#define F_HEIGHT 20
#define F_WIDTH 10
#define NEXT_HEIGHT 4
#define NEXT_WIDTH 4

// информация об игре
typedef struct {
  int **field;
  int **next;
  int score;
  int highscore;
  int level;
  int speed;
  int pause;
} GameInfo_t;

// действия
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

#endif