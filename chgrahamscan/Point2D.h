#ifndef __POINT2D_H__
#define __POINT2D_H__

class Point2D{
public:
  float x;
  float y;
  Point2D();
  Point2D(float _x, float _y);
  void print(bool printCR = true);
  bool operator==(const Point2D &P) const;
  bool operator<(Point2D P);
  Point2D  operator-(Point2D P);
};

#endif

