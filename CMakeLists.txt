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
    main.cpp
    Game.cpp
    Ball.cpp
    Paddle.cpp
    ControlStrategy.cpp
	CenterLine.cpp
	ScoreDisplay.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}   
        ${SFML_INCLUDE_DIR}           # SFML/include
)

target_link_directories(${PROJECT_NAME}
    PRIVATE
        ${SFML_LIB_DIR}               # SFML/lib
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        sfml-system
        sfml-window
        sfml-graphics
)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/arial.ttf")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/arial.ttf"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/arial.ttf"
    )
endif()

