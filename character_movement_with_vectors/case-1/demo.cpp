#include <iostream>

class Point {
public:
  float x, y;
};

class Vector {
public:
  Vector findVector(Point a, Point b);
  float x, y;
};

Vector Vector::findVector(Point a, Point b) {
  Vector vector;
  vector.x = b.x - a.x;
  vector.y = b.y - a.y;
  return vector;
};

int main(int argc, char *argv[]) {
  Point p1; // (1, 0)
  p1.x = 1;
  p1.y = 0;

  Point p2; // (3, 0)
  p2.x = 3;
  p2.y = 0;

  Vector v;

  Vector result = v.findVector(p1, p2);
  std::cout << "Result (" << result.x << ", " << result.y << ")\n";
  return 0;
}
