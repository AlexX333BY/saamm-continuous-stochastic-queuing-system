#ifndef CONTINUOUSSTOCHASTICQUEUINGSYSTEM_SERVER_H
#define CONTINUOUSSTOCHASTICQUEUINGSYSTEM_SERVER_H


#include "runnable.h"
#include "helper_queue.h"
#include "time_generator.h"
#include <chrono>

namespace queuing_system {
    class server : public runnable {
    public:
        server(const double intensity, const std::chrono::milliseconds& max_time, const std::shared_ptr<helper_queue>& queue);

        size_t get_served_customers_count() const;
        void reset() final;

    protected:
        void on_stop() final;
        void thread_routine() final;

    private:
        time_generator generator;
        std::shared_ptr<helper_queue> customers_queue;
        size_t served_count;
    };
}


#endif //CONTINUOUSSTOCHASTICQUEUINGSYSTEM_SERVER_H
