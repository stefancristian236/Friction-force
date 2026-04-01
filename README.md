# Friction Force Simulation

## Overview
This project is a 2D physics simulation built in C++ using the SFML (Simple and Fast Multimedia Library) framework. It models the linear motion of a physical body across a flat surface, demonstrating the effects of user-applied forces, kinetic friction, and collision damping in real-time. It also targets the basics of using SFML libraries.

## Features
* **Real-time Physics Integration:** Calculates acceleration, velocity, and position frame-by-frame using the **Semi-implicit Euler integration method** based on elapsed delta time (`dt`).
* **Interactive Controls:** Users can dynamically apply continuous pushing forces to the moving body using mouse inputs.
* **Kinetic Friction:** Implements a realistic friction model that calculates a resistive force opposite to the body's current direction of motion based on a defined friction coefficient, gravity, and the body's mass.
* **Boundary Collisions:** The body is constrained within the 1280x960 window. Hitting the left or right walls resets the pushing force to 0 and reverses the body's velocity while applying a damping factor.
* **On-Screen Telemetry:** Live SFML text rendering displays the currently applied pushing force and the resulting velocity of the body.

## Controls
* **Left Mouse Button (Hold):** Increases the pushing force applied to the right (`+10` per frame).
* **Right Mouse Button (Hold):** Decreases the pushing force, applying force to the left (`-10` per frame).

## Physics Parameters
The simulation runs with the following default physical properties:
* **Mass of Body:** `5.0f`
* **Friction Coefficient:** `2.0f`
* **Gravity (g):** `9.81f`
* **Collision Damping:** `0.5f` (Velocity is halved upon hitting a wall)
* **Resting Threshold:** The body comes to a complete halt if no force is applied and absolute velocity drops below `1.0f`.

## Mathematical Model
The core movement logic relies on Newton's laws and the Euler method for numerical integration:

1. **Friction Calculation:** `friction = ±(coefficient * g * mass)` depending on the current direction of velocity.
2. **Acceleration:** `a = coefficient * g`.
3. **Integration:** `velocity += a * dt` followed by `position += velocity * dt`.

## Installation & Setup
### Prerequisites
* A C++17 compatible compiler (required for `std::optional` event polling).
* SFML 3.x library installed.
* CMake build system.

### Assets
Ensure you have a valid TrueType font file located at `../assets/fonts/arialceb.ttf` relative to your executable for the telemetry text to render correctly. The `assets/` directory is intentionally ignored by source control.

### Sources:
https://en.wikipedia.org/wiki/Euler_method
https://en.wikipedia.org/wiki/Friction
