#pragma once

#include <vector>
#include <QString>
#include "geometry.h"

struct Triangle {
  Triangle(Vec3f n, Vec3f v1, Vec3f v2, Vec3f v3)
      : normal(n), vertex1(v1), vertex2(v2), vertex3(v3) {};
  Vec3f normal;
  Vec3f vertex1;
  Vec3f vertex2;
  Vec3f vertex3;
};

class ModelLoader {
 public:
  static std::vector<Triangle> LoadModel(const QString& filepath);
 private:
  static int Parse32bitInt(const QByteArray& stl_bytes, int index);
  static float Parse32bitfloat(const QByteArray& stl_bytes, int index);
};
