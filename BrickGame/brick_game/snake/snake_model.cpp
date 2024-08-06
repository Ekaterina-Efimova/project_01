#include "snake_model.hpp"

using namespace s21;

Snake_model::Snake_model() {
  gen = std::mt19937(rd());
  dis_width = std::uniform_int_distribution<>(0, F_WIDTH - 1);
  dis_height = std::uniform_int_distribution<>(0, F_HEIGHT - 1);
  snake = {{8, 5}, {9, 5}, {10, 5}, {11, 5}};
  init_apple();
  init_game_info();
  snake_length = SNAKE_LENGTH - 1;
  activity = Pause; 
  state = SNAKE_PAUSE;
  derect = UP;
  gameover = false;
  hold = false;
  conect = 0;
};

Snake_model::~Snake_model() {
  if (info->score == info->highscore) write_score();

  if (info->field) {
    for (int i = 0; i < F_HEIGHT; i++) delete[] info->field[i];
    delete[] info->field;
    info->field = nullptr;
  }

  if (info->next) {
    for (int i = 0; i < NEXT_HEIGHT; i++) delete[] info->next[i];
    delete[] info->next;
    info->next = nullptr;
  }

  if (info) {
    delete info;
    info = nullptr;
  }
}

void Snake_model::clear() {
  if (info->score == info->highscore) write_score();
  snake = {{8, 5}, {9, 5}, {10, 5}, {11, 5}};
  init_apple();
  set_field();

  info->score = 0;
  info->level = 1;
  info->speed = 1;
  info->pause = 1;

  snake_length = SNAKE_LENGTH - 1;
  activity = Pause;
  state = SNAKE_PAUSE;
  derect = UP;
  gameover = false;
  hold = false;
  conect = 0;
}

void Snake_model::init_apple() {
  do {
    apple.first = dis_width(gen);
    apple.second = dis_height(gen);
  } while (check_apple_coord());
}

bool Snake_model::check_apple_coord() {
  bool result = false;

  for (std::pair<int, int> &s : snake)
    if (s.second == apple.first && s.first == apple.second) result = true;

  return result;
}

void Snake_model::init_game_info() {
  info = new GameInfo_t;
  init_field();
  init_next_field();

  info->highscore = read_score();
  info->score = 0;
  info->level = 1;
  info->speed = 1;
  info->pause = 1;
}

void Snake_model::init_field() {
  malloc_field();
  empty_field();
  put_snake();
}

void Snake_model::malloc_field() {
  info->field = new int *[F_HEIGHT];
  for (int i = 0; i < F_HEIGHT; i++) info->field[i] = new int[F_WIDTH];
}

void Snake_model::empty_field() {
  for (int i = 0; i < F_HEIGHT; i++)
    for (int j = 0; j < F_WIDTH; j++) info->field[i][j] = SNAKE_EMPTY;
}

void Snake_model::put_snake() {
  for (auto s : snake) info->field[s.first][s.second] = SNAKE;
  info->field[snake[0].first][snake[0].second] = SNAKE_HEAD;
}

void Snake_model::init_next_field() {
  info->next = new int *[NEXT_HEIGHT];
  for (int i = 0; i < NEXT_HEIGHT; i++) info->next[i] = new int[NEXT_WIDTH];
  for (int i = 0; i < NEXT_HEIGHT; i++)
    for (int j = 0; j < NEXT_HEIGHT; j++) info->next[i][j] = SNAKE_EMPTY;
}

void Snake_model::set_field() {
  empty_field();
  put_snake();
  info->field[apple.second][apple.first] = APPLE;
}

void Snake_model::write_score() {
  std::ofstream file(SNAKE_FILE);
  if (file.is_open()) {
    file << info->highscore;
    file.close();
  }
}

int Snake_model::read_score() {
  int score = 0;
  std::ifstream file(SNAKE_FILE);
  if (file.is_open()) {
    file >> score;
    file.close();
  }
  return score;
};

//____________________________________________________________________________

void Snake_model::snake_game() {
  if (state == SNAKE_START)
    start();
  else if (state == SNAKE_PAUSE)
    pause();
  else if (state == SNAKE_SPAWN)
    spawn();
  else if (state == SNAKE_SHIFTING)
    shifting();
  else if (state == SNAKE_MOVING) {
    if (activity == Left)
      move_left();
    else if (activity == Right)
      move_right();
    else if (activity == Up)
      move_up();
    else if (activity == Down)
      move_down();
  } else if (state == SNAKE_CONECTION)
    conection();
  else if (state == SNAKE_CHECKING)
    checking();
  else if (state == SNAKE_GROW)
    growing();
  else if (state == SNAKE_GAME_OVER)
    game_over();
  else if (state == SNAKE_EXIT_STATE)
    exit_state();
}

