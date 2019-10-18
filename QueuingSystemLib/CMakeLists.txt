find_package(Threads REQUIRED)

set(HEADERS
        runnable.h
        helper_queue.h
        customer.h
        server.h
        time_generator.h
)

set(SOURCES
        runnable.cpp
        helper_queue.cpp
        customer.cpp
        server.cpp
        time_generator.cpp
)

add_library(QueuingSystemLib ${HEADERS} ${SOURCES})
target_link_libraries(QueuingSystemLib ${CMAKE_THREAD_LIBS_INIT})

set_target_properties(QueuingSystemLib PROPERTIES OUTPUT_NAME "libqueuingsystem")
