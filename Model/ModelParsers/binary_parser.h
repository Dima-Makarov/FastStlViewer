#pragma once

#include <vector>

#include <QByteArray>

#include "Model/geometry.h"

class BinaryParser {
 public:
  static std::vector<Triangle> ParseModel(const QByteArray& data);
};
