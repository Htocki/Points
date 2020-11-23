cmake_minimum_required (VERSION 3.18)

project ("project")

if (MSVC)
  add_definitions (/W4)
elseif (CMAKE_COMPILER_IS_GNUCXX)
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


include (FetchContent)

# googletest
FetchContent_Declare (
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        master
)

FetchContent_GetProperties (googletest)
if (NOT googletest_POPULATED)
  FetchContent_Populate (googletest)
  add_subdirectory (
    ${googletest_SOURCE_DIR} 
    ${googletest_BINARY_DIR}
  )
endif ()

# sfml
set (BUILD_SHARED_LIBS false)

FetchContent_Declare (
  sfml
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        master
)

FetchContent_GetProperties (sfml)
if (NOT sfml_POPULATED)
  if (LINK_DEPS_STATIC)
    set (SFML_STATIC_LIBRARIES CACHE BOOL TRUE)
  endif ()

  FetchContent_Populate (sfml)
  add_subdirectory (
    ${sfml_SOURCE_DIR} 
    ${sfml_BINARY_DIR}
  )
endif ()

add_subdirectory ("application")