void Snake_model::set_snake_head() {
  if (derect == UP)
    set_snake_up();
  else if (derect == DOWN)
    set_snake_down();
  else if (derect == LEFT)
    set_snake_left();
  else if (derect == RIGHT)
    set_snake_right();
}

void Snake_model::set_snake_up() {
  snake.insert(snake.begin(),
               std::make_pair(snake[0].first - 1, snake[0].second));
}
void Snake_model::set_snake_down() {
  snake.insert(snake.begin(),
               std::make_pair(snake[0].first + 1, snake[0].second));
}
void Snake_model::set_snake_left() {
  snake.insert(snake.begin(),
               std::make_pair(snake[0].first, snake[0].second - 1));
}
void Snake_model::set_snake_right() {
  snake.insert(snake.begin(),
               std::make_pair(snake[0].first, snake[0].second + 1));
}

void Snake_model::shifting() {
  set_snake_head();
  snake.pop_back();
  state = SNAKE_CHECKING;
}

void Snake_model::move_left() {
  if (derect != RIGHT) {
    set_snake_left();
    snake.pop_back();
    derect = LEFT;
  }
  state = SNAKE_CHECKING;
}

void Snake_model::move_right() {
  if (derect != LEFT) {
    set_snake_right();
    snake.pop_back();
    derect = RIGHT;
  }
  state = SNAKE_CHECKING;
}

void Snake_model::move_up() {
  if (derect != DOWN) {
    set_snake_up();
    snake.pop_back();
    derect = UP;
  }
  state = SNAKE_CHECKING;
}

void Snake_model::move_down() {
  if (derect != UP) {
    set_snake_down();
    snake.pop_back();
    derect = DOWN;
  }
  state = SNAKE_CHECKING;
}

void Snake_model::spawn() {
  init_apple();
  set_field();
  state = SNAKE_EXIT_STATE;
}

void Snake_model::growing() {
  snake_length++;
  snake.push_back(
      std::make_pair(snake[snake_length].first, snake[snake_length].second));
  conect--;
}

void Snake_model::conection() {
  info->score++;
  if (NEW_LEVEL) {
    info->level++;
    info->speed++;
  }

  if (info->score > info->highscore) info->highscore = info->score;

  if (info->score == FINAL_SCORE) state = SNAKE_GAME_OVER;

  conect++;
  state = SNAKE_SPAWN;
}

void Snake_model::game_over() {
  gameover = true;
  state = SNAKE_EXIT_STATE;
}

void Snake_model::start() {
  info->pause = 0;
  state = SNAKE_SHIFTING;
};

void Snake_model::pause() {
  state = SNAKE_EXIT_STATE;
  info->pause = 1;
}

void Snake_model::checking() {
  if (check_die()) {
    state = SNAKE_GAME_OVER;
  } else if (snake[0].second == apple.first && snake[0].first == apple.second) {
    state = SNAKE_CONECTION;
  } else {
    state = SNAKE_EXIT_STATE;
    set_field();
  }
  if (conect && timer()) growing();
}

bool Snake_model::check_die() {
  bool result = false;

  if (snake[0].first == -1 || snake[0].second == -1 ||
      snake[0].first == F_HEIGHT || snake[0].second == F_WIDTH ||
      snake[snake_length].first == -1 || snake[snake_length].second == -1 ||
      snake[snake_length].first == F_HEIGHT ||
      snake[snake_length].second == F_WIDTH)
    result = true;

  if (!result)
    for (int i = 1; i < snake_length; i++)
      if (snake[0] == snake[i]) result = true;

  return result;
}

void Snake_model::set_state(UserAction_t action) {
  if (action == Start) {
    info->pause = 0;
    state = SNAKE_SHIFTING;
  } else if (action == Pause)
    state = SNAKE_PAUSE;
  else if (action == Left)
    state = SNAKE_MOVING;
  else if (action == Right)
    state = SNAKE_MOVING;
  else if (action == Up)
    state = SNAKE_MOVING;
  else if (action == Down)
    state = SNAKE_MOVING;
  else if (action == Terminate)
    state = SNAKE_GAME_OVER;
}

bool Snake_model::timer() {
  static int t = 0;
  bool result = false;
  t++;
  if (t == snake_length) {
    result = true;
    t = 0;
  }
  return result;
}
