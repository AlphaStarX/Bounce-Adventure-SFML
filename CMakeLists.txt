cmake_minimum_required(VERSION 3.20)

project(BounceAdventure
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 3 COMPONENTS Graphics Window System Audio QUIET)
if (NOT SFML_FOUND)
    find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system audio)
endif()

add_executable(BounceAdventure
    src/main.cpp
    src/Core/AssetManager.cpp
    src/Core/AudioManager.cpp
    src/Core/Game.cpp
    src/Core/InputManager.cpp
    src/Core/SceneManager.cpp
    src/Core/WindowManager.cpp
    src/Gameplay/Checkpoint.cpp
    src/Gameplay/Collectible.cpp
    src/Gameplay/Goal.cpp
    src/Gameplay/Hazard.cpp
    src/Gameplay/HealthSystem.cpp
    src/Gameplay/MovingPlatform.cpp
    src/Gameplay/Platform.cpp
    src/Gameplay/Player.cpp
    src/Level/Level.cpp
    src/Level/LevelLoader.cpp
    src/Physics/Collision.cpp
    src/Physics/CollisionSystem.cpp
    src/Physics/PhysicsBody.cpp
    src/Physics/PhysicsConstants.cpp
    src/Scenes/GameScene.cpp
    src/Scenes/MainMenuScene.cpp
    src/Scenes/LevelSelectScene.cpp
    src/Scenes/PauseScene.cpp
    src/Scenes/LevelCompleteScene.cpp
    src/Scenes/GameCompleteScene.cpp
    src/UI/HUD.cpp
    src/UI/TextLabel.cpp
    src/UI/Button.cpp
)

target_include_directories(BounceAdventure
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (TARGET SFML::Graphics)
    target_link_libraries(BounceAdventure
        PRIVATE
            SFML::Graphics
            SFML::Window
            SFML::System
            SFML::Audio
    )
else()
    target_link_libraries(BounceAdventure
        PRIVATE
            sfml-graphics
            sfml-window
            sfml-system
            sfml-audio
    )
endif()

if (MSVC)
    target_compile_options(BounceAdventure PRIVATE /W4 /permissive-)
else()
    target_compile_options(BounceAdventure PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_custom_command(TARGET BounceAdventure POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:BounceAdventure>/assets
)

if (WIN32 AND DEFINED SFML_DIR)
    get_filename_component(SFML_CMAKE_DIR "${SFML_DIR}" ABSOLUTE)
    get_filename_component(SFML_LIB_DIR "${SFML_CMAKE_DIR}/../.." ABSOLUTE)
    get_filename_component(SFML_ROOT_DIR "${SFML_LIB_DIR}/.." ABSOLUTE)
    file(GLOB SFML_RUNTIME_DLLS "${SFML_ROOT_DIR}/bin/*.dll")

    if (SFML_RUNTIME_DLLS)
        add_custom_command(TARGET BounceAdventure POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SFML_RUNTIME_DLLS}
                $<TARGET_FILE_DIR:BounceAdventure>
        )
    endif()
endif()
