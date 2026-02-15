#include "raylib.h"
#include <cmath>
#include <cstdio>

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
  InitWindow(800, 600, "Case 4: Vector Scaling");
  SetTargetFPS(60);

  Vector P(100, 300);
  Vector InitialV(100, 0); // Base velocity
  float scale = 1.0f;

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    // Input to scale velocity
    if (IsKeyDown(KEY_UP))
      scale += 1.0f * dt;
    if (IsKeyDown(KEY_DOWN))
      scale -= 1.0f * dt;
    if (scale < 0)
      scale = 0; // Prevent negative speed for this demo

    // Calculate Scaled Vector
    Vector V = InitialV * scale;

    // Update Position
    P += V * dt;

    // Reset if off screen
    if (P.x > 800 + 20)
      P.x = -20;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Case 4: Vector Scaling (Speed Control)", 20, 20, 20, DARKGRAY);
    DrawText("Hold UP to speed up, DOWN to slow down", 20, 50, 16, GRAY);

    // Draw Player
    DrawCircleV({P.x, P.y}, 20, BLUE);
    DrawText("P", (int)P.x - 5, (int)P.y - 40, 20, BLUE);

    // Draw Velocity Vector
    if (scale > 0) {
      DrawLineEx({P.x, P.y}, {P.x + V.x, P.y + V.y}, 3.0f, RED);
      // Arrow head
      DrawTriangle({P.x + V.x, P.y + V.y}, {P.x + V.x - 10, P.y + V.y - 5},
                   {P.x + V.x - 10, P.y + V.y + 5}, RED);
    }

    char buffer[100];
    sprintf(buffer, "Scale (k): %.2f", scale);
    DrawText(buffer, 20, 500, 20, BLACK);

    sprintf(buffer, "Speed (|V|): %.0f pixels/sec", V.Length());
    DrawText(buffer, 20, 530, 20, BLACK);

    DrawText("V' = k * V", 20, 560, 20, DARKBLUE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
