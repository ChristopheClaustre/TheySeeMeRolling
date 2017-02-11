cmake_minimum_required(VERSION 3.1)
set(CMAKE_BUILD_TYPE RELEASE)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
project(ProjetAudioVideo)

find_package( OpenCV REQUIRED )

add_subdirectory(src)
add_subdirectory(library)

