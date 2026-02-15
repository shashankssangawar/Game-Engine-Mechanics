#include "raylib.h"

// =====================
// Vector Class
// =====================
class Vector {
public:
  float x, y;

  Vector() : x(0), y(0) {}
  Vector(float X, float Y) : x(X), y(Y) {}

  // Vector operations
  Vector operator+(const Vector &other) const {
    return Vector(x + other.x, y + other.y);
  }
  Vector operator-(const Vector &other) const {
    return Vector(x - other.x, y - other.y);
  }
  Vector operator*(float scalar) const {
    return Vector(x * scalar, y * scalar);
  }

  // Add and assign
  Vector &operator+=(const Vector &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
};

// =====================
// Main
// =====================
int main() {
  // Initialization
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Movement Formula Demo");
  SetTargetFPS(60);

  // Initial State
  Vector P(100, 300); // Position
  Vector V(150, 0);   // Velocity (pixels per second)

  while (!WindowShouldClose()) {
    // Update
    float dt = GetFrameTime(); // Delta Time

    // P' = P + (V * dt)
    P += V * dt;

    // Reset if off screen to loop the demo
    if (P.x > screenWidth + 20)
      P.x = -20;

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Formula: P' = P + (V * dt)", 20, 20, 20, DARKGRAY);
    DrawText("(New Position = Old Position + Velocity * Time)", 20, 50, 16,
             GRAY);

    // Draw Player (P)
    DrawCircle((int)P.x, (int)P.y, 20, BLUE);
    DrawText("P", (int)P.x - 5, (int)P.y - 40, 20, BLUE);

    // Draw Velocity Vector (V)
    // We draw it starting from P to visualize direction
    DrawLineEx({P.x, P.y}, {P.x + V.x, P.y + V.y}, 3.0f, RED);
    DrawTriangle({P.x + V.x, P.y + V.y}, {P.x + V.x - 10, P.y + V.y - 5},
                 {P.x + V.x - 10, P.y + V.y + 5}, RED);
    DrawText("V", (int)(P.x + V.x / 2), (int)(P.y + V.y / 2) - 20, 20, RED);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
