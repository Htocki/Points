
cmake_minimum_required (VERSION 3.18)

project ("application")

add_executable (${PROJECT_NAME} "src/Main.cpp")

set_target_properties (${PROJECT_NAME}
  PROPERTIES
    set (CMAKE_CXX_STANDARD 20)
    set (CMAKE_CXX_STANDARD_REQUIRED ON)
)

target_link_libraries (${PROJECT_NAME} 
  PUBLIC
    sfml-graphics
    sfml-system
    sfml-window
)
