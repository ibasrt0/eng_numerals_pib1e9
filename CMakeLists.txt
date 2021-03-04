cmake_minimum_required(VERSION 3.14)
# CMAKE 3.14 needed for FetchContent_MakeAvailable

project(eng_numerals_pib1e9)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

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

option(CODE_COVERAGE "Enable coverage reporting" OFF)
if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  message("!!! building with code coverage !!!")
  include(CodeCoverage)
  append_coverage_compiler_flags()
  setup_target_for_coverage_lcov(
      NAME tests_coverage
      EXECUTABLE tests
      DEPENDENCIES tests
      EXCLUDE
        # exclude system headers
        '/usr/include/*'
  )
endif()

include_directories(./include)

add_library( eng_numerals_pib1e9
  include/eng_numerals_pib1e9.hpp 
  src/eng_numerals_pib1e9.cpp
)
  
add_executable( eng_numerals_pib1e9_cli
    src/cli_main.cpp
  )
  target_link_libraries(eng_numerals_pib1e9_cli PRIVATE eng_numerals_pib1e9)

add_executable(tests 
    src/test_main.cpp
  )
  target_link_libraries(tests PRIVATE eng_numerals_pib1e9)
  target_link_libraries(tests PRIVATE Catch2::Catch2)

add_test(NAME tests COMMAND tests)
