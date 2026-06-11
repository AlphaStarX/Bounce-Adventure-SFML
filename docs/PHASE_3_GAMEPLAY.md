# Bounce Adventure — Phase 3 Gameplay

## Objective

Close out the project by adding the gameplay layer on top of the Phase 2 engine
foundation. Phase 3 implements the player, all gameplay entities, the level
system, the UI, and the scene flow that ties them together into a playable
6-level platformer.

This document complements `PHASE_1_ARCHITECTURE.md` and
`PHASE_2_ENGINE_FOUNDATION.md`.

## What Phase 3 Adds

### Player and physics
- `Player` (circle, radius 22) with a `PhysicsBody` for integration.
- Custom physics: gravity, move acceleration, ground/air friction, terminal
  velocity, jump impulse, landing bounce.
- Circle-vs-rectangle collision resolution via the `Collision` helper.
- **Jump feel** (added in a later pass):
  - **Coyote time** — `PhysicsConstants::CoyoteTime` (0.10s) of grace after
    walking off a ledge, during which Jump still works.
  - **Jump buffer** — `PhysicsConstants::JumpBufferTime` (0.10s) of grace
    before landing, during which a Jump press is remembered and fired the
    instant the player is grounded.
  - **Variable jump height** — releasing Jump mid-air caps upward velocity at
    `JumpVelocity * JumpCutMultiplier` (40% by default) so short taps produce
    short hops and held presses produce full jumps.

### Gameplay entities
All under `src/Gameplay/`:

| Class         | Purpose                                                    |
|---------------|------------------------------------------------------------|
| `Platform`    | Static solid tile the player can stand on.                 |
| `MovingPlatform` | Sine-driven platform moving horizontally or vertically. |
| `Hazard`      | Spikes. On overlap, deals damage.                          |
| `Collectible` | Coin. On overlap, increments the coin counter.            |
| `Checkpoint`  | Flagpost. On overlap, saves the current respawn position.  |
| `Goal`        | End-of-level trigger that advances to the next scene.      |
| `HealthSystem`| Lives (default 3) and damage tracking.                     |

### Level system
- Text-map level files in `assets/levels/` (one row per line, one character per
  tile). Tile codes are defined in `include/BounceAdventure/Level/TileCodes.hpp`:
  - `.` empty
  - `P` player spawn
  - `#` platform
  - `^` hazard
  - `C` collectible (coin)
  - `K` checkpoint
  - `G` goal
  - `H` moving platform, horizontal
  - `V` moving platform, vertical
- `LevelLoader` parses the text into a `LevelData` struct, which is then held
  by `Level` for runtime access.

### UI
- `Button` — hand-rolled button with hover highlighting, mouse click handling,
  and a `std::function<void()>` callback.
- `TextLabel` — drawable `sf::Text` wrapper with a `TextAlignment` enum.
- `HUD` — top-left status display showing health, coin count, and current
  level name. Also displays centered messages (e.g. "Game Over!").

### Scene flow
Six concrete scenes derived from the `Scene` interface:

```
MainMenuScene ──click Play──▶ GameScene (level 1)
MainMenuScene ──click Level Select──▶ LevelSelectScene ──click tile──▶ GameScene
GameScene ──Esc──▶ PauseScene ──Esc──▶ GameScene
GameScene ──reach goal──▶ LevelCompleteScene ──Enter──▶ GameScene (level + 1)
GameScene ──reach goal on level 6──▶ GameCompleteScene ──Enter──▶ GameScene (level 1)
```

`SceneManager` is a stack with **deferred** mutations
(`processPendingChanges()` between frames) so that scenes can request
`push`/`pop`/`replace`/`clear` from inside their own `update()` without
invalidating iteration state.

### Persistent state
- Coin count carries across levels. The scene constructor accepts the running
  total and `LevelCompleteScene` / `GameCompleteScene` forward it forward.
- Lives are reset to `HealthSystem::MaxHealth` at the start of each level.
- Checkpoint position is per-level and resets when the level is reloaded.

## File Structure (Phase 3 additions)

