project(music_player CXX)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

find_package(SDL REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(Threads REQUIRED)
find_package(GMock)
find_package(GTest)

include(CodeCoverage)

add_library(mp src/musicplayer.cpp src/sdlplayer.cpp)
target_include_directories(mp PUBLIC ${SDL_INCLUDE_DIRS} ${SDL_MIXER_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_options(mp PRIVATE -O0 --coverage -fprofile-arcs -ftest-coverage)

add_executable(music_player src/main.cpp)
target_link_libraries(music_player ${SDL_LIBRARY} ${SDL_MIXER_LIBRARIES} stdc++fs mp)

if(GMOCK_FOUND AND GTEST_FOUND)
    enable_testing()

    add_executable(tests tests/main.cpp tests/musicplayertests.cpp)
    add_test(player_tests tests)
    target_link_libraries(tests ${GMOCK_LIBRARIES} ${GTEST_LIBRARIES} mp ${CMAKE_THREAD_LIBS_INIT})
    target_include_directories(tests PRIVATE ${GMOCK_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})

    setup_target_for_coverage_cobertura( NAME coverage_xml EXECUTABLE ctest DEPENDENCIES tests)
    setup_target_for_coverage( NAME coverage_html EXECUTABLE ctest DEPENDENCIES tests)
endif()
