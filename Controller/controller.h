
#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QTimer>
#include <QFileDialog>

#include "View/view.h"
#include "Model/Model.h"

class Controller : public QWidget {
 Q_OBJECT
 public:
  Controller(const std::vector<QString>& args);
  ~Controller() override;
  void wheelEvent(QWheelEvent* e) override;
  void mousePressEvent(QMouseEvent* e) override;
  void mouseReleaseEvent(QMouseEvent* e) override;
  void mouseMoveEvent(QMouseEvent* e) override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;
  void paintEvent(QPaintEvent*) override;

 private:
  std::pair<int, int> lmb_prev_position_;
  std::pair<int, int> rmb_prev_position_;
  bool is_lmb_pressed = false;
  bool is_rmb_pressed = false;
  void RequestFilepath();
  Model* model_;
  View* view_;
};
