#include <iostream>
#include <QMainWindow>
#include <QApplication>
#include "Controller/controller.h"

int main(int argc, char* argv[]) {
  QApplication qapp(argc, argv);
  std::vector<QString> args;
  args.reserve(argc);
  for (int i = 0; i < argc; i++) {
    args.emplace_back(argv[i]);
  }
  Controller controller(args);
  controller.show();
  return QApplication::exec();
}
