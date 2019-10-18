#ifndef CONTINUOUSSTOCHASTICQUEUINGSYSTEM_HELPER_QUEUE_H
#define CONTINUOUSSTOCHASTICQUEUINGSYSTEM_HELPER_QUEUE_H


#include <memory>
#include <deque>
#include <mutex>
#include <condition_variable>

namespace queuing_system {
    class customer;

    class helper_queue {
    public:
        helper_queue();

        void add_customer(const std::shared_ptr<customer> &customer);
        std::shared_ptr<customer> get_customer();
        void stop();
        void reset();

    private:
        std::deque<std::shared_ptr<customer>> customers;
        std::mutex customers_mutex;
        std::condition_variable customer_condition_variable;
        bool is_running;
    };
}


#endif //CONTINUOUSSTOCHASTICQUEUINGSYSTEM_HELPER_QUEUE_H
