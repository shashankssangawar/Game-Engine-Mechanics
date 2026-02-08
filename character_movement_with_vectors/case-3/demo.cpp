#include <cmath>
#include <iostream>

class Point {
public:
  float x, y;
};

class Vector {
public:
  float findDistance() const;
  float findDistanceSq() const;
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

float Vector::findDistanceSq() const {
  float length;
  length = std::sqrt(x * x + y * y);
  return length;
};

int main(int argc, char *argv[]) {
  Point p1; // Person A (1, 0)
  p1.x = 1;
  p1.y = 0;

  Point p2; // Person B (3, 2)
  p2.x = 3;
  p2.y = 2;

  Point p3; // Person C (3, 0)
  p3.x = 3;
  p3.y = 0;

  // Distance travelled by Person A
  Vector v1;
  Vector vector1 = v1.findVector(p1, p2); // (2, 2)
  // float distance1 = vector1.findDistance(); // Compute Intensive
  float distance1sq = vector1.findDistanceSq();

  // Distance travelled by Person B
  Vector v2;
  Vector vector2 = v2.findVector(p3, p2); // (2, 2)
  // float distance2 = vector2.findDistance(); // Compute Intensive
  float distance2sq = vector2.findDistanceSq();

  std::cout << "Distance travelled by Person A (" << distance1sq
            << ") sq.units\n";
  std::cout << "Distance travelled by Person B (" << distance2sq
            << ") sq.units\n";

  if (distance1sq < distance2sq) {
    std::cout << "Person A travelled the shortest distance\n";
  } else if (distance2sq < distance1sq) {
    std::cout << "Person C travelled the shortest distance\n";
  } else {
    std::cout << "Both travelled the same distance\n";
  }
  return 0;
}
