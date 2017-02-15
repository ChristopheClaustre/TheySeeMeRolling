file(
    GLOB_RECURSE
    source_files
    *.cpp
    *.h
    )

file(
    GLOB_RECURSE
    audio_source_files
    Audio/*.cpp
    Audio/*.h
    utils.h
    Audio/*.cxx
    )

file(
    GLOB_RECURSE
    video_source_files
    Video/*.cpp
    Video/*.h
    utils.h
    Video/*.cxx
    )

add_executable (app ${source_files})
add_executable (test_audio ${audio_source_files})
add_executable (test_video ${video_source_files})

target_link_libraries (app ${OpenCV_LIBS} ${OPENAL_LIBRARY})
target_link_libraries (test_video ${OpenCV_LIBS})
target_link_libraries (test_audio ${OPENAL_LIBRARY})

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/app
    DESTINATION bin
    RENAME ${CMAKE_PROJECT_NAME}-app)
    
    
