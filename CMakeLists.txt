cmake_minimum_required(VERSION 3.13)
project(ContinuousStochasticQueuingSystem)

find_package(Boost 1.67.0 REQUIRED COMPONENTS
    program_options
)

add_subdirectory(QueuingSystemLib)

set(HEADERS
        closed_queuing_system.h
        model_parameters_parser.h
)

set(SOURCES
        closed_queuing_system.cpp
        model_parameters_parser.cpp
)

add_executable(QueuingSystem ${HEADERS} ${SOURCES})

target_include_directories(QueuingSystem PRIVATE
        ${Boost_INCLUDE_DIRS}
        QueuingSystemLib
)
target_link_libraries(QueuingSystem
        ${Boost_LIBRARIES}
        QueuingSystemLib
)
