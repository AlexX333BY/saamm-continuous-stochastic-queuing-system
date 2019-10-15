set(HEADERS
        runnable.h
)

set(SOURCES
        runnable.cpp
)

add_library(QueuingSystemLib ${HEADERS} ${SOURCES})
set_target_properties(QueuingSystemLib PROPERTIES OUTPUT_NAME "libqueuingsystem")