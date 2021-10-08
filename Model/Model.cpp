
#include "Model.h"
#include <chrono>
#include <iostream>
#include <utility>

void Model::Update(int millis) {
}

void Model::HandleKeyPressEvent(QKeyEvent* event) {
}

void Model::HandleKeyReleaseEvent(QKeyEvent* event) {
}

Model::Model() {
}

int Model::Parse32bitInt(int index) {
  int result;
  result = static_cast<unsigned char>(stl_bytes_.at(index));
  result += static_cast<unsigned char>(stl_bytes_.at(index + 1)) << 8;
  result += static_cast<unsigned char>(stl_bytes_.at(index + 2)) << 16;
  result += static_cast<unsigned char>(stl_bytes_.at(index + 3)) << 24;
  return result;
}

float Model::Parse32bitfloat(int index) {
  int result = 0;
  int i1 = static_cast<unsigned char>(stl_bytes_.at(index));
  int i2 = static_cast<unsigned char>(stl_bytes_.at(index + 1));
  int i3 = static_cast<unsigned char>(stl_bytes_.at(index + 2));
  int i4 = static_cast<unsigned char>(stl_bytes_.at(index + 3));

  result = i1;
  result += i2 << 8;
  result += i3 << 16;
  result += i4 << 24;
  float ans = *reinterpret_cast<float*>(&result);
  return ans;
}

std::vector<Triangle> Model::GetTriangles() {
  return triangles_;
}

void Model::LoadModel(const QString& filepath) {
  if(filepath.isEmpty()) {
    return;
  }
  triangles_.clear();
  QFile file(filepath);
  file.open(QIODevice::ReadOnly);
  stl_bytes_ = file.readAll();
  int index = 0;
  index += 80;
  int number_of_faces = Parse32bitInt(index);
  index += 4;
  std::cout << number_of_faces << std::endl;
  triangles_.reserve(number_of_faces);
  for (int i = 0; i < number_of_faces; i++) {
    float normal_x = Parse32bitfloat(index);
    index += 4;
    float normal_y = Parse32bitfloat(index);
    index += 4;
    float normal_z = Parse32bitfloat(index);
    index += 4;
    float vertex_1_x = Parse32bitfloat(index);
    index += 4;
    float vertex_1_y = Parse32bitfloat(index);
    index += 4;
    float vertex_1_z = Parse32bitfloat(index);
    index += 4;
    float vertex_2_x = Parse32bitfloat(index);
    index += 4;
    float vertex_2_y = Parse32bitfloat(index);
    index += 4;
    float vertex_2_z = Parse32bitfloat(index);
    index += 4;
    float vertex_3_x = Parse32bitfloat(index);
    index += 4;
    float vertex_3_y = Parse32bitfloat(index);
    index += 4;
    float vertex_3_z = Parse32bitfloat(index);
    index += 4;
    index += 2;
    triangles_.emplace_back(Vec3f(normal_x, normal_y, normal_z).normalize(),
                            Vec3f(vertex_1_x, vertex_1_y, vertex_1_z),
                            Vec3f(vertex_2_x, vertex_2_y, vertex_2_z),
                            Vec3f(vertex_3_x, vertex_3_y, vertex_3_z));
  }
}
