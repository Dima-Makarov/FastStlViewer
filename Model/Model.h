
#pragma once

#include <QKeyEvent>
#include "model_loader.h"

class Model : public QObject {
 Q_OBJECT

 public:
  Model();
  void Update(int millis);
  void HandleKeyPressEvent(QKeyEvent* event);
  void HandleKeyReleaseEvent(QKeyEvent* event);
  const std::vector<Triangle>& GetTriangles();
  void LoadModel(const QString& filepath);

 private:
  std::vector<Triangle> triangles_;

  QByteArray stl_bytes_;
};



