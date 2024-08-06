#pragma once
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "../../common/bg_objects.h"
#include "snake_define.hpp"

namespace s21 {
class Snake_model {
 private:
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_int_distribution<> dis_width;
  std::uniform_int_distribution<> dis_height;

  GameInfo_t *info;
  std::vector<std::pair<int, int>> snake;
  std::pair<int, int> apple;
  int activity;
  int state;
  int snake_length;
  int derect;
  bool gameover;
  bool hold;
  int conect;

  // иницивализация поля
  void init_field();
  // выделение памяти для поля
  void malloc_field();
  // заполнение поля пустым значением
  void empty_field();
  // заполнение поля змейкой
  void put_snake();
  // инициализация следуюзщего поля
  void init_next_field();
  // инициализация яблока
  void init_apple();
  // проверка координат яблока, true - координаты совпали
  bool check_apple_coord();
  // инициализация информации о игре
  void init_game_info();
  // чтение лучшего счета
  int read_score();
  // запись лучшего счета
  void write_score();

  // смена координат головы змейки
  void set_snake_head();
  // смещение змейки вверх
  void set_snake_up();
  // смещение змейки вниз
  void set_snake_down();
  // смещение змейки влево
  void set_snake_left();
  // смещение змейки вправо
  void set_snake_right();
  // смена поля
  void set_field();

  // кнопка старт
  void start();
  // поворот налево
  void move_left();
  // поворот направо
  void move_right();
  // поворот вниз
  void move_down();
  // поворот вверх
  void move_up();
  // создание нового яблока
  void spawn();
  // пауза
  void pause();
  // рост змейки
  void growing();
  // выход из матрицы состояний
  void exit_state() { state = SNAKE_EXIT_STATE; };
  // присоединение яблока к змейке
  void conection();
  // конец из игры
  void game_over();
  // смещение змейк
  void shifting();
  // проверка
  void checking();
  // проверка на столкновение с границами
  bool check_die();
  // таймер
  bool timer();

 public:
  Snake_model();
  ~Snake_model();
  void clear();

  void snake_game();

  // получение значения следущего поля
  int **get_next() { return info->next; };
  // получение значения поля
  int **get_field() { return info->field; };
  // получение значения уровня
  int get_level() { return info->level; };
  // получение значения паузы
  int get_pause() { return info->pause; };
  // получение значения текущего счета
  int get_score() { return info->score; };
  // получение значения лучшего счета
  int get_highscore() { return info->highscore; };
  // смена значения скорости
  int get_speed() { return info->speed; };
  // получение конца игры
  bool get_gameover() { return gameover; };
  // смена значения текущей активности
  void set_activity(int new_activity) { activity = new_activity; };
  // смена значения текущего состояния
  void set_state(UserAction_t action);
  // получение значения текущего состояния
  int get_state() { return state; };
  // получение значения текущей активности
  int get_activity() { return activity; };
  void set_hold(bool new_hold) { hold = new_hold; };
};
}  // namespace s21