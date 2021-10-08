
#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>

#include "view.h"
#include "Model.h"

class Controller : public QWidget {
  Q_OBJECT
 public:
  Controller();
  ~Controller() override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;
  void paintEvent(QPaintEvent*) override;

 private:
  Model* model_;
  View* view_;
};
