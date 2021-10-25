#include "Model.h"

void Model::Update(int millis) {
}

void Model::HandleKeyPressEvent(QKeyEvent* event) {
}

void Model::HandleKeyReleaseEvent(QKeyEvent* event) {
}

Model::Model() = default;

const std::vector<Triangle>& Model::GetTriangles() {
  return triangles_;
}

void Model::LoadModel(const QString& filepath) {
  triangles_ = ModelLoader::LoadModel(filepath);
  Vec3f center_point;
  double minimum_z = 1000;
  for (auto& triangle: triangles_) {
    center_point = center_point + triangle.vertex1;
    center_point = center_point + triangle.vertex2;
    center_point = center_point + triangle.vertex3;
    if(triangle.vertex1.z < minimum_z) {
      minimum_z = triangle.vertex1.z;
    }
    if(triangle.vertex2.z < minimum_z) {
      minimum_z = triangle.vertex2.z;
    }
    if(triangle.vertex3.z < minimum_z) {
      minimum_z = triangle.vertex3.z;
    }
  }
  center_point.z = minimum_z;
  center_point.x /= triangles_.size()*3;
  center_point.y /= triangles_.size()*3;
  for (auto& triangle: triangles_) {
    triangle.vertex1 = triangle.vertex1 - center_point;
    triangle.vertex2 = triangle.vertex2 - center_point;
    triangle.vertex3 = triangle.vertex3 - center_point;
  }
}
