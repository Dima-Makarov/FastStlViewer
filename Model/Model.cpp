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
}
