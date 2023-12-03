cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
  ttt
  VERSION 0.1.0
  DESCRIPTION "Short description"
  HOMEPAGE_URL "https://example.com/"
  LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----
add_library(
  ttt_lib OBJECT
  source/lib.cpp
  source/day_1/day1.hpp
)

target_include_directories(
  ttt_lib ${warning_guard}
  PUBLIC
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(ttt_lib PUBLIC cxx_std_20)

# ---- Declare executable ----
add_executable(ttt_exe source/main.cpp)
add_executable(ttt::exe ALIAS ttt_exe)

set_property(TARGET ttt_exe PROPERTY OUTPUT_NAME ttt)
target_compile_features(ttt_exe PRIVATE cxx_std_20)
target_compile_options(ttt_exe PRIVATE -Wall -Wextra -Wpedantic -ggdb)
target_link_libraries(ttt_exe PRIVATE ttt_lib)
target_include_directories(ttt_exe PRIVATE ${PROJECT_SOURCE_DIR}/source/day_1/)

# ---- Install rules ----
if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----
if(NOT ttt_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
    AUTHOR_WARNING
    "Developer mode is intended for developers of ttt"
  )
endif()

include(cmake/dev-mode.cmake)
