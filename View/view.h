
#pragma once

#include <QPainter>
#include <QPushButton>
#include "Model/Model.h"
#include "camera.h"

class View {
 public:
  explicit View(QWidget* parent, Model* model);
  void Update(QPainter* painter);
  [[nodiscard]] const QPushButton& GetLoadFileButton() const;
  void MouseMove(int dx, int dy);
  void UpdateTriangles(const std::vector<Triangle>& triangles);

 private:
  static constexpr double kPixelToAngleCoefficient = 0.1;
  std::vector<Triangle> triangles_;
  mat<3,3> transform_matrix_;
  Camera camera_;
  QWidget* parent_;
  Model* model_;
  QPushButton load_file_;
};
