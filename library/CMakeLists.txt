#include(ExternalProject)
#
#ExternalProject_Add(
#    OpenCV
#    SOURCE_DIR  "${CMAKE_SOURCE_DIR}/library/opencv/sources"
#    INSTALL_COMMAND make install PREFIX=${CMAKE_CURRENT_BINARY_DIR}/library
#    )
