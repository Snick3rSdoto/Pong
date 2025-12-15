cmake_minimum_required(VERSION 3.16)

project(PongSFML LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SFML_ROOT         "${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML")
set(SFML_INCLUDE_DIR  "${SFML_ROOT}/include")
set(SFML_LIB_DIR      "${SFML_ROOT}/lib")

if (NOT EXISTS "${SFML_INCLUDE_DIR}/SFML/Graphics.hpp")
    message(FATAL_ERROR "not found ${SFML_INCLUDE_DIR}/SFML/Graphics.hpp. Check the structure of libs/SFML.")
endif()

set(SOURCES
    src/Ball.cpp
    src/CenterLine.cpp
    src/ControlStrategy.cpp
    src/Game.cpp
    src/Paddle.cpp
    src/ScoreDisplay.cpp
)

add_library(pong_lib ${SOURCES})

target_include_directories(pong_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/pong
        ${SFML_INCLUDE_DIR}
)

target_link_directories(pong_lib
    PUBLIC
        ${SFML_LIB_DIR}
)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        pong_lib
        sfml-graphics
        sfml-window
        sfml-system
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          ${CMAKE_SOURCE_DIR}/assets/fonts/arial.ttf
          $<TARGET_FILE_DIR:${PROJECT_NAME}>/arial.ttf
)
