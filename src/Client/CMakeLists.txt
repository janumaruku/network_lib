add_executable(client TcpClient.cpp
        main.cpp)

target_include_directories(client PUBLIC include)

target_link_libraries(client PUBLIC network warning_options)

set_target_properties(client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
