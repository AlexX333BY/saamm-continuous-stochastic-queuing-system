set(HEADERS
        runnable.h
        helper_queue.h
        customer.h
        server.h
)

set(SOURCES
        runnable.cpp
        helper_queue.cpp
        customer.cpp
        server.cpp
)

add_library(QueuingSystemLib ${HEADERS} ${SOURCES})
set_target_properties(QueuingSystemLib PROPERTIES OUTPUT_NAME "libqueuingsystem")
