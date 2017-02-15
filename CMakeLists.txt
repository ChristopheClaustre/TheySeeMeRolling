cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE RELEASE)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
project(TheySeeMeRolling)

find_package( OpenCV REQUIRED )
find_package( OpenAL REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test REQUIRED )
find_package( Qt5Core REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5Concurrent REQUIRED )
find_package( Qt5OpenGL REQUIRED )

add_subdirectory(src)

