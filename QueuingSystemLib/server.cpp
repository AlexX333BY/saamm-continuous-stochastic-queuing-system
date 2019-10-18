#include "server.h"
#include "customer.h"

using namespace queuing_system;

server::server(const double intensity, const std::chrono::milliseconds& max_time,
        const std::shared_ptr<helper_queue>& queue)
    : runnable(), generator(intensity, max_time), customers_queue(queue), served_count(0)
{ }

size_t server::get_served_customers_count() const
{
    return served_count;
}

void server::on_stop()
{ }

void server::thread_routine()
{
    while (is_running()) {
        std::shared_ptr<customer> serving_customer;
        do {
            serving_customer = customers_queue->get_customer();
        } while (is_running() && !serving_customer);

        if (is_running() && serving_customer) {
            std::this_thread::sleep_for(generator());
            serving_customer->notify_processed();
            serving_customer.reset();
            ++served_count;
        }
    }
}

void server::reset()
{
    stop();
    served_count = 0;
}
