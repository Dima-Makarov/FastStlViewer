#pragma once

struct DefaultPlane {
  DefaultPlane() {
    grid_lines.reserve(100);
    for (int i = -10; i < 10; i++) {
      grid_lines.emplace_back(Vec3f(-100, i * 10, 0), Vec3f(100, i * 10, 0));
      grid_lines.emplace_back(Vec3f(i * 10, -100, 0), Vec3f(i * 10, 100, 0));
    }
  }

  Vec3f corner_1_ = {-100, 100, 0};
  Vec3f corner_2_ = {100, 100, 0};
  Vec3f corner_3_ = {100, -100, 0};
  Vec3f corner_4_ = {-100, -100, 0};
  std::vector<std::pair<Vec3f, Vec3f>> grid_lines;
  std::pair<Vec3f, Vec3f> x_axis{Vec3f(-100,-100,0),Vec3f(-70,-100,0)};
  std::pair<Vec3f, Vec3f> y_axis{Vec3f(-100,-100,0),Vec3f(-100,-70,0)};
  std::pair<Vec3f, Vec3f> z_axis{Vec3f(-100,-100,0),Vec3f(-100,-100,30)};

  friend DefaultPlane operator*(mat<3, 3> t_m, const DefaultPlane& dp) {
    DefaultPlane default_plane;
    default_plane.corner_1_ = t_m * dp.corner_1_;
    default_plane.corner_2_ = t_m * dp.corner_2_;
    default_plane.corner_3_ = t_m * dp.corner_3_;
    default_plane.corner_4_ = t_m * dp.corner_4_;
    for (size_t i = 0; i < dp.grid_lines.size(); ++i) {
      default_plane.grid_lines[i] =
          std::make_pair(t_m * dp.grid_lines[i].first, t_m * dp.grid_lines[i].second);
    }
    default_plane.x_axis.first = t_m * dp.x_axis.first;
    default_plane.x_axis.second = t_m * dp.x_axis.second;
    default_plane.y_axis.first = t_m * dp.y_axis.first;
    default_plane.y_axis.second = t_m * dp.y_axis.second;
    default_plane.z_axis.first = t_m * dp.z_axis.first;
    default_plane.z_axis.second= t_m * dp.z_axis.second;

    return default_plane;
  }
};
