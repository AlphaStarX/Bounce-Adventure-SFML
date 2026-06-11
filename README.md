# Bounce Adventure

A modern C++17 2D platformer game built using the Simple and Fast Multimedia Library (SFML). This project was created as an educational learning endeavor to understand game engine architecture, scene state management, physics integration, and platforming logic.

## Tech Stack

*   **Language**: C++17 (for modern standards, smart pointers, structure binds, filesystem access).
*   **Multimedia Framework**: SFML (Simple and Fast Multimedia Library) 3.0+ / 2.6+ (handles render windowing, input events, graphics, custom views/cameras, and audio systems).
*   **Build Tool**: CMake 3.20+ (cross-platform build system generation).
*   **Compiler Toolchain**: MSVC (Microsoft Visual C++ compiler via Visual Studio Build Tools).

---

## Game Features

*   **Physics-Based Controls**: Realistic acceleration, ground/air friction, terminal velocity, and bouncing mechanics mapping player keyboard inputs (`A`/`D`/`Space`).
*   **State-Driven Scene Flow**: Built with a stack-based `SceneManager` allowing transitions between the `MainMenuScene`, active `GameScene`, `PauseScene` overlay, `LevelCompleteScene`, and `GameCompleteScene`.
*   **Custom UI Subsystem**: Custom-built `TextLabel` and `Button` classes supporting hover highlights and callbacks.
*   **Level Selection Menu**: Directly select and jump into any level from the Main Menu.
*   **Checkpoint & Health Systems**:
    *   3 lives per level. Completing a level successfully replenishes lives to full.
    *   Checkpoint flagposts save respawn coordinates.
    *   Game Over retries restart the player on the current level reached, rather than resetting to Level 1.
*   **Persistent Statistics**: Coin collection accumulates and carries over dynamically between stages.

---

## Level Layouts

Bounce Adventure features 6 uniquely themed levels:
1.  **Level 1 (Learning Basics)**: Introduces basic movements, small jumps, and coin collections.
2.  **Level 2 (Collectibles)**: Focuses on optional collection paths and platform heights.
3.  **Level 3 (Hazards)**: Introduces spikes on the ground where the player must time their jumps.
4.  **Level 4 (Moving Platforms)**: Incorporates smooth horizontal and vertical moving platforms.
5.  **Level 5 (Advanced Platforming)**: Demands tighter jumps, hazard avoidance, and checkpoints.
6.  **Level 6 (Final Challenge)**: An intensive course featuring moving platform chains in mid-air and tight spike hurdles.

---

## Build and Run Instructions

### Prerequisites
*   Visual Studio Community (with C++ Desktop Development tools).
*   CMake 3.20+ installed.
*   SFML 3.x / 2.6+ libraries installed.

### Compilation
Configure the build specifying your local SFML installation directory:

```powershell
# Configure CMake (using Win32 architecture to match 32-bit SFML libraries)
cmake -S . -B build -A Win32 -DSFML_DIR="C:\SFML\lib\cmake\SFML"

# Build the project (Debug Configuration)
cmake --build build --config Debug
```

### Running the Game
Run the compiled executable located at:
`build/Debug/BounceAdventure.exe`

---

## Controls

*   **Move Left**: `A`
*   **Move Right**: `D`
*   **Jump**: `Space`
*   **Pause Game**: `Escape` (Press again to Resume)
*   **Select/Confirm Menu Buttons**: Left Mouse Click
*   **Reset Level**: `Backspace`
