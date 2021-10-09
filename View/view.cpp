#include "view.h"

View::View(QWidget* parent, Model* model)
    : parent_(parent), model_(model), load_file_("Load file", parent_) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == j) {
        transform_matrix_[i][j] = 1;
      }
    }
  }
}

void View::Update(QPainter* painter) {
  painter->translate(painter->window().center());
  painter->drawEllipse(camera_.GetPosition().y, camera_.GetPosition().x, 10, 10);
  painter->drawEllipse(0,0, 4, 4);
  for (auto& triangle: triangles_) {
    triangle.vertex1 = transform_matrix_ * triangle.vertex1;
    triangle.vertex2 = transform_matrix_ * triangle.vertex2;
    triangle.vertex3 = transform_matrix_ * triangle.vertex3;
    QLine l1(triangle.vertex1.y, triangle.vertex1.x, triangle.vertex2.y, triangle.vertex2.x);
    QLine l2(triangle.vertex2.y, triangle.vertex2.x, triangle.vertex3.y, triangle.vertex3.x);
    QLine l3(triangle.vertex3.y, triangle.vertex3.x, triangle.vertex1.y, triangle.vertex1.x);
    painter->drawLine(l1);
    painter->drawLine(l2);
    painter->drawLine(l3);
  }
}

const QPushButton& View::GetLoadFileButton() const {
  return load_file_;
}

void View::MouseMove(int dx_i, int dy_i) {
  double dx = static_cast<double>(dx_i) / 360 * 2 * M_PI;
  double dy = -static_cast<double>(dy_i) / 360 * 2 * M_PI;
  // std::cout << dx << " " << dy << std::endl;
  mat<3, 3> x_rotate;
  x_rotate.rows[0][0] = 1;
  x_rotate.rows[1][1] = cos(dx);
  x_rotate.rows[1][2] = sin(dx);
  x_rotate.rows[2][1] = -sin(dx);
  x_rotate.rows[2][2] = cos(dx);
  mat<3, 3> y_rotate;
  y_rotate.rows[1][1] = 1;
  y_rotate.rows[0][0] = cos(dy);
  y_rotate.rows[2][0] = sin(dy);
  y_rotate.rows[2][2] = cos(dy);
  y_rotate.rows[0][2] = -sin(dy);
  transform_matrix_ = x_rotate * y_rotate;
  camera_.SetPosition(transform_matrix_ * camera_.GetPosition());
}

void View::UpdateTriangles(const std::vector<Triangle>& triangles) {
  triangles_ = triangles;
  for(auto& i : triangles_) {
    i.vertex1 = i.vertex1 * 5;
    i.vertex2 = i.vertex2 * 5;
    i.vertex3 = i.vertex3 * 5;
  }
}
