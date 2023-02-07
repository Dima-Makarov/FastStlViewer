#ifndef _UTILS_H_
#define _UTILS_H_

#include <QByteArray>

int ParseInt32(const QByteArray& arr, int index);
float ParseFloatFromBytes(const QByteArray& bytes, int index);
float ParseFloatFromString(const QByteArray& chars, int begin, int end);

#endif //_UTILS_H_
