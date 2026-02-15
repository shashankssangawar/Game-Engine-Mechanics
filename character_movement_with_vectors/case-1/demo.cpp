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

  Vector operator-(const Vector &other) const {
    return Vector(x - other.x, y - other.y);
  }
  float Length() const { return std::sqrt(x * x + y * y); }
};

// =====================
// Main
// =====================
int main() {
  InitWindow(800, 600, "Case 1: Finding Vector");
  SetTargetFPS(60);

  // Points
  Vector A(200, 300); // Start
  Vector B(600, 300); // End

  // Interaction
  bool draggingA = false;
  bool draggingB = false;

  while (!WindowShouldClose()) {
    Vector mp(GetMouseX(), GetMouseY());

    // Dragging Logic
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      if (Vector(mp.x - A.x, mp.y - A.y).Length() < 20)
        draggingA = true;
      else if (Vector(mp.x - B.x, mp.y - B.y).Length() < 20)
        draggingB = true;
    }
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
      draggingA = false;
      draggingB = false;
    }

    if (draggingA) {
      A.x = mp.x;
      A.y = mp.y;
    }
    if (draggingB) {
      B.x = mp.x;
      B.y = mp.y;
    }

    // Calculate Vector V = B - A
    Vector V = B - A;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Case 1: Finding the Vector", 20, 20, 20, DARKGRAY);
    DrawText("Drag points A and B", 20, 50, 16, GRAY);

    char buffer[100];
    sprintf(buffer, "Formula: V = B - A = (%.0f, %.0f)", V.x, V.y);
    DrawText(buffer, 20, 80, 20, BLACK);

    // Draw Vector Line
    DrawLineEx({A.x, A.y}, {B.x, B.y}, 3.0f, GREEN);

    // Draw Arrow Head
    // Only if points are not same
    if (V.Length() > 0) {
      // Simple arrow logic matching rotation
      // Could use vector math but let's just draw a circle at end for
      // simplicity or custom shape
      DrawCircleV({B.x, B.y}, 5, GREEN);
    }

    // Draw Points
    DrawCircleV({A.x, A.y}, 20, BLUE);
    DrawText("A", A.x - 5, A.y - 10, 20, WHITE);

    DrawCircleV({B.x, B.y}, 20, RED);
    DrawText("B", B.x - 5, B.y - 10, 20, WHITE);

    // Draw component info
    DrawText(TextFormat("A: (%.0f, %.0f)", A.x, A.y), A.x - 40, A.y + 25, 10,
             DARKGRAY);
    DrawText(TextFormat("B: (%.0f, %.0f)", B.x, B.y), B.x - 40, B.y + 25, 10,
             DARKGRAY);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
