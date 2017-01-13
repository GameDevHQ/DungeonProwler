cmake_minimum_required(VERSION 3.6)
project(roguelike)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)

file(GLOB SOURCE_FILES src/*.cpp)

include_directories(include/)
add_executable(roguelike ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules/")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(roguelike ${SFML_LIBRARIES})
endif()
