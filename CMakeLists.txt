cmake_minimum_required(VERSION 2.8)
project(ixte)

add_definitions(--std=c++11 -Wall -Werror -pedantic -pthread -g)

find_package(Threads)

find_package(Boost 1.5 REQUIRED COMPONENTS filesystem system)
include_directories(${Boost_INCLUDE_DIRS})

set(IXTE_SOURCES main.cpp gui.cpp text_buffer.cpp processor.cpp
     external.cpp piper.cpp graphic_system.cpp command.cpp mouse.cpp
     mouse.cpp ruler.cpp error_msgr.cpp system.cpp line.cpp)

add_executable(ixte ${IXTE_SOURCES})
target_link_libraries(ixte ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES}
    sfml-graphics sfml-window sfml-system)

file(COPY assets DESTINATION .)

file(GLOB scripts scripts/*)

file(COPY ${scripts} DESTINATION .)
