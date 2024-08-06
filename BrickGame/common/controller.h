#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../brick_game/snake/snake_controller.h"
#include "../brick_game/tetris/tetris_controller.h"
#include "bg_objects.h"

namespace s21 {

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

int *get_game();
Snake_controller *get_snake_game();
params_t *get_tetris_game();
bool *gameOver();
}  // namespace s21

#endif