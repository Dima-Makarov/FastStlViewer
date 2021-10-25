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
  if(argc == 1) {
    args.emplace_back("C:/Dima/mama i am programmer/projects/StlViewer/cmake-build-debug/obama_prism.stl");
  }
  Controller controller(args);
  controller.show();
  return QApplication::exec();
}
