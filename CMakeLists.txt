cmake_minimum_required(VERSION 3.1)
set(CMAKE_BUILD_TYPE RELEASE)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
project(TheySeeMeRolling)

find_package( OpenCV REQUIRED )
find_package( OpenAL REQUIRED )

add_subdirectory(src)

