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
  Vector operator-(const Vector &other) const {
    return Vector(x - other.x, y - other.y);
  }
  Vector operator*(float scalar) const {
    return Vector(x * scalar, y * scalar);
  }
  Vector operator/(float scalar) const {
    return Vector(x / scalar, y / scalar);
  }
  Vector &operator+=(const Vector &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  float Length() const { return std::sqrt(x * x + y * y); }

  Vector Normalize() const {
    float len = Length();
    if (len == 0)
      return Vector(0, 0);
    return *this / len;
  }
};

// =====================
// Main
// =====================
int main() {
  InitWindow(800, 600, "Case 5: Unit Vector (Direction)");
  SetTargetFPS(60);

  Vector Player(400, 300); // P
  Vector Target(600, 200); // T
  float speed = 150.0f;    // Pixels per second

  bool draggingT = false;

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    Vector mp((float)GetMouseX(), (float)GetMouseY());

    // Drag Setup
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      if ((mp - Target).Length() < 20)
        draggingT = true;
    }
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
      draggingT = false;

    if (draggingT) {
      Target.x = mp.x;
      Target.y = mp.y;
    }

    // Logic
    Vector V = Target - Player; // Vector to Target
    Vector Dir = V.Normalize(); // Unit Vector (Direction)

    // Move if far enough (prevent jitter)
    if (V.Length() > 5.0f) {
      Vector Velocity = Dir * speed;
      Player += Velocity * dt;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Case 5: Moving towards Target (Unit Vector)", 20, 20, 20,
             DARKGRAY);
    DrawText("Drag the Red Target", 20, 50, 16, GRAY);

    // Draw Line to Target
    DrawLineEx({Player.x, Player.y}, {Target.x, Target.y}, 1.0f, LIGHTGRAY);

    // Draw Player
    DrawCircleV({Player.x, Player.y}, 20, BLUE);
    DrawText("Player", Player.x - 20, Player.y + 25, 10, BLUE);

    // Draw Target
    DrawCircleV({Target.x, Target.y}, 15, RED);
    DrawText("Target", Target.x - 20, Target.y - 25, 10, RED);

    // Draw Unit Vector (Visualized as a small yellow arrow from Player)
    // We scale it up for visibility (Unit length is 1 pixel, which is too
    // small)
    float vizScale = 50.0f;
    Vector VisualDir = Dir * vizScale;
    DrawLineEx({Player.x, Player.y},
               {Player.x + VisualDir.x, Player.y + VisualDir.y}, 4.0f, ORANGE);

    // Stats
    DrawText(TextFormat("Distance: %.0f", V.Length()), 20, 500, 20, BLACK);
    DrawText(TextFormat("Direction (Unit): (%.2f, %.2f)", Dir.x, Dir.y), 20,
             530, 20, BLACK);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
