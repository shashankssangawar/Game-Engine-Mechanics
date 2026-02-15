#include "raylib.h"
#include <cmath>
// #include <iostream>
#include <string>
#include <vector>

// =====================
// Vector
// =====================
class Vector {
public:
  float x, y;

  Vector() : x(0), y(0) {}
  Vector(float X, float Y) : x(X), y(Y) {}

  float Length() const { return std::sqrt(x * x + y * y); }

  Vector Normalize() const {
    float len = Length();
    if (len == 0)
      return Vector(0, 0);
    return Vector(x / len, y / len);
  }

  float Dot(const Vector &other) const { return x * other.x + y * other.y; }

  Vector operator+(const Vector &other) const {
    return Vector(x + other.x, y + other.y);
  }

  Vector operator-(const Vector &other) const {
    return Vector(x - other.x, y - other.y);
  }

  Vector operator*(float scalar) const {
    return Vector(x * scalar, y * scalar);
  }

  Vector &operator+=(const Vector &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
};

// =====================
// Character
// =====================
class Character {
public:
  Character(float startX, float startY, int keyUp, int keyDown, int keyLeft,
            int keyRight, Color drawColor)
      : position(startX, startY), up(keyUp), down(keyDown), left(keyLeft),
        right(keyRight), color(drawColor) {
    facing = Vector(0, -1);
  }

  void Update(float deltaTime) {
    HandleInput();
    position += velocity * deltaTime;
  }

  void Draw() const {
    DrawRectangle((int)position.x, (int)position.y, width, height, color);
  }

  void DrawDebug() const {
    Vector center = GetCenter();
    Vector swordEnd = center + facing * attackRange;

    // Sword line (actual attack)
    DrawLineEx({center.x, center.y}, {swordEnd.x, swordEnd.y}, 4.0f, BLACK);
  }

  Vector GetCenter() const {
    return Vector(position.x + width / 2.0f, position.y + height / 2.0f);
  }

  Vector GetFacing() const { return facing; }
  float GetAttackRange() const { return attackRange; }
  float GetAttackWidth() const { return attackWidth; }

private:
  Vector position;
  Vector velocity;
  Vector facing;

  int up, down, left, right;

  const int width = 40;
  const int height = 60;
  const float moveSpeed = 250.0f;

  const float attackRange = 80.0f;
  const float attackWidth = 20.0f;

  Color color;

  void HandleInput() {
    velocity = Vector(0, 0);

    if (IsKeyDown(left)) {
      velocity.x = -moveSpeed;
      facing = Vector(-1, 0);
    }
    if (IsKeyDown(right)) {
      velocity.x = moveSpeed;
      facing = Vector(1, 0);
    }
    if (IsKeyDown(up)) {
      velocity.y = -moveSpeed;
      facing = Vector(0, -1);
    }
    if (IsKeyDown(down)) {
      velocity.y = moveSpeed;
      facing = Vector(0, 1);
    }

    if (velocity.Length() > 0)
      velocity = velocity.Normalize() * moveSpeed;
  }
};

// =====================
// Combat Result
// =====================
enum AttackResult { NO_ATTACK, BACKSTAB, BLOCKED_FACING };

// =====================
// Sword-Based Combat
// =====================
AttackResult CheckAttack(const Character &attacker, const Character &victim) {
  Vector start = attacker.GetCenter();
  Vector end = start + attacker.GetFacing() * attacker.GetAttackRange();

  Vector victimCenter = victim.GetCenter();

  Vector swordDir = (end - start).Normalize();
  Vector toVictim = victimCenter - start;

  float projectionLength = toVictim.Dot(swordDir);

  if (projectionLength < 0 || projectionLength > attacker.GetAttackRange())
    return NO_ATTACK;

  Vector closestPoint = start + swordDir * projectionLength;

  float distance = (victimCenter - closestPoint).Length();

  if (distance <= attacker.GetAttackWidth()) {
    float facingAlignment = attacker.GetFacing().Dot(victim.GetFacing());

    if (facingAlignment <= 0.7f)
      return BLOCKED_FACING;

    return BACKSTAB;
  }

  return NO_ATTACK;
}

// =====================
// Word Wrap
// =====================
std::vector<std::string> WordWrap(const std::string &text, int fontSize,
                                  int maxWidth) {
  std::vector<std::string> lines;
  std::string currentLine;
  std::string word;

  for (char c : text) {
    if (c == ' ') {
      std::string test = currentLine + word + " ";
      if (MeasureText(test.c_str(), fontSize) > maxWidth) {
        lines.push_back(currentLine);
        currentLine = word + " ";
      } else {
        currentLine = test;
      }
      word.clear();
    } else {
      word += c;
    }
  }

  if (!word.empty()) {
    std::string test = currentLine + word;
    if (MeasureText(test.c_str(), fontSize) > maxWidth) {
      lines.push_back(currentLine);
      currentLine = word;
    } else {
      currentLine = test;
    }
  }

  if (!currentLine.empty())
    lines.push_back(currentLine);

  return lines;
}

// =====================
// Main
// =====================
int main() {
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Backstab Demo");
  SetTargetFPS(60);

  Character player(200, 300, KEY_W, KEY_S, KEY_A, KEY_D, BLUE);

  Character enemy(500, 300, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, RED);

  std::string message = "";
  float messageTimer = 0.0f;
  const float messageDuration = 1.5f;

  while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();

    player.Update(deltaTime);
    enemy.Update(deltaTime);

    if (IsKeyPressed(KEY_SPACE)) {
      AttackResult result = CheckAttack(player, enemy);

      if (result == BACKSTAB)
        message = "RED WAS BACKSTABBED BY BLUE'S SWORD!";
      else if (result == BLOCKED_FACING)
        message = "Cannot backstab - enemy is facing you!";
      else
        message = "Attack missed.";

      messageTimer = messageDuration;
    }

    if (IsKeyPressed(KEY_ENTER)) {
      AttackResult result = CheckAttack(enemy, player);

      if (result == BACKSTAB)
        message = "BLUE WAS BACKSTABBED BY RED'S SWORD!";
      else if (result == BLOCKED_FACING)
        message = "Cannot backstab - player is facing you!";
      else
        message = "Attack missed.";

      messageTimer = messageDuration;
    }

    if (messageTimer > 0)
      messageTimer -= deltaTime;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    player.Draw();
    player.DrawDebug();

    enemy.Draw();
    enemy.DrawDebug();

    if (messageTimer > 0) {
      int fontSize = 28;
      int maxWidth = screenWidth - 100;

      auto lines = WordWrap(message, fontSize, maxWidth);

      int totalHeight = lines.size() * (fontSize + 5);
      int startY = screenHeight / 2 - totalHeight / 2;

      for (size_t i = 0; i < lines.size(); i++) {
        int textWidth = MeasureText(lines[i].c_str(), fontSize);
        int x = screenWidth / 2 - textWidth / 2;
        int y = startY + i * (fontSize + 5);

        DrawText(lines[i].c_str(), x, y, fontSize, DARKPURPLE);
      }
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
