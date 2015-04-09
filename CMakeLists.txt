cmake_minimum_required(VERSION 3.0)
project(xts)

add_definitions(--std=c++14 -Wall -Werror -pedantic -pthread -g)

find_package(Threads)

find_package(Boost 1.55 REQUIRED COMPONENTS filesystem system)
include_directories(${Boost_INCLUDE_DIRS})

set(XTS_SOURCES main.cpp gui.cpp text_buffer.cpp processor.cpp
     external.cpp piper.cpp graphic_system.cpp command.cpp mouse.cpp
     mouse.cpp ruler.cpp error_msgr.cpp system.cpp line.cpp)

add_executable(xts ${XTS_SOURCES})
target_link_libraries(xts ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES}
    sfml-graphics sfml-window sfml-system)
    
file(COPY assets DESTINATION .)

file(GLOB scripts scripts/*)

file(COPY ${scripts} DESTINATION .)