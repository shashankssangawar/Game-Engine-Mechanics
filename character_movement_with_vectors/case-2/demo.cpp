#include <cmath>
#include <iostream>

class Point {
public:
  float x, y;
};

class Vector {
public:
  float findDistance() const;
  Vector findVector(Point a, Point b);
  float x, y;
};

Vector Vector::findVector(Point a, Point b) {
  Vector vector;
  vector.x = b.x - a.x;
  vector.y = b.y - a.y;
  return vector;
};

float Vector::findDistance() const {
  float length;
  length = std::sqrt(x * x + y * y);
  return length;
};

int main(int argc, char *argv[]) {
  Point p1; // (1, 0)
  p1.x = 1;
  p1.y = 0;

  Point p2; // (3, 2)
  p2.x = 3;
  p2.y = 2;

  Vector v;
  Vector vector = v.findVector(p1, p2); // (2, 2)
  float result = vector.findDistance();
  std::cout << "Result (" << result << ") units\n";
  return 0;
}
