#include <cmath>
#include <iostream>

class Point {
public:
  Point() {}
  Point(float X, float Y) {
    x = X;
    y = Y;
  }
  float x, y;
};

class Vector {
public:
  Vector() {}
  Vector(float X, float Y) {
    x = X;
    y = Y;
  }
  float findDistance() const;
  Vector operator+(const Vector &v) const;
  Vector operator-(const Vector &v) const;
  float x, y;
};

float Vector::findDistance() const {
  float length;
  length = std::sqrt(x * x + y * y);
  return length;
};

// Operator Overloads
Vector Vector::operator+(const Vector &v) const {
  Vector result_vector;
  result_vector.x = x + v.x;
  result_vector.y = y + v.y;
  return result_vector;
}

Vector Vector::operator-(const Vector &v) const {
  Vector result_vector;
  result_vector.x = x - v.x;
  result_vector.y = y - v.y;
  return result_vector;
}

int main(int argc, char *argv[]) {
  Vector vector1(4, 0);
  Vector vector2(0, -5);
  Vector result_vector = vector1 + vector2;
  std::cout << "New Velocity: (" << result_vector.x << ", " << result_vector.y
            << ") \n";
  std::cout << "New Distance: " << result_vector.findDistance() << "";
  return 0;
}
