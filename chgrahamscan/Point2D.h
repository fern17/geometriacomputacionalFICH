#ifndef __POINT2D_H__
#define __POINT2D_H__

class Point2D{
public:
  float x;
  float y;
  Point2D();
  Point2D(float _x, float _y);
  void print();
  bool operator==(Point2D P);
};

#endif

