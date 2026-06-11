# Bounce Adventure - Phase 2 Engine Foundation

## Objective

Build the initial engine foundation for Bounce Adventure using C++17, SFML 2.6+, and CMake.

Phase 2 implemented:

- Game loop
- Window manager
- Input manager
- Scene interface and scene manager
- Collision helpers
- Asset manager
- Audio manager
- Level loading data/parser

Gameplay systems such as player movement, platform physics, hazards, collectibles, checkpoints, camera follow, and level completion are intentionally deferred to later phases.

## Design

The engine foundation uses small focused classes:

- `Game` owns the runtime loop and engine managers.
- `WindowManager` owns the SFML window.
- `InputManager` maps SFML keyboard events to game actions.
- `SceneManager` owns a stack of active scenes.
- `AssetManager` caches textures and fonts.
- `AudioManager` caches sound buffers and controls active sounds/music.
- `Collision` provides reusable geometric collision helpers.
- `CollisionSystem` groups collision queries that will be used by gameplay.
- `LevelLoader` parses text-map level files into `LevelData`.

The code is structured so Phase 3 can add gameplay without turning the engine classes into large gameplay containers.

## File Structure

```text
include/BounceAdventure/
├── Core/
│   ├── AssetManager.hpp
│   ├── AudioManager.hpp
│   ├── Game.hpp
│   ├── GameConfig.hpp
│   ├── InputManager.hpp
│   ├── Scene.hpp
│   ├── SceneManager.hpp
│   └── WindowManager.hpp
├── Level/
│   ├── LevelData.hpp
│   ├── LevelLoader.hpp
│   └── TileCodes.hpp
└── Physics/
    ├── Collision.hpp
    └── CollisionSystem.hpp

src/
├── Core/
│   ├── AssetManager.cpp
│   ├── AudioManager.cpp
│   ├── Game.cpp
│   ├── InputManager.cpp
│   ├── SceneManager.cpp
│   └── WindowManager.cpp
├── Level/
│   └── LevelLoader.cpp
├── Physics/
│   ├── Collision.cpp
│   └── CollisionSystem.cpp
└── main.cpp
```

## Header Files

- `GameConfig.hpp`: window and timing constants.
- `WindowManager.hpp`: SFML render-window ownership.
- `Game.hpp`: main-loop owner.
- `InputManager.hpp`: action-based keyboard input.
- `Scene.hpp`: abstract scene interface.
- `SceneManager.hpp`: scene stack owner.
- `AssetManager.hpp`: texture/font cache.
- `AudioManager.hpp`: sound/music playback manager.
- `Collision.hpp`: collision data and static geometric helpers.
- `CollisionSystem.hpp`: grouped collision queries.
- `TileCodes.hpp`: level text-map symbols.
- `LevelData.hpp`: parsed level object data.
- `LevelLoader.hpp`: level file parser interface.

## Source Files

- `main.cpp`: creates and runs `Game`.
- `WindowManager.cpp`: creates and controls the SFML window.
- `Game.cpp`: event loop, update loop, render loop, scene forwarding.
- `InputManager.cpp`: keyboard event mapping.
- `SceneManager.cpp`: push/pop/replace/current scene operations.
- `AssetManager.cpp`: lazy texture/font loading.
- `AudioManager.cpp`: sound buffer cache and music playback.
- `Collision.cpp`: rectangle/circle collision helpers.
- `CollisionSystem.cpp`: reusable collision queries.
- `LevelLoader.cpp`: text-map parsing into `LevelData`.

## Build Instructions

Required tools:

- CMake 3.20+
- C++17 compiler
- SFML 2.6+ with graphics, window, system, and audio components

Expected commands:

```bash
cmake -S . -B build
cmake --build build
```

On this machine, CMake exists at:

```text
C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe
```

## Testing Instructions

Phase 2 runtime smoke test after compiler/SFML setup:

1. Configure with CMake.
2. Build `BounceAdventure`.
3. Run the executable.
4. Confirm a `1280x720` window opens with the title `Bounce Adventure`.
5. Confirm closing the window exits cleanly.

## Verification Checklist

- [x] `Game` system added
- [x] `WindowManager` system added
- [x] `InputManager` system added
- [x] `Scene` and `SceneManager` systems added
- [x] `Collision` and `CollisionSystem` systems added
- [x] `AssetManager` system added
- [x] `AudioManager` system added
- [x] `LevelLoader` system added
- [x] CMake project file added
- [ ] Configure/build verified locally

## Verification Blocker

CMake configuration was attempted, but no C++ compiler is installed or discoverable:

```text
No CMAKE_CXX_COMPILER could be found.
```

Also, SFML discovery cannot be verified until compiler configuration succeeds.

## Next Step

Install or expose a C++17 compiler and SFML 2.6+ to CMake, then rerun:

```bash
cmake -S . -B build
cmake --build build
```

After Phase 2 compiles, Phase 3 can begin:

1. Player movement
2. Physics integration
3. Platform collisions
4. Camera follow
5. Level completion
