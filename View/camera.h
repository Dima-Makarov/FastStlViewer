#pragma once

#include "Model/geometry.h"

class Camera {
 public:
  Camera();
  void SetPosition(const Vec3f& position);
  [[nodiscard]] const Vec3f& GetOrientation() const;
  [[nodiscard]] const Vec3f& GetPosition() const;
 private:
  Vec3f orientation_;
  Vec3f position_ {0,0,100}; //mm
};



