#ifndef CONTINUOUSSTOCHASTICQUEUINGSYSTEM_CUSTOMER_H
#define CONTINUOUSSTOCHASTICQUEUINGSYSTEM_CUSTOMER_H


#include "runnable.h"
#include "helper_queue.h"
#include "time_generator.h"
#include <chrono>
#include <condition_variable>

namespace queuing_system {
    class customer : public runnable {
    public:
        customer(const double intensity, const std::chrono::milliseconds& max_time,
                const std::shared_ptr<helper_queue>& queue);

        const std::chrono::nanoseconds& get_total_wait_time() const;
        void notify_processed();
        void reset() final;

    protected:
        void on_stop() final;
        void thread_routine() final;

    private:
        enum class customer_state {
            waiting,
            processed
        };

        std::chrono::nanoseconds total_wait_time;
        std::shared_ptr<helper_queue> customers_queue;
        std::condition_variable state_change_notify_cv;
        customer_state state;
        time_generator generator;
    };
}


#endif //CONTINUOUSSTOCHASTICQUEUINGSYSTEM_CUSTOMER_H
