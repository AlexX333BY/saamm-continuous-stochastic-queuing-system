#ifndef CONTINUOUSSTOCHASTICQUEUINGSYSTEM_TIME_GENERATOR_H
#define CONTINUOUSSTOCHASTICQUEUINGSYSTEM_TIME_GENERATOR_H


#include <chrono>
#include <random>

namespace queuing_system {
    class time_generator {
    public:
        time_generator(const double intensity, const std::chrono::milliseconds& max_time);

        std::chrono::milliseconds operator()();

    private:
        std::mt19937 random_generator;
        std::exponential_distribution<> distribution;
        const std::chrono::milliseconds maximum_time;
    };
}


#endif //CONTINUOUSSTOCHASTICQUEUINGSYSTEM_TIME_GENERATOR_H
