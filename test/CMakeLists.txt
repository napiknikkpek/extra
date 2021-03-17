add_executable(extra_test main.cpp fix_vector.cpp)

target_link_libraries(extra_test PUBLIC 
    extra
    Boost::boost)

add_test(NAME extra_test COMMAND $<TARGET_FILE:extra_test>)
