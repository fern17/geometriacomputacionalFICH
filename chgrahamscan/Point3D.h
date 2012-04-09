#ifndef __POINT3D_H__
#define __POINT3D_H__
#include "Point2D.h"

class Point3D{
public:
  float x;
  float y;
  float z;
  Point3D();
  Point3D(float _x, float _y, float _z);
  Point3D(Point2D P);
  void print();
  bool operator==(Point3D P);
  Point3D  operator-(Point3D P);
};

#endif

