#ifndef CONTINUOUSSTOCHASTICQUEUINGSYSTEM_SERVER_H
#define CONTINUOUSSTOCHASTICQUEUINGSYSTEM_SERVER_H


#include "runnable.h"
#include "helper_queue.h"

namespace queuing_system {
    class server : public runnable {
    public:
        server(const std::chrono::milliseconds& serve_time, const std::shared_ptr<helper_queue>& queue);

        size_t get_served_customers_count() const;

    protected:
        void on_stop() final;
        void thread_routine() final;

    private:
        const std::chrono::milliseconds customer_serve_time;
        std::shared_ptr<helper_queue> customers_queue;
        size_t served_count;

    };
}


#endif //CONTINUOUSSTOCHASTICQUEUINGSYSTEM_SERVER_H
