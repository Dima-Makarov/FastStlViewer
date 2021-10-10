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
  painter->translate(painter->window().center() + pan_offset_);
  painter->drawEllipse(camera_.GetPosition().y * scale_,
                       camera_.GetPosition().x * scale_,
                       10 * scale_,
                       10 * scale_);
  painter->drawEllipse(-1, -1, 2, 2);
  for (auto& triangle: triangles_) {
    QLine l1(triangle.vertex1.y * scale_,
             triangle.vertex1.x * scale_,
             triangle.vertex2.y * scale_,
             triangle.vertex2.x * scale_);
    QLine l2(triangle.vertex2.y * scale_,
             triangle.vertex2.x * scale_,
             triangle.vertex3.y * scale_,
             triangle.vertex3.x * scale_);
    QLine l3(triangle.vertex3.y * scale_,
             triangle.vertex3.x * scale_,
             triangle.vertex1.y * scale_,
             triangle.vertex1.x * scale_);

    painter->drawLine(l1);
    painter->drawLine(l2);
    painter->drawLine(l3);
  }
}

const QPushButton& View::GetLoadFileButton() const {
  return load_file_;
}

void View::MouseRotate(int dx_i, int dy_i) {
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
  for (auto& triangle: triangles_) {
    triangle.vertex1 = transform_matrix_ * triangle.vertex1;
    triangle.vertex2 = transform_matrix_ * triangle.vertex2;
    triangle.vertex3 = transform_matrix_ * triangle.vertex3;
  }
  camera_.SetPosition(transform_matrix_ * camera_.GetPosition());
}

void View::UpdateTriangles(const std::vector<Triangle>& triangles) {
  triangles_ = triangles;
  for (auto& i: triangles_) {
    i.vertex1 = i.vertex1;
    i.vertex2 = i.vertex2;
    i.vertex3 = i.vertex3;
  }
}

void View::MousePan(int dx, int dy) {
  pan_offset_ = {pan_offset_.x() + dx, pan_offset_.y() + dy};
}

void View::MouseScale(double ds) {
  if (ds < 0) {
    scale_ /= 1.5;
  } else {
    scale_ *= 1.5;
  }
}


