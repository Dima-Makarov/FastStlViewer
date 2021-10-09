
#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QFileDialog>

#include "View/view.h"
#include "Model/Model.h"

class Controller : public QWidget {
  Q_OBJECT
 public:
  Controller();
  ~Controller() override;
  void mousePressEvent(QMouseEvent* e) override;
  void mouseReleaseEvent(QMouseEvent* e) override;
  void mouseMoveEvent(QMouseEvent* e) override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;
  void paintEvent(QPaintEvent*) override;

 private:
  int previous_x_position_ = 0;
  int previous_y_position_ = 0;
  bool is_lkm_pressed = false;
  void RequestFilepath();
  Model* model_;
  View* view_;
};
