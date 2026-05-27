add_executable(server main.cpp
        TcpServer.cpp
        include/TcpServer.hpp
        ClientSession.cpp
        include/ClientSession.hpp)

target_include_directories(server PRIVATE include)

target_link_libraries(server PRIVATE network warning_options)

set_target_properties(server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
