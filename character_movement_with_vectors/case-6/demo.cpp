#include "raylib.h"
#include <cmath>

// =====================
// Vector Class
// =====================
class Vector {
public:
  float x, y;

  Vector() : x(0), y(0) {}
  Vector(float X, float Y) : x(X), y(Y) {}

  Vector operator+(const Vector &other) const {
    return Vector(x + other.x, y + other.y);
  }
  Vector operator*(float scalar) const {
    return Vector(x * scalar, y * scalar);
  }
  Vector &operator+=(const Vector &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  float Length() const { return std::sqrt(x * x + y * y); }
};

// =====================
// Main
// =====================
int main() {
  InitWindow(800, 600, "Case 6: Vector Addition (Diagonal)");
  SetTargetFPS(60);

  Vector P(100, 100);
  float speed = 200.0f;

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    Vector Vx(0, 0);
    Vector Vy(0, 0);

    // Input
    if (IsKeyDown(KEY_RIGHT))
      Vx.x = speed;
    if (IsKeyDown(KEY_LEFT))
      Vx.x = -speed;
    if (IsKeyDown(KEY_DOWN))
      Vy.y = speed;
    if (IsKeyDown(KEY_UP))
      Vy.y = -speed;

    // Vector Addition
    Vector Vsum = Vx + Vy;

    // Apply Movement
    P += Vsum * dt;

    // Reset
    if (P.x > 800)
      P.x = 0;
    if (P.x < 0)
      P.x = 800;
    if (P.y > 600)
      P.y = 0;
    if (P.y < 0)
      P.y = 600;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Case 6: Vector Addition", 20, 20, 20, DARKGRAY);
    DrawText("Use Arrow Keys to move", 20, 50, 16, GRAY);

    // Draw Player
    DrawCircleV({P.x, P.y}, 20, BLUE);
    DrawText("P", (int)P.x - 5, (int)P.y - 40, 20, BLUE);

    // Visualizing Component Vectors attached to Player
    if (Vx.x != 0) {
      DrawLineEx({P.x, P.y}, {P.x + Vx.x, P.y}, 2.0f, RED);
      DrawText("Vx", (int)(P.x + Vx.x / 2), (int)(P.y - 15), 10, RED);
    }
    if (Vy.y != 0) {
      DrawLineEx({P.x, P.y}, {P.x, P.y + Vy.y}, 2.0f, GREEN);
      DrawText("Vy", (int)(P.x + 15), (int)(P.y + Vy.y / 2), 10, GREEN);
    }

    // Visualizing Resultant Vector
    if (Vsum.Length() > 0) {
      DrawLineEx({P.x, P.y}, {P.x + Vsum.x, P.y + Vsum.y}, 4.0f, BLACK);
      // Resultant Arrow Head
      DrawTriangle(
          {P.x + Vsum.x, P.y + Vsum.y}, {P.x + Vsum.x - 5, P.y + Vsum.y - 5},
          {P.x + Vsum.x - 5, P.y + Vsum.y + 5}, // Rough approximation of arrow
          BLACK);

      // Show formula
      // We only show it if moving diagonally
      if (Vx.x != 0 && Vy.y != 0) {
        DrawText("Vsum = Vx + Vy", 20, 550, 20, BLACK);
      }
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
