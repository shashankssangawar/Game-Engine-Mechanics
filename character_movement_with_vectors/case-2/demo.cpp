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
  InitWindow(800, 600, "Case 2: Calculating Distance");
  SetTargetFPS(60);

  // Points
  Vector A(200, 300);
  Vector B(500, 400);

  bool draggingA = false;
  bool draggingB = false;

  while (!WindowShouldClose()) {
    Vector mp((float)GetMouseX(), (float)GetMouseY());

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

    Vector V = B - A;
    float distance = V.Length();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Case 2: Calculating Distance", 20, 20, 20, DARKGRAY);
    DrawText("Drag points to change distance", 20, 50, 16, GRAY);

    // Draw Line
    DrawLineEx({A.x, A.y}, {B.x, B.y}, 2.0f, GRAY);

    // Draw Points
    DrawCircleV({A.x, A.y}, 10, BLUE);
    DrawText("A", (int)A.x - 5, (int)A.y - 25, 20, BLUE);

    DrawCircleV({B.x, B.y}, 10, RED);
    DrawText("B", (int)B.x - 5, (int)B.y - 25, 20, RED);

    // Draw Distance Text at center of line
    Vector center((A.x + B.x) / 2, (A.y + B.y) / 2);
    char distText[50];
    sprintf(distText, "%.2f", distance);

    // Draw a background for text
    int textWidth = MeasureText(distText, 20);
    DrawRectangle((int)center.x - textWidth / 2 - 5, (int)center.y - 12,
                  textWidth + 10, 24, RAYWHITE);
    DrawText(distText, (int)center.x - textWidth / 2, (int)center.y - 10, 20,
             BLACK);

    // Formula Display
    DrawText("|V| = sqrt(Vx*Vx + Vy*Vy)", 20, 550, 20, BLACK);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
