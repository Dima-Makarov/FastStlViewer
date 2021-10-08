#include <iostream>
#include "view.h"

View::View(QWidget* parent, Model* model)
    : parent_(parent), model_(model), load_file_("Load file", parent_) {};

void View::Update(QPainter* painter) {
  auto triangles = model_->GetTriangles();
  painter->translate(200, 200);
  for (auto triangle: triangles) {
    QLine l1(triangle.vertex1.x, triangle.vertex1.y, triangle.vertex2.x, triangle.vertex2.y);
    QLine l2(triangle.vertex2.x, triangle.vertex2.y, triangle.vertex3.x, triangle.vertex3.y);
    QLine l3(triangle.vertex3.x, triangle.vertex3.y, triangle.vertex1.x, triangle.vertex1.y);
    painter->drawLine(l1);
    painter->drawLine(l2);
    painter->drawLine(l3);
  }
}

const QPushButton& View::GetLoadFile() const {
  return load_file_;
}
