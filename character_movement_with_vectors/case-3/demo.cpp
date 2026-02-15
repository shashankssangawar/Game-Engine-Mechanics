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

  Vector operator-(const Vector &other) const {
    return Vector(x - other.x, y - other.y);
  }
  float Length() const { return std::sqrt(x * x + y * y); }
  float LengthSqr() const { return x * x + y * y; }
};

// =====================
// Main
// =====================
int main() {
  InitWindow(800, 600, "Case 3: Shortest Distance");
  SetTargetFPS(60);

  Vector Player(400, 500); // B
  Vector Enemy1(200, 200); // A
  Vector Enemy2(600, 200); // C

  bool draggingP = false;
  bool draggingE1 = false;
  bool draggingE2 = false;

  while (!WindowShouldClose()) {
    Vector mp((float)GetMouseX(), (float)GetMouseY());

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      if ((mp - Player).Length() < 20)
        draggingP = true;
      else if ((mp - Enemy1).Length() < 20)
        draggingE1 = true;
      else if ((mp - Enemy2).Length() < 20)
        draggingE2 = true;
    }
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
      draggingP = false;
      draggingE1 = false;
      draggingE2 = false;
    }

    if (draggingP) {
      Player.x = mp.x;
      Player.y = mp.y;
    }
    if (draggingE1) {
      Enemy1.x = mp.x;
      Enemy1.y = mp.y;
    }
    if (draggingE2) {
      Enemy2.x = mp.x;
      Enemy2.y = mp.y;
    }

    // Comparison
    // We use Squared Length for optimization (avoiding sqrt) as described in
    // the readme logic though we display actual distance for clarity.
    float dist1Sqr = (Player - Enemy1).LengthSqr();
    float dist2Sqr = (Player - Enemy2).LengthSqr();

    float dist1 = std::sqrt(dist1Sqr);
    float dist2 = std::sqrt(dist2Sqr);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Case 3: Comparing Distances", 20, 20, 20, DARKGRAY);
    DrawText("Drag Player (Blue) or Enemies (Red)", 20, 50, 16, GRAY);

    // Lines
    Color color1 = (dist1Sqr < dist2Sqr) ? GREEN : GRAY;
    Color color2 = (dist2Sqr < dist1Sqr) ? GREEN : GRAY;

    float epsilon = 1.0f; // tolerance in squared-pixel units
    if (std::fabs(dist1Sqr - dist2Sqr) < epsilon) {
      color1 = ORANGE;
      color2 = ORANGE;
    }

    DrawLineEx({Player.x, Player.y}, {Enemy1.x, Enemy1.y}, 3.0f, color1);
    DrawLineEx({Player.x, Player.y}, {Enemy2.x, Enemy2.y}, 3.0f, color2);

    // Draw Player
    DrawCircleV({Player.x, Player.y}, 15, BLUE);
    DrawText("Player", Player.x - 20, Player.y + 20, 10, BLUE);

    // Draw Enemy 1
    DrawCircleV({Enemy1.x, Enemy1.y}, 15, RED);
    DrawText("Enemy A", Enemy1.x - 20, Enemy1.y - 25, 10, RED);
    DrawText(TextFormat("%.0f", dist1), (Player.x + Enemy1.x) / 2,
             (Player.y + Enemy1.y) / 2, 20, color1);

    // Draw Enemy 2
    DrawCircleV({Enemy2.x, Enemy2.y}, 15, RED);
    DrawText("Enemy C", Enemy2.x - 20, Enemy2.y - 25, 10, RED);
    DrawText(TextFormat("%.0f", dist2), (Player.x + Enemy2.x) / 2,
             (Player.y + Enemy2.y) / 2, 20, color2);

    // Result Text
    if (dist1Sqr < dist2Sqr)
      DrawText("Enemy A is closer!", 20, 550, 20, GREEN);
    else if (dist2Sqr < dist1Sqr)
      DrawText("Enemy C is closer!", 20, 550, 20, GREEN);
    else
      DrawText("Both are at same distance!", 20, 550, 20, ORANGE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
