set(HEADERS
        runnable.h
        helper_queue.h
)

set(SOURCES
        runnable.cpp
        helper_queue.cpp
)

add_library(QueuingSystemLib ${HEADERS} ${SOURCES})
set_target_properties(QueuingSystemLib PROPERTIES OUTPUT_NAME "libqueuingsystem")
