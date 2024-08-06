#pragma once
#include <chrono>

#include "../../common/bg_objects.h"
#include "snake_define.hpp"
#include "snake_model.hpp"

namespace s21 {
class Snake_controller {
 private:
  Snake_model *model;
  // возврат текущего состояния
  int get_state() { return model->get_state(); };
  // игра
  void snake_game() { model->snake_game(); };
  // таймер
  bool time_action(bool f);

 public:
  Snake_controller() : model(new Snake_model){};
  ~Snake_controller() {
    if (model) {
      delete model;
      model = nullptr;
    }
  };

  // смена значения текущего состояния
  GameInfo_t updateCurrentStateSnake();
  // возврат пользовательского ввода
  void userInputSnake(UserAction_t action, bool hold);
  // флаг конца игры
  int get_gameover() { return model->get_gameover(); };
  // обновление model
  void clear();
};
}  // namespace s21