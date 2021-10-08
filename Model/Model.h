
#pragma once

#include <QKeyEvent>
#include "geometry.h"

struct Triangle {
  Triangle(Vec3f n, Vec3f v1, Vec3f v2, Vec3f v3)
      : normal(n), vertex1(v1), vertex2(v2), vertex3(v3) {};
  Vec3f normal;
  Vec3f vertex1;
  Vec3f vertex2;
  Vec3f vertex3;
};

class Model : public QObject {
 Q_OBJECT

 public:
  Model();
  void Update(int millis);
  void HandleKeyPressEvent(QKeyEvent* event);
  void HandleKeyReleaseEvent(QKeyEvent* event);
  std::vector<Triangle> GetTriangles();
  void LoadModel(const QString& filepath);

 private:
  std::vector<Triangle> triangles_;
  int Parse32bitInt(int index);
  float Parse32bitfloat(int index);
  QByteArray stl_bytes_;
};



