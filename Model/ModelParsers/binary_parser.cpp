#include "binary_parser.h"

#include "utils.h"

std::vector<Triangle> BinaryParser::ParseModel(const QByteArray& data) {
  int index = 0;
  index += 80;
  int number_of_faces = ParseInt32(data,index);
  index += 4;

  std::vector<Triangle> triangles;
  triangles.reserve(number_of_faces);
  for (int i = 0; i < number_of_faces; i++) {
    std::vector<float> floats(12);
    for(size_t j = 0; j < 12; j++) {
      floats[j] = ParseFloatFromBytes(data, index);
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
