#include <QFile>
#include "model_loader.h"
std::vector<Triangle> ModelLoader::LoadModel(const QString& filepath) {
  std::vector<Triangle> triangles;
  if(filepath.isEmpty()) {
    return triangles;
  }
  QFile file(filepath);
  file.open(QIODevice::ReadOnly);
  QByteArray stl_bytes = file.readAll();
  int index = 0;
  index += 80;
  int number_of_faces = Parse32bitInt(stl_bytes,index);
  index += 4;
  triangles.reserve(number_of_faces);
  for (int i = 0; i < number_of_faces; i++) {
    std::vector<float> floats(12);
    for(size_t j = 0; j < 12; j++) {
      floats[j] = Parse32bitfloat(stl_bytes, index);
      index += 4;
    }
    index += 2;
    triangles.emplace_back(Vec3f(floats[0], floats[1], floats[2]).normalize(),
                            Vec3f(floats[3], floats[4], floats[5]),
                            Vec3f(floats[6], floats[7], floats[8]),
                            Vec3f(floats[9], floats[10], floats[11]));
  }
  return triangles;
}

int ModelLoader::Parse32bitInt(const QByteArray& stl_bytes, int index) {
  int result;
  result = static_cast<unsigned char>(stl_bytes.at(index));
  result += static_cast<unsigned char>(stl_bytes.at(index + 1)) << 8;
  result += static_cast<unsigned char>(stl_bytes.at(index + 2)) << 16;
  result += static_cast<unsigned char>(stl_bytes.at(index + 3)) << 24;
  return result;
}

float ModelLoader::Parse32bitfloat(const QByteArray& stl_bytes, int index) {
  int result = 0;
  int i1 = static_cast<unsigned char>(stl_bytes.at(index));
  int i2 = static_cast<unsigned char>(stl_bytes.at(index + 1));
  int i3 = static_cast<unsigned char>(stl_bytes.at(index + 2));
  int i4 = static_cast<unsigned char>(stl_bytes.at(index + 3));

  result = i1;
  result += i2 << 8;
  result += i3 << 16;
  result += i4 << 24;
  float ans = *reinterpret_cast<float*>(&result);
  return ans;
}