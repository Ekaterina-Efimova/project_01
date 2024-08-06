#include "View.h"

#include <iostream>

#include "ui_View.h"

using namespace s21;

View::View(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::View), current_game(NONE), action(Pause) {
  ui->setupUi(this);
  move(1000, 300);
  setWindowTitle("Brick Game");
  ui->stackedWidget->setCurrentIndex(1);
  flag = gameOver();
  timer = new QTimer(this);
  game = get_game();
  *game = current_game;

  connect(timer, &QTimer::timeout, this, &View::update);
}

View::~View() {
  if (timer != nullptr) delete timer;
  delete ui;
}

void View::keyPressEvent(QKeyEvent *event) {
  int key = event->key();
  if (key == Qt::Key_Left) {
    action = Left;
  } else if (key == Qt::Key_Right) {
    action = Right;
  } else if (key == Qt::Key_Up) {
    action = Up;
  } else if (key == Qt::Key_Down) {
    action = Down;
  } else if (key == Qt::Key_S) {
    action = Start;
  } else if (key == Qt::Key_P) {
    action = Pause;
  } else if (key == Qt::Key_Space) {
    action = Action;
  } else if (key == Qt::Key_Q) {
    action = Terminate;
  }
}

void View::paintEvent(QPaintEvent *event) {
  QWidget::paintEvent(event);
  if (current_game != NONE) {
    if (!(*flag)) {
      if (action == Start) {
        start_window(ui->InfoLabel);
      } else if (action == Pause) {
        pause_window(ui->InfoLabel);
      } else {
        ui->InfoLabel->setText("Press P for pause");
        render();
      }
    } else {
      clear_field();
      game_over(info.score == info.highscore);
    }
  }
}

void View::clear_field() {
  QPainter qp(this);
  qp.eraseRect(rect());
  qp.end();
}

void View::game_over(bool is_victory) {
  info.pause = 1;
  timer->stop();

  ui->stackedWidget->setCurrentIndex(0);
  if (is_victory) {
    ui->GameStatus->setText("YOU WON!!!");
  } else {
    ui->GameStatus->setText("GAME OVER!");
  }

  ui->MenuCurrScore->setText(QString::number(info.score));
  ui->MenuBestScore->setText(QString::number(info.highscore));
}

void View::update() {
  userInput(action, false);
  info = updateCurrentState();

  if (action != Pause) {
    if (current_game == SNAKE)
      action = Action;
    else if (current_game == TETRIS)
      action = Up;
  }

  ui->CurrScore->setText(QString::number(info.score));
  ui->CurrLevel->setText(QString::number(info.level));
  ui->BestScore->setText(QString::number(info.highscore));

  if (*flag) {
    timer->stop();
  }

  repaint();
}

void View::on_playAgain_clicked() {
  *flag = false;
  if (current_game != NONE) {
    info = updateCurrentState();
    if (current_game == TETRIS)
      ui->name_game->setText("Tetris");
    else if (current_game == SNAKE)
      ui->name_game->setText("Snake");
    ui->stackedWidget->setCurrentIndex(2);
    timer->start(10);

  } else if (current_game == NONE) {
    ui->stackedWidget->setCurrentIndex(1);
  }
}

void View::on_start_snake_btn_clicked() {
  *flag = false;
  current_game = SNAKE;
  *game = current_game;
  info = updateCurrentState();

  ui->name_game->setText("Snake");
  ui->stackedWidget->setCurrentIndex(2);
  timer->start(10);
}

void View::on_start_tetris_btn_clicked() {
  *flag = false;
  current_game = TETRIS;
  *game = current_game;
  info = updateCurrentState();

  ui->name_game->setText("Tetris");
  ui->stackedWidget->setCurrentIndex(2);
  timer->start(10);
}

void View::on_exit_btn_clicked() { close(); }

void View::on_closeGame_clicked() {
  current_game = NONE;
  *game = current_game;
  ui->stackedWidget->setCurrentIndex(1);
}

void View::render() {
  QPainter qp(this);
  qp.setBrush(QColor(90, 90, 90));
  qp.setPen(QColor(0, 0, 0));

  for (int i = 0; i < NEXT_HEIGHT; ++i)
    for (int j = 0; j < NEXT_WIDTH; ++j)
      if (info.next[i][j]) {
        qp.setBrush(colors[GREEN]);
        qp.drawRect((j + 11) * SIZE_DOT, (i + 9) * SIZE_DOT, SIZE_DOT - 1,
                    SIZE_DOT - 1);
      }

  for (int i = 0; i < F_HEIGHT; ++i)
    for (int j = 0; j < F_WIDTH; ++j)
      if (info.field[i][j] == 1) {
        qp.setBrush(colors[YELLOW]);
        qp.drawRect(j * SIZE_DOT, i * SIZE_DOT, SIZE_DOT - 1, SIZE_DOT - 1);
      } else if (info.field[i][j] == 2) {
        qp.setBrush(colors[RED]);
        qp.drawRect(j * SIZE_DOT, i * SIZE_DOT, SIZE_DOT - 1, SIZE_DOT - 1);
      } else if (info.field[i][j] == 3) {
        qp.setBrush(colors[ORANGE]);
        qp.drawRect(j * SIZE_DOT, i * SIZE_DOT, SIZE_DOT - 1, SIZE_DOT - 1);
      } else {
        qp.setBrush(colors[GREY]);
        qp.drawRect(j * SIZE_DOT, i * SIZE_DOT, SIZE_DOT - 1, SIZE_DOT - 1);
      }

  qp.end();
}

void View::start_window(QLabel *p_label) {
  p_label->setText("Press S to start");
  p_label->setStyleSheet("border: none;");
}

void View::pause_window(QLabel *p_label) {
  p_label->setText("Game on pause.<br> Press S to continue<br> or Q to exit");
}