```text
include/BounceAdventure/
├── Gameplay/
│   ├── Checkpoint.hpp
│   ├── Collectible.hpp
│   ├── Goal.hpp
│   ├── Hazard.hpp
│   ├── HealthSystem.hpp
│   ├── MovingPlatform.hpp
│   ├── Platform.hpp
│   └── Player.hpp
├── Level/
│   ├── Level.hpp
│   ├── LevelData.hpp
│   ├── LevelLoader.hpp
│   └── TileCodes.hpp
├── Scenes/
│   ├── GameCompleteScene.hpp
│   ├── GameScene.hpp
│   ├── LevelCompleteScene.hpp
│   ├── LevelSelectScene.hpp
│   ├── MainMenuScene.hpp
│   └── PauseScene.hpp
└── UI/
    ├── Button.hpp
    ├── HUD.hpp
    └── TextLabel.hpp

src/
├── Gameplay/
│   ├── Checkpoint.cpp
│   ├── Collectible.cpp
│   ├── Goal.cpp
│   ├── Hazard.cpp
│   ├── HealthSystem.cpp
│   ├── MovingPlatform.cpp
│   ├── Platform.cpp
│   └── Player.cpp
├── Level/
│   ├── Level.cpp
│   └── LevelLoader.cpp
├── Scenes/
│   ├── GameCompleteScene.cpp
│   ├── GameScene.cpp
│   ├── LevelCompleteScene.cpp
│   ├── LevelSelectScene.cpp
│   ├── MainMenuScene.cpp
│   └── PauseScene.cpp
└── UI/
    ├── Button.cpp
    ├── HUD.cpp
    └── TextLabel.cpp
```

## Tests

A unit test executable (`BounceAdventureTests`) is built by the same CMake
project under `tests/`. It currently covers:

- `Collision` and `CollisionSystem` (rect/rect, circle/rect, point-in-rect).
- `LevelLoader` (parses a minimal level, a full level, and rejects missing
  files / missing goals / unknown tile codes).
- `PhysicsConstants` (gravity sign, jump velocity sign, friction ordering,
  jump-cut multiplier bounds, internal consistency of movement tunables).
- `SceneManager` (push/pop/replace/clear, the deferred-changes contract, and
  queue ordering).

The test harness is a single header (`tests/test_harness.hpp`) — deliberately
hand-written so the project has no third-party test dependency.

Run via:

```bash
cmake --build build --config Debug --target BounceAdventureTests
ctest --test-dir build --output-on-failure
```

## Build & Run (unchanged from Phase 2)

```bash
cmake -S . -B build -A Win32 -DSFML_DIR="C:\SFML\lib\cmake\SFML"
cmake --build build --config Debug
build\Debug\BounceAdventure.exe
```

## Verification Checklist

- [x] Player physics: movement, jumping, landing bounce
- [x] All 6 level tiles (P, #, ^, C, K, G, H, V) parse and render
- [x] Moving platforms carry the player horizontally and vertically
- [x] Hazards damage and respawn the player
- [x] Collectibles increment the coin counter
- [x] Checkpoints save a respawn position
- [x] Goal advances to the next level (or to GameCompleteScene on level 6)
- [x] All six scenes transition correctly via SceneManager
- [x] Pause/resume via Esc preserves game state
- [x] Jump feel: coyote time, jump buffer, variable jump height
- [x] Unit test executable builds and all 32 tests pass
- [x] Stale build directories removed
- [x] `.clang-format`, `LICENSE`, and this document added

## Known Gaps / Follow-ups

These were intentionally out of scope but are the natural next steps:

- Audio is wired into `AudioManager` but **not yet triggered from gameplay
  scenes** — coin pickup, hazard hit, jump, etc. should call `playSound()`.
- The HUD font is hardcoded to `C:\Windows\Fonts\arial.ttf`; a real font
  should be bundled in `assets/fonts/`.
- The "Game Over" branch in `GameScene::update` resets the coin counter, which
  contradicts the README's "carries over" wording — the branch should preserve
  coins and only reset on level change.
- Hazards deal damage every frame the player overlaps; an invulnerability
  timer (i-frames) is needed.
- Reaching the goal can re-trigger and stack scenes if the player backs out
  of `LevelCompleteScene` and returns — needs a "this level is done" flag.
- No CI, no automated builds on push.
