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

void View::DrawDefaultPolygon(QPainter* painter) {
  painter->save();
  QPolygonF default_polygon;
  DefaultPlane default_plane;
  default_plane = transform_matrix_ * default_plane;
  default_polygon << QPointF(default_plane.corner_1_.y * scale_, default_plane.corner_1_.x * scale_)
                  << QPointF(default_plane.corner_2_.y * scale_, default_plane.corner_2_.x * scale_)
                  << QPointF(default_plane.corner_3_.y * scale_, default_plane.corner_3_.x * scale_)
                  << QPointF(default_plane.corner_4_.y * scale_,
                             default_plane.corner_4_.x * scale_);
  painter->setBrush(QBrush(QColor(133, 133, 133)));
  painter->drawPolygon(default_polygon);
  painter->setPen(QColor(100, 100, 100));
  for (const auto& i: default_plane.grid_lines) {
    painter->drawLine(i.second.y * scale_,
                      i.second.x * scale_,
                      i.first.y * scale_,
                      i.first.x * scale_);
  }
  painter->setPen(QPen(QBrush(QColor(255, 0, 0)),5));
  painter->drawLine(default_plane.x_axis.first.y * scale_,
                    default_plane.x_axis.first.x * scale_,
                    default_plane.x_axis.second.y * scale_,
                    default_plane.x_axis.second.x * scale_);
  painter->setPen(QPen(QBrush(QColor(0, 255, 0)),5));
  painter->drawLine(default_plane.y_axis.first.y * scale_,
                    default_plane.y_axis.first.x * scale_,
                    default_plane.y_axis.second.y * scale_,
                    default_plane.y_axis.second.x * scale_);
  painter->setPen(QPen(QBrush(QColor(0, 0, 255)),5));
  painter->drawLine(default_plane.z_axis.first.y * scale_,
                    default_plane.z_axis.first.x * scale_,
                    default_plane.z_axis.second.y * scale_,
                    default_plane.z_axis.second.x * scale_);
  painter->restore();
}

void View::Update(QPainter* painter) {
  painter->translate(painter->window().center() + pan_offset_);
  DrawDefaultPolygon(painter);
  DrawModel(painter);
}

const QPushButton& View::GetLoadFileButton() const {
  return load_file_;
}

void View::MouseRotate(int dx_i, int dy_i) {
  double dx = -static_cast<double>(dx_i) / 360 * 2 * M_PI;
  double dy = -static_cast<double>(dy_i) / 360 * 2 * M_PI;
  dx /= 3;
  dy /= 3;
  mat<3, 3> y_rotate;
  y_rotate.rows[1][1] = 1;
  y_rotate.rows[0][0] = cos(dy);
  y_rotate.rows[2][0] = sin(dy);
  y_rotate.rows[2][2] = cos(dy);
  y_rotate.rows[0][2] = -sin(dy);
  transform_matrix_ = y_rotate * transform_matrix_;

  Vec3f vertical(0, 0, 1);
  vertical = transform_matrix_ * vertical;
  double x = vertical.x;
  double y = vertical.y;
  double z = vertical.z;
  mat<3, 3> z_rotate;
  z_rotate.rows[0][0] = cos(dx) + (1 - cos(dx)) * x * x;
  z_rotate.rows[1][0] = (1 - cos(dx)) * x * y - (sin(dx) * z);
  z_rotate.rows[2][0] = (1 - cos(dx)) * x * z + sin(dx) * y;
  z_rotate.rows[0][1] = (1 - cos(dx)) * y * z + sin(dx) * z;
  z_rotate.rows[1][1] = cos(dx) + (1 - cos(dx)) * y * y;
  z_rotate.rows[2][1] = (1 - cos(dx)) * y * z - sin(dx) * x;
  z_rotate.rows[0][2] = (1 - cos(dx)) * z * x - sin(dx) * y;
  z_rotate.rows[1][2] = (1 - cos(dx)) * z * y + sin(dx) * x;
  z_rotate.rows[2][2] = cos(dx) + (1 - cos(dx)) * z * z;
  transform_matrix_ = z_rotate * transform_matrix_;
}

void View::UpdateTriangles(const std::vector<Triangle>& triangles) {
  triangles_ = triangles;
}

void View::MousePan(int dx, int dy) {
  pan_offset_ = {pan_offset_.x() + dx, pan_offset_.y() + dy};
}

void View::MouseScale(double ds, QPointF cursor_position, QRect geom) {
  QPointF win_center = {static_cast<qreal>(-geom.left() + geom.right()) / 2,
                        static_cast<qreal>(-geom.top() + geom.bottom()) / 2};
  QPointF pos = win_center + pan_offset_ - cursor_position;
  if (ds < 0) {
    scale_ /= 1.5;
    pos /= 3;
    pos *= -1;
  } else {
    scale_ *= 1.5;
    pos *= 0.5;
  }
  MousePan(static_cast<int>(pos.x()), static_cast<int>(pos.y()));
}

void View::DrawModel(QPainter* painter) {
  Vec3f camera(0, 0, 1);
  for (auto triangle: triangles_) {
    triangle.normal = transform_matrix_ * triangle.normal;
    triangle.vertex1 = transform_matrix_ * triangle.vertex1;
    triangle.vertex2 = transform_matrix_ * triangle.vertex2;
    triangle.vertex3 = transform_matrix_ * triangle.vertex3;
    double intensity = triangle.normal * camera;
    if (intensity > 0) {
      QColor color;
      color.setHsv(21, 200, intensity * 155 + 100);
      QPolygonF polygon;
      polygon << QPointF(triangle.vertex1.y * scale_, triangle.vertex1.x * scale_)
              << QPointF(triangle.vertex2.y * scale_, triangle.vertex2.x * scale_)
              << QPointF(triangle.vertex3.y * scale_, triangle.vertex3.x * scale_);
      painter->setBrush(QBrush(color));
      painter->setPen(color);
      painter->drawPolygon(polygon);
    }
  }
}


