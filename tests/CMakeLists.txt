# Bounce Adventure test target.
#
# Pulls in the engine sources that have no SFML runtime dependency (i.e. logic
# classes), plus the same SFML components the game links, and registers an
# executable with CTest via add_test().

add_executable(BounceAdventureTests
    test_main.cpp

    test_collision.cpp
    test_level_loader.cpp
    test_physics_constants.cpp
    test_scene_manager.cpp

    # Engine sources exercised by the tests above.
    ${CMAKE_SOURCE_DIR}/src/Physics/Collision.cpp
    ${CMAKE_SOURCE_DIR}/src/Physics/CollisionSystem.cpp
    ${CMAKE_SOURCE_DIR}/src/Level/LevelLoader.cpp
    ${CMAKE_SOURCE_DIR}/src/Core/SceneManager.cpp
)

target_include_directories(BounceAdventureTests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include
)

# Match the same SFML component selection the main game uses (3 preferred, 2.6 fallback).
if (TARGET SFML::Graphics)
    target_link_libraries(BounceAdventureTests
        PRIVATE
            SFML::Graphics
            SFML::Window
            SFML::System
    )
else()
    target_link_libraries(BounceAdventureTests
        PRIVATE
            sfml-graphics
            sfml-window
            sfml-system
    )
endif()

# CTest will run the executable from the directory containing the fixtures/.
add_test(
    NAME BounceAdventureTests
    COMMAND BounceAdventureTests
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
