
#pragma once

#include <QPainter>
#include "Model.h"

class View {
 public:
  explicit View(Model* model);
  void Update(QPainter* painter);

 private:
  Model* model_;
};



