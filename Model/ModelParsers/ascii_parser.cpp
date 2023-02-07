#include "ascii_parser.h"

#include <cctype>

#include "utils.h"

AsciiParser::ArrayReader::ArrayReader(const QByteArray& array) : arr(array), i(0) {}

void AsciiParser::ArrayReader::SkipCurrentLine() {
  while (!Ended() && arr[i] != '\n') {
    i++;
  }
  i++;
}

Triangle AsciiParser::ArrayReader::ReadTriangle() {
  /*
   * facet normal ni nj nk
   * outer loop
   * vertex v1x v1y v1z
   * vertex v2x v2y v2z
   * vertex v3x v3y v3z
   * endloop
   * endfacet
   */

  Vec3f normal = ParseFacetNormal();

  SkipCurrentLine(); // outer loop

  Vec3f v1 = ParseVertex();
  Vec3f v2 = ParseVertex();
  Vec3f v3 = ParseVertex();

  SkipCurrentLine(); // endloop
  SkipCurrentLine(); // endfacet

  return Triangle(normal, v1, v2, v3);
}

void AsciiParser::ArrayReader::SkipUntilSpaceCharacter() {
  while (!Ended() && !std::isspace(arr[i])) {
    i++;
  }
}

void AsciiParser::ArrayReader::SkipUntilNonSpaceCharacter() {
  while (!Ended() && std::isspace(arr[i])) {
    i++;
  }
}

void AsciiParser::ArrayReader::SkipUntilNextWord() {
  SkipUntilSpaceCharacter();
  SkipUntilNonSpaceCharacter();
}

bool AsciiParser::ArrayReader::Ended() {
  return i >= arr.size();
}

Vec3f AsciiParser::ArrayReader::ParseVertex() {
  SkipUntilNonSpaceCharacter(); // for spaces in the beginning of the line

  SkipUntilNextWord(); // vertex
  Vec3f result = ParseVec3f();
  SkipCurrentLine(); // new line

  return result;
}

Vec3f AsciiParser::ArrayReader::ParseFacetNormal() {
  SkipUntilNonSpaceCharacter(); // for spaces in the beginning of the line

  SkipUntilNextWord(); // facet
  SkipUntilNextWord(); // normal
  Vec3f result = ParseVec3f();
  SkipCurrentLine(); // new line

  return result.normalize();
}

Vec3f AsciiParser::ArrayReader::ParseVec3f() {
  SkipUntilNonSpaceCharacter();
  float ni = ParseFloat();
  SkipUntilNonSpaceCharacter(); // space
  float nj = ParseFloat();
  SkipUntilNonSpaceCharacter(); // space
  float nk = ParseFloat();

  return Vec3f{ni, nj, nk};
}

float AsciiParser::ArrayReader::ParseFloat() {
  int begin = i;
  SkipUntilSpaceCharacter();
  int end = i;
  float result = ::ParseFloatFromString(arr, begin, end);
  return result;
}

std::vector<Triangle> AsciiParser::ParseModel(const QByteArray& data) {
  ArrayReader reader(data);

  reader.SkipCurrentLine(); // solid name

  std::vector<Triangle> triangles;

  while (!reader.Ended()) {
    triangles.push_back(reader.ReadTriangle());
  }

  return triangles;
}
