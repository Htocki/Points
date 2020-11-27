cmake_minimum_required (VERSION 3.18)

project ("project")

if (CMAKE_COMPILER_IS_GNUCXX)
  add_definitions (-Wall -pedantic -std=gnu++2a)
endif ()

if (MSVC) 
  set_property (
    TARGET 
      ${PROJECT_NAME} APPEND_STRING
    PROPERTY LINK_FLAGS 
      "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
  )
endif ()

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include (CTest)
endif ()

## sfml
find_package (SFML 2.5.1 REQUIRED network audio graphics window system)
if (SFML_FOUND)
  include_directories (${SFML_INCLUDE_DIR})
endif ()

## gtest
find_package(GTest REQUIRED)
if (GTEST_FOUND)
  include_directories (${GTEST_INCLUDE_DIRS})
endif ()

add_subdirectory ("application")
