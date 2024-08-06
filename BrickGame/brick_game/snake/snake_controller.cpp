#include "snake_controller.h"
#undef scroll

using namespace s21;

GameInfo_t Snake_controller::updateCurrentStateSnake() {
  GameInfo_t temp;

  while (get_state() != SNAKE_EXIT_STATE) snake_game();
  if (model->get_activity() != Pause) model->set_activity(Action);

  temp.field = model->get_field();
  temp.next = model->get_next();
  temp.score = model->get_score();
  temp.level = model->get_level();
  temp.highscore = model->get_highscore();
  temp.pause = model->get_pause();
  temp.speed = model->get_speed();

  return temp;
}

void Snake_controller::userInputSnake(UserAction_t action, bool hold) {
  if (action != Pause && time_action(action != Action)) action = Start;

  model->set_activity(action);
  model->set_hold(hold);
  model->set_state(action);
}

void Snake_controller::clear() { model->clear(); }

bool Snake_controller::time_action(bool f) {
  static int t = 0;
  int speed = model->get_speed();
  bool result = false;
  t++;
  if (t == NEW_SPEED) {
    result = true;
    t = 0;
  }
  if (f) t = 0;
  return result;
}