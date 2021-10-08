
#pragma once

#include <QPainter>
#include <QPushButton>
#include "Model/Model.h"

class View {
 public:
  explicit View(QWidget* parent, Model* model);
  void Update(QPainter* painter);
  const QPushButton& GetLoadFile() const;
 private:
  QWidget* parent_;
  Model* model_;
  QPushButton load_file_;
};
