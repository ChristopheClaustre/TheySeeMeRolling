 
file(
    GLOB_RECURSE
    source_files
    *.cpp
    *.hpp
    )
       
add_executable (app ${source_files})
target_link_libraries (app ${OpenCV_LIBS} )

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/app
    DESTINATION bin
    RENAME ${CMAKE_PROJECT_NAME}-app)
    
    
