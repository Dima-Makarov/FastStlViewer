#include "camera.h"

Camera::Camera() {
  orientation_ = position_;
  orientation_ = orientation_ * -1;
  orientation_.normalize();
}

const Vec3f& Camera::GetOrientation() const {
  return orientation_;
}

const Vec3f& Camera::GetPosition() const {
  return position_;
}

void Camera::SetPosition(const Vec3f& position) {
  position_ = position;
}
