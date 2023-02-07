#pragma once

#include <vector>

#include <QByteArray>

#include "Model/geometry.h"

/*
 * solid name
 * facet normal ni nj nk
 * outer loop
 * vertex v1x v1y v1z
 * vertex v2x v2y v2z
 * vertex v3x v3y v3z
 * endloop
 * endfacet
 * endsolid name
 */

class AsciiParser {
 public:
  static std::vector<Triangle> ParseModel(const QByteArray& data);

 private:
  class ArrayReader {
   public:
    explicit ArrayReader(const QByteArray& array);

    void SkipCurrentLine();
    void SkipUntilSpaceCharacter();
    void SkipUntilNonSpaceCharacter();
    void SkipUntilNextWord();

    bool Ended();

    Triangle ReadTriangle();
    Vec3f ParseVertex();
    Vec3f ParseFacetNormal();
    Vec3f ParseVec3f();

    float ParseFloat();

   private:
    const QByteArray& arr;
    int i;
  };
};
