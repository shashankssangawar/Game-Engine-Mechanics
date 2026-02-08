#include <cmath>
#include <iostream>

class Point {
public:
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
  float findDistanceSq() const;

  Vector operator*(float scale) const;
  Vector operator/(float scale) const;
  float x, y;
};

float Vector::findDistance() const {
  float length;
  length = std::sqrt(x * x + y * y);
  return length;
};

float Vector::findDistanceSq() const {
  float length;
  length = std::sqrt(x * x + y * y);
  return length;
};

// Operator Overloads
Vector Vector::operator*(float scale) const {
  Vector scaled_vector;
  scaled_vector.x = x * scale;
  scaled_vector.y = y * scale;
  return scaled_vector;
}

Vector Vector::operator/(float scale) const {
  Vector scaled_vector;
  scaled_vector.x = x / scale;
  scaled_vector.y = y / scale;
  return scaled_vector;
}

int main(int argc, char *argv[]) {

  Vector initial_vector(2, 4);
  std::cout << "Initial Speed: " << initial_vector.findDistance() << '\n';

  Vector doubled_vector = initial_vector * 2;
  std::cout << "Doubled Speed: " << doubled_vector.findDistance() << '\n';

  Vector halved_vector = initial_vector / 2;
  std::cout << "Halved Speed: " << halved_vector.findDistance() << '\n';

  return 0;
}
