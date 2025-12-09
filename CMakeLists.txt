cmake_minimum_required(VERSION 3.16)

project(PongSFML LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    main.cpp
    Game.cpp
    Ball.cpp
    Paddle.cpp
    ControlStrategy.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        sfml-system
        sfml-window
        sfml-graphics
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/arial.ttf")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/arial.ttf"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/arial.ttf"
    )
endif()

