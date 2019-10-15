set(HEADERS
        runnable.h
        helper_queue.h
        customer.h
)

set(SOURCES
        runnable.cpp
        helper_queue.cpp
        customer.cpp
)

add_library(QueuingSystemLib ${HEADERS} ${SOURCES})
set_target_properties(QueuingSystemLib PROPERTIES OUTPUT_NAME "libqueuingsystem")
