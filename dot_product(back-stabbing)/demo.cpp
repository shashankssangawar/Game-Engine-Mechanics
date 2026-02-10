#include <cmath>
#include <iostream>

// --------------------
// Point = position in space
// --------------------
class Point {
public:
  Point() : x(0), y(0) {}
  Point(float X, float Y) : x(X), y(Y) {}
  float x, y;
};

// --------------------
// Vector = direction + magnitude
// --------------------
class Vector {
public:
  Vector() : x(0), y(0) {}
  Vector(float X, float Y) : x(X), y(Y) {}

  float findDistance() const { return std::sqrt(x * x + y * y); }

  Vector NormalizeVector() const {
    float len = findDistance();
    if (len == 0)
      return Vector(0, 0);
    return (*this) / len;
  }

  float Dot(const Vector &other) const { return x * other.x + y * other.y; }

  // 2D cross product (returns scalar)
  float Cross(const Vector &other) const { return x * other.y - y * other.x; }

  Vector operator/(float scale) const { return Vector(x / scale, y / scale); }

  float x, y;
};

int main() {

  // --------------------
  // World positions
  // --------------------
  Point playerPos(2, 2);
  Point enemyPos(1, 1);

  // --------------------
  // Player facing direction (dynamic in real games)
  // --------------------
  Vector playerFacing(0, 1); // facing right
  playerFacing = playerFacing.NormalizeVector();

  // --------------------
  // Direction from player to enemy
  // --------------------
  Vector toEnemy(enemyPos.x - playerPos.x, enemyPos.y - playerPos.y);
  toEnemy = toEnemy.NormalizeVector();

  // --------------------
  // Dot product: front / back
  // --------------------
  float dot = playerFacing.Dot(toEnemy);

  // --------------------
  // Cross product: left / right
  // --------------------
  float cross = playerFacing.Cross(toEnemy);

  // --------------------
  // Backstab logic
  // --------------------
  if (dot < -0.5) {
    std::cout << "BACKSTAB! Enemy is behind the player.\n";
  } else {
    std::cout << "No backstab. Enemy is ";

    if (dot > 0.5)
      std::cout << "in front ";
    else
      std::cout << "to the side ";

    if (cross > 0)
      std::cout << "on the LEFT.\n";
    else
      std::cout << "on the RIGHT.\n";
  }

  return 0;
}
