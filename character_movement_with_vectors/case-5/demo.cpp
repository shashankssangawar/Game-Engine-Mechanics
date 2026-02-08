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
  Vector NormalizeVector() const;
  Vector operator/(float scale) const;
  float x, y;
};

float Vector::findDistance() const {
  float length;
  length = std::sqrt(x * x + y * y);
  return length;
};

// Operator Overloads
Vector Vector::operator/(float scale) const {
  Vector scaled_vector;
  scaled_vector.x = x / scale;
  scaled_vector.y = y / scale;
  return scaled_vector;
}

Vector Vector::NormalizeVector() const {
  Vector normalized_vector;
  normalized_vector = (*this) / findDistance();
  return normalized_vector;
};

int main(int argc, char *argv[]) {
  Point p1(1, 2);
  Point p2(3, 4);

  Vector vector;
  vector.x = p1.x - p2.x;
  vector.y = p1.y - p2.y;

  Vector normalized_vector = vector.NormalizeVector();
  std::cout << "View Vector: (" << normalized_vector.x << ", "
            << normalized_vector.y << ")\n";
  std::cout << "View Vector Length: " << normalized_vector.findDistance()
            << "\n";
  return 0;
}
