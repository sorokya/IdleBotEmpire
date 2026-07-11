cmake_minimum_required(VERSION 3.10)
project(IdleBotEmpire)

find_package(raylib 5.0 REQUIRED)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(${PROJECT_NAME} src/main.c src/ui.c
    src/atlas.c)

target_link_libraries(${PROJECT_NAME} raylib)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
