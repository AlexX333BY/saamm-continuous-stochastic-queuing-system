#ifndef CONTINUOUSSTOCHASTICQUEUINGSYSTEM_RUNNABLE_H
#define CONTINUOUSSTOCHASTICQUEUINGSYSTEM_RUNNABLE_H


#include <thread>
#include <memory>

namespace queuing_system {
class runnable : public std::enable_shared_from_this<runnable> {
    public:
        runnable();
        virtual ~runnable();

        void run();
        void stop();
        bool is_running() const;

    protected:
        virtual void on_stop() = 0;
        virtual void thread_routine() = 0;

    private:
        std::unique_ptr<std::thread> thread;
        bool should_run;
    };
}


#endif //CONTINUOUSSTOCHASTICQUEUINGSYSTEM_RUNNABLE_H