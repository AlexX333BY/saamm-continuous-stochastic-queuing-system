#include "time_generator.h"

using namespace queuing_system;

time_generator::time_generator(const double intensity, const std::chrono::milliseconds& max_time)
    : maximum_time(max_time), random_generator(std::random_device()()), distribution(intensity)
{ }

std::chrono::nanoseconds time_generator::operator()() {
    return std::chrono::nanoseconds((int64_t)(maximum_time.count() * distribution(random_generator)));
}
