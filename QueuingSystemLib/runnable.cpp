#include "runnable.h"

using namespace queuing_system;

runnable::runnable() : thread(), should_run(false)
{ }

runnable::~runnable()
{
    stop();
}

void runnable::run()
{
    if (!should_run) {
        should_run = true;
        thread = std::make_unique<std::thread>(&runnable::thread_routine, shared_from_this());
    }
}

void runnable::signal_to_stop()
{
    if (should_run) {
        should_run = false;
        on_stop();
    }
}

void runnable::join()
{
    if (!should_run && thread) {
        thread->join();
        thread.reset();
    }
}

void runnable::stop()
{
    signal_to_stop();
    join();
}

bool runnable::is_running() const
{
    return should_run;
}
