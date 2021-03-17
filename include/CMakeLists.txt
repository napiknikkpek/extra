add_library(extra INTERFACE)

target_include_directories(extra INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>)
