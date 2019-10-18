#include "customer.h"

using namespace queuing_system;

customer::customer(const double intensity, const std::chrono::milliseconds& max_time,
        const std::shared_ptr<helper_queue>& queue)
    : total_wait_time(0),
    generator(intensity, max_time),
    customers_queue(queue),
    state_change_notify_cv(),
    state()
{ }

const std::chrono::nanoseconds& customer::get_total_wait_time() const
{
    return total_wait_time;
}

void customer::on_stop()
{
    state_change_notify_cv.notify_one();
}

void customer::notify_processed()
{
    state = customer_state::processed;
    state_change_notify_cv.notify_one();
}

void customer::thread_routine()
{
    while(is_running()) {
        std::mutex state_change_mutex;
        bool was_wait_for_produce_interrupted;

        state = customer_state::waiting;
        {
            std::unique_lock<std::mutex> lock(state_change_mutex);
            was_wait_for_produce_interrupted = state_change_notify_cv.wait_for(lock, generator(), [this] {
                return !is_running();
            });
        }

        if (!was_wait_for_produce_interrupted) {
            const std::chrono::time_point waiting_start_time_point = std::chrono::system_clock::now();

            customers_queue->add_customer(std::dynamic_pointer_cast<customer>(shared_from_this()));
            {
                std::unique_lock<std::mutex> lock(state_change_mutex);
                state_change_notify_cv.wait(lock, [this] {
                    return !is_running() || (state == customer_state::processed);
                });
            }

            if (is_running()) {
                total_wait_time += std::chrono::system_clock::now() - waiting_start_time_point;
            }
        }
    }
}

void customer::reset()
{
    stop();
    total_wait_time = std::chrono::nanoseconds(0);
}
