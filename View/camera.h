#pragma once

#include "Model/geometry.h"

class Camera {
 public:
  Camera();
  void SetPosition(const Vec3f& position);
  const Vec3f& GetOrientation() const;
  const Vec3f& GetPosition() const;
 private:
  Vec3f orientation_;
  Vec3f position_ {100,100,100}; //mm
};



