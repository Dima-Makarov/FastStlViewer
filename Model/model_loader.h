#pragma once

#include <vector>

#include <QString>

#include "Model/geometry.h"
#include "utils.h"

class ModelLoader {
 public:
  static std::vector<Triangle> LoadModel(const QString& filepath);

 private:
  static bool IsAsciiData(const QByteArray& data);
};
