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
    //args.emplace_back(R"(C:\Users\User\Downloads\1903_Wright_Flyer_-_3D_model_by_The_Smithsonian_Institution_-_Sketchfab.stl)");
    args.emplace_back(R"(C:\Users\User\Downloads\sphere3.stl)");
  }
  Controller controller(args);
  controller.show();
  return QApplication::exec();
}
