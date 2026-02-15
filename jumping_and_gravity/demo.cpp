#include "raylib.h"

// --------------------------------------------------
// Simple 2D vector class for position and velocity
// --------------------------------------------------
class Vector {
public:
  float x;
  float y;

  // Default constructor (0,0)
  Vector() : x(0.0f), y(0.0f) {}

  // Parameterized constructor
  Vector(float xVal, float yVal) : x(xVal), y(yVal) {}

  // Vector addition
  Vector operator+(const Vector &other) const {
    return Vector(x + other.x, y + other.y);
  }

  // Multiply vector by scalar
  Vector operator*(float scalar) const {
    return Vector(x * scalar, y * scalar);
  }

  // Add and assign (useful for integration)
  Vector &operator+=(const Vector &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
};

// --------------------------------------------------
// Player class
// Handles physics, input, collision, and rendering
// --------------------------------------------------
class Player {
public:
  // Constructor initializes position and ground level
  Player(float startX, float startY, float groundLevel)
      : position(startX, startY), velocity(0.0f, 0.0f), groundY(groundLevel),
        isGrounded(false) {}

  // Main update function called every frame
  void Update(float deltaTime) {

    // 1. Handle keyboard input
    HandleInput();

    // 2. Apply gravity (acceleration)
    //    v = v + a * dt
    velocity.y += gravity * deltaTime;

    // 3. Integrate velocity into position
    //    p = p + v * dt
    position += velocity * deltaTime;

    // 4. Resolve collision with ground
    ResolveGroundCollision();
  }

  // Draw player as rectangle
  void Draw() const {
    DrawRectangle(static_cast<int>(position.x), static_cast<int>(position.y),
                  width, height, BLUE);
  }

private:
  // --- Physics state ---
  Vector position; // Player location in world
  Vector velocity; // Player velocity (pixels/sec)

  // --- Player dimensions ---
  const int width = 40;
  const int height = 60;

  // --- Physics constants ---
  const float gravity = 1100.0f;   // Downward acceleration
  const float moveSpeed = 350.0f;  // Horizontal speed
  const float jumpForce = -500.0f; // Instant upward velocity

  float groundY;   // Y position of the ground
  bool isGrounded; // True if standing on ground

  // -----------------------------------------
  // HandleInput
  // Reads keyboard and modifies velocity
  // -----------------------------------------
  void HandleInput() {

    // Reset horizontal velocity every frame
    // (This gives instant acceleration movement style)
    velocity.x = 0.0f;

    // Move left
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
      velocity.x = -moveSpeed;

    // Move right
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
      velocity.x = moveSpeed;

    // Jump only if on ground
    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP) || IsKeyDown(KEY_SPACE)) &&
        isGrounded) {
      // Apply upward impulse
      velocity.y = jumpForce;
      isGrounded = false;
    }
  }

  // -----------------------------------------
  // ResolveGroundCollision
  // Prevents player from falling through floor
  // -----------------------------------------
  void ResolveGroundCollision() {

    // Calculate bottom of player rectangle
    float bottom = position.y + height;

    // If player is below or touching ground
    if (bottom >= groundY) {

      // Snap player to ground surface
      position.y = groundY - height;

      // Stop downward motion
      velocity.y = 0.0f;

      // Player is now grounded
      isGrounded = true;
    }
  }
};

// --------------------------------------------------
// Main Entry Point
// --------------------------------------------------
int main() {

  const int screenWidth = 1000;
  const int screenHeight = 600;
  const float groundY = 500.0f;

  // Initialize window
  InitWindow(screenWidth, screenHeight, "C++ Jump Physics (raylib)");

  // Limit to 60 frames per second
  SetTargetFPS(20);

  // Create player
  Player player(200.0f, 200.0f, groundY);

  // Game loop
  while (!WindowShouldClose()) {

    // Get frame time (delta time in seconds)
    float dt = GetFrameTime();

    // Update physics
    player.Update(dt);

    // Begin rendering
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw ground
    DrawRectangle(0, (groundY), screenWidth,
                  screenHeight - static_cast<int>(groundY), DARKGRAY);

    // Draw player
    player.Draw();

    EndDrawing();
  }

  // Cleanup
  CloseWindow();

  return 0;
}
