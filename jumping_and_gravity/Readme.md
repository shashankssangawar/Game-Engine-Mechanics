# Jumping and Gravity

This example demonstrates how to implement basic 2D platformer physics including gravity, velocity integration, and jumping using Raylib and C++.

## Core Physics Concepts

### 1. Gravity (Acceleration)
Gravity is a constant force that pulls the character downwards. In physics terms, it's an acceleration.

```cpp
// Apply gravity (acceleration)
// v = v + a * dt
velocity.y += gravity * deltaTime;
```
*   **Constant Force**: `gravity` is a constant (e.g., 1100.0f).
*   **Time Step**: Multiplying by `deltaTime` ensures the effect is consistent regardless of frame rate.

### 2. Velocity Integration
To move the character, we add velocity to position. This is known as **Euler Integration**.

```cpp
// Integrate velocity into position
// p = p + v * dt
position += velocity * deltaTime;
```

### 3. Collision Resolution (Ground Check)
We need to stop the character from falling forever. We check if they have passed the ground level and "snap" them back.

```cpp
if (bottom >= groundY) {
    // Snap player to ground surface
    position.y = groundY - height;

    // Stop downward motion
    velocity.y = 0.0f;

    // Player is now grounded
    isGrounded = true;
}
```

### 4. Jumping (Impulse)
Jumping is an instantaneous change in velocity. We directly set the vertical velocity to a negative value (upwards in 2D screen coordinates).

```cpp
if (IsKeyPressed(KEY_SPACE) && isGrounded) {
    // Apply upward impulse
    velocity.y = jumpForce; // e.g., -500.0f
    isGrounded = false;
}
```

## Code Structure

*   **`Vector` Class**: A simple helper for 2D math (x, y).
*   **`Player` Class**: Encapsulates position, velocity, and physics logic.
*   **`Update` Loop**: Runs every frame to process input and physics.
*   **`Draw` Loop**: Renders the player and ground.

## Logic Flow

1.  **Input**: Check if Left/Right is pressed to set horizontal velocity. Check Space for Jump.
2.  **Gravity**: Add gravity to `velocity.y`.
3.  **Move**: Add `velocity` to `position`.
4.  **Collision**: If below ground, snap to ground and reset `velocity.y` to 0.
5.  **Draw**: Render the scene.

[View Code](demo.cpp)
