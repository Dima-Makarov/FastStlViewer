#include "model_loader.h"

#include <QFile>

#include "ModelParsers/ascii_parser.h"
#include "ModelParsers/binary_parser.h"

bool ModelLoader::IsAsciiData(const QByteArray& data) {
  std::array ascii_header = {'s', 'o', 'l', 'i', 'd', ' '};

  for (int i = 0 ; i < ascii_header.size() ; ++i) {
    if (data[i] != ascii_header[i]) {
      return false;
    }
  }

  return true;
}

std::vector<Triangle> ModelLoader::LoadModel(const QString& filepath) {
  QFile file(filepath);

  if(!file.exists()) {
    throw std::invalid_argument("File doesn't exists");
  }

  file.open(QIODevice::ReadOnly);
  QByteArray stl_bytes = file.readAll();

  if (ModelLoader::IsAsciiData(stl_bytes)) {
    return AsciiParser::ParseModel(stl_bytes);
  } else {
    return BinaryParser::ParseModel(stl_bytes);
  }
}
