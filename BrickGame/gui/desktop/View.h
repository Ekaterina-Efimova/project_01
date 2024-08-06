#ifndef DESKTOP_H_
#define DESKTOP_H_

#include <QDebug>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QString>
#include <QTimer>
#include <QWidget>

#include "../../common/bg_objects.h"
#include "../../common/controller.h"

#define SIZE_DOT 30

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

  // номера цветов
  enum color { GREY, RED, GREEN, YELLOW, ORANGE };
  // цвета
  const QColor colors[8] = {
      QColor(125, 125, 125),  // серый
      QColor(255, 0, 0),      // красный
      QColor(103, 250, 0),    // зеленый
      QColor(250, 235, 5),    // желтый
      QColor(250, 200, 5),    // оранжевый
  };
  enum game { NONE, SNAKE, TETRIS };

 protected:
  void keyPressEvent(QKeyEvent *) override;
  void paintEvent(QPaintEvent *event) override;

 private slots:
  void on_playAgain_clicked();
  void on_closeGame_clicked();
  void on_start_tetris_btn_clicked();
  void on_start_snake_btn_clicked();
  void on_exit_btn_clicked();

 private:
  QTimer *timer;
  Ui::View *ui;
  game current_game;
  UserAction_t action;
  GameInfo_t info;
  bool *flag;
  int *game;

  void clear_field();
  void game_over(bool is_victory);
  void update();
  void render();
  void start_window(QLabel *p_label);
  void pause_window(QLabel *p_label);
};

}  // namespace s21

#endif
