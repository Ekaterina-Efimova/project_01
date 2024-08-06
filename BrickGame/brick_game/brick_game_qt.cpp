#include <QApplication>

#include "View.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::View v;
  v.show();
  return QApplication::exec();
}
