#include "closed_queuing_system.h"

closed_queuing_system::closed_queuing_system(const size_t customers_count, const double customer_intensity,
    const size_t servers_count, const double server_intensity, const std::chrono::milliseconds &time_interval)
    : time_interval(time_interval), customers(), servers(), queue(std::make_shared<queuing_system::helper_queue>())
{
    customers.reserve(customers_count);
    for (size_t customer = 0; customer < customers_count; ++customer) {
        customers.push_back(std::make_shared<queuing_system::customer>(customer_intensity, time_interval, queue));
    }
    servers.reserve(servers_count);
    for (size_t server = 0; server < servers_count; ++server) {
        servers.push_back(std::make_shared<queuing_system::server>(server_intensity, time_interval, queue));
    }
}

closed_queuing_system::run_result closed_queuing_system::run_for(const size_t time_intervals_count)
{
    for (const std::shared_ptr<queuing_system::customer>& customer : customers) {
        customer->run();
    }
    for (const std::shared_ptr<queuing_system::server>& server : servers) {
        server->run();
    }

    std::this_thread::sleep_for(time_intervals_count * time_interval);

    for (const std::shared_ptr<queuing_system::server>& server : servers) {
        server->signal_to_stop();
    }
    queue->stop();
    for (const std::shared_ptr<queuing_system::customer>& customer : customers) {
        customer->signal_to_stop();
    }
    for (const std::shared_ptr<queuing_system::server>& server : servers) {
        server->join();
    }
    for (const std::shared_ptr<queuing_system::customer>& customer : customers) {
        customer->join();
    }

    run_result result{};

    size_t total_served = 0;
    for (const std::shared_ptr<queuing_system::server>& server : servers) {
        total_served += server->get_served_customers_count();
    }
    result.absolute_bandwidth = (double)total_served / time_intervals_count;

    std::chrono::nanoseconds total_response_time(0);
    for (const std::shared_ptr<queuing_system::customer>& customer : customers) {
        total_response_time += customer->get_total_response_time();
    }
    result.average_response_time
        = (double)std::chrono::duration_cast<std::chrono::milliseconds>(total_response_time).count()
            / total_served
            / time_interval.count();

    result.average_number_of_pending_customers = result.average_response_time * result.absolute_bandwidth;

    for (const std::shared_ptr<queuing_system::customer>& customer : customers) {
        customer->reset();
    }
    for (const std::shared_ptr<queuing_system::server>& server : servers) {
        server->reset();
    }
    queue->reset();

    return result;
}
