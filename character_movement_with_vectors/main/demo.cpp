#include <iostream>

class Vector {
public:
  float x, y;
};

class Point {
public:
  Point addVector(Vector v);
  float x, y;
};

Point Point::addVector(Vector v) {
  Point new_p;
  new_p.x = x + v.x;
  new_p.y = y + v.y;
  return new_p;
};

int main(int argc, char *argv[]) {
  Point p; // (1, 0)
  p.x = 1;
  p.y = 0;

  Vector v; // (2, 0)
  v.x = 2;
  v.y = 0;

  Point result = p.addVector(v); // Position of Person B
  std::cout << "Result (" << result.x << ", " << result.y << ")\n";
  return 0;
}
