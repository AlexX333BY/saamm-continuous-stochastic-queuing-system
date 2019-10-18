cmake_minimum_required(VERSION 3.13)
project(ContinuousStochasticQueuingSystem)

add_subdirectory(QueuingSystemLib)

set(HEADERS
        closed_queuing_system.h
        )

set(SOURCES
        closed_queuing_system.cpp
        )

add_executable(QueuingSystem ${HEADERS} ${SOURCES})

target_include_directories(QueuingSystem PRIVATE QueuingSystemLib)
target_link_libraries(QueuingSystem QueuingSystemLib)
