cmake_minimum_required(VERSION 3.14)
# CMAKE 3.14 needed for FetchContent_MakeAvailable

project(eng_numerals_pib1e9)

# set C++ 14 as required for all targets
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)
FetchContent_MakeAvailable(Catch2)

include(CTest)
enable_testing()

add_executable(eng_numerals_pib1e9_cli src/cli_main.cpp)

add_executable(tests src/test_main.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2)
add_test(NAME test1 COMMAND tests)
