cmake_minimum_required (VERSION 3.19)

set (HEADERS "include/Application.h")
set (SOURCES "src/Application.cpp")

project ("application")

add_library (${PROJECT_NAME}
  STATIC
    ${HEADERS}
    ${SOURCES}
)

set_target_properties (${PROJECT_NAME}
  PROPERTIES
    set (CMAKE_CXX_STANDARD 20)
    set (CMAKE_CXX_STANDARD_REQUIRED ON)
)

target_include_directories (${PROJECT_NAME}
  PUBLIC 
    $<INSTALL_INTERFACE:include>    
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries (${PROJECT_NAME} 
  PUBLIC
    assets
    closed-bounded-polyline
    field
    indicator
    player
    sfml-graphics
    sfml-system
    sfml-window
)

add_subdirectory ("test")
