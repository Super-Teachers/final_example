project(music_player CXX)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

find_package(SDL REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(Threads REQUIRED)

include(CodeCoverage)

add_subdirectory(3rdParty/gtest/googlemock)

add_library(mp src/musicplayer.cpp src/sdlplayer.cpp)
target_include_directories(mp PUBLIC ${SDL_INCLUDE_DIRS} ${SDL_MIXER_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_options(mp PRIVATE -O0 --coverage -fprofile-arcs -ftest-coverage)

add_executable(music_player src/main.cpp)
target_link_libraries(music_player ${SDL_LIBRARY} ${SDL_MIXER_LIBRARIES} stdc++fs mp)

add_executable(tests tests/main.cpp tests/musicplayertests.cpp)
add_test(player_tests tests)
target_link_libraries(tests gmock gtest mp ${CMAKE_THREAD_LIBS_INIT})

setup_target_for_coverage_cobertura( NAME coverage_xml EXECUTABLE ctest DEPENDENCIES tests)
setup_target_for_coverage( NAME coverage_html EXECUTABLE ctest DEPENDENCIES tests)
