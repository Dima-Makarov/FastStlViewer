#include "utils.h"

#include <charconv>

int ParseInt32(const QByteArray& stl_bytes, int index) {
  int result;
  result = static_cast<unsigned char>(stl_bytes.at(index));
  result += static_cast<unsigned char>(stl_bytes.at(index + 1)) << 8;
  result += static_cast<unsigned char>(stl_bytes.at(index + 2)) << 16;
  result += static_cast<unsigned char>(stl_bytes.at(index + 3)) << 24;
  return result;
}

float ParseFloatFromBytes(const QByteArray& bytes, int index) {
  int result = 0;
  int i1 = static_cast<unsigned char>(bytes.at(index));
  int i2 = static_cast<unsigned char>(bytes.at(index + 1));
  int i3 = static_cast<unsigned char>(bytes.at(index + 2));
  int i4 = static_cast<unsigned char>(bytes.at(index + 3));

  result = i1;
  result += i2 << 8;
  result += i3 << 16;
  result += i4 << 24;
  float ans = *reinterpret_cast<float*>(&result);
  return ans;
}

float ParseFloatFromString(const QByteArray& chars, int begin, int end) {
  std::string s(chars.data() + begin, chars.data() + end);

  float result = atof(s.c_str());

  return result;
}
