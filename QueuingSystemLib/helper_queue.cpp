#include "helper_queue.h"

using namespace queuing_system;

helper_queue::helper_queue() : customers(), customers_mutex(), customer_condition_variable(), is_running(true)
{ }

void helper_queue::stop()
{
    if (is_running) {
        is_running = false;
        std::unique_lock<std::mutex> lock(customers_mutex);
        customers.clear();
        customer_condition_variable.notify_all();
    }
}

void helper_queue::add_customer(const std::shared_ptr<customer> &customer)
{
    if (is_running) {
        std::unique_lock<std::mutex> lock(customers_mutex);
        customers.push_back(customer);
        customer_condition_variable.notify_one();
    }
}

std::shared_ptr<customer> helper_queue::get_customer()
{
    std::shared_ptr<customer> result;

    if (is_running) {
        std::unique_lock<std::mutex> lock(customers_mutex);
        customer_condition_variable.wait(lock, [this] { return !is_running || !customers.empty(); });

        if (is_running) {
            result = customers.front();
            customers.pop_front();
        }
    }

    return result;
}

void helper_queue::reset()
{
    std::unique_lock<std::mutex> lock(customers_mutex);
    customers.clear();
    is_running = true;
}
