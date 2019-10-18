#ifndef CONTINUOUSSTOCHASTICQUEUINGSYSTEM_CLOSED_QUEUING_SYSTEM_H
#define CONTINUOUSSTOCHASTICQUEUINGSYSTEM_CLOSED_QUEUING_SYSTEM_H


#include <chrono>
#include <vector>
#include <memory>
#include "customer.h"
#include "server.h"

class closed_queuing_system {
public:
    struct run_result {
        double average_number_of_pending_customers;
        double average_response_time;
        double absolute_bandwidth;
    };

    closed_queuing_system(const size_t customers_count, const double customer_intensity, const size_t servers_count,
            const double server_intensity, const std::chrono::milliseconds& time_interval);

    run_result run_for(const size_t time_intervals_count);

private:
    std::vector<std::shared_ptr<queuing_system::customer>> customers;
    std::vector<std::shared_ptr<queuing_system::server>> servers;
    std::shared_ptr<queuing_system::helper_queue> queue;
    const std::chrono::milliseconds time_interval;
};


#endif //CONTINUOUSSTOCHASTICQUEUINGSYSTEM_CLOSED_QUEUING_SYSTEM_H
