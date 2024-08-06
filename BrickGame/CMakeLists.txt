cmake_minimum_required(VERSION 3.5)

project(desktop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
link_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(DEFINED ENV{QTDIR})
    set(CMAKE_PREFIX_PATH "$ENV{QTDIR}")
endif()

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror  -fPIC -std=c++17")

include_directories(brick_game/snake)
include_directories(brick_game/tetris)
include_directories(brick_game/common)
include_directories(brick_game)
include_directories(gui/cli)
include_directories(gui/desktop)

add_executable(desktopBrickGame
    gui/desktop/View.cpp
    gui/desktop/View.h
    gui/desktop/View.ui
    common/bg_objects.h
    brick_game/brick_game_qt.cpp
    common/controller.cpp
    )

target_link_libraries(desktopBrickGame
    Qt::Core
    Qt::Gui
    Qt::Widgets
    -l:tetris.a
    -l:snake.a
    # -l:brick.a   
)


message(STATUS "PROJECT_SOURCES: ${PROJECT_SOURCES}")

# if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#     qt_add_executable(desktop
#         MANUAL_FINALIZATION
#         ${PROJECT_SOURCES}
#     )
# else()
#     if(ANDROID)
#         add_library(desktop SHARED
#             ${PROJECT_SOURCES}
#         )
#     else()
#         add_executable(desktop
#             ${PROJECT_SOURCES}
#         )
#     endif()
# endif()


# set_target_properties(desktop PROPERTIES
#     MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(desktop)
# endif()
