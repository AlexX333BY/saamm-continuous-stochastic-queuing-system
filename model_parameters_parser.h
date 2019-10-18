#ifndef DISCRETESTOCHASTICQUEUINGSYSTEM_PARSER_H
#define DISCRETESTOCHASTICQUEUINGSYSTEM_PARSER_H


#include <boost/program_options.hpp>
#include <string>
#include <chrono>

class model_parameters_parser {
public:
    enum class parse_result {
        ok,
        wrong_arguments,
        help
    };

    model_parameters_parser(int argc, char** argv);

    parse_result parse();
    std::string get_help_message() const;

    std::chrono::milliseconds get_time_interval() const;
    size_t get_customers_count() const;
    size_t get_servers_count() const;
    double get_customer_intensity() const;
    double get_server_intensity() const;
    unsigned int get_time_intervals_count() const;

private:
    bool has_time_interval() const;
    bool has_time_intervals_count() const;
    bool has_help() const;

    boost::program_options::variables_map parser;
    boost::program_options::options_description desc;
    const int args_count;
    char** args;
    unsigned int time_interval, time_intervals_count;
    size_t customers_count, servers_count;
    double customer_intensity, server_intensity;

    static const std::string TIME_INTERVAL_ARG, TIME_INTERVALS_COUNT_ARG, CUSTOMERS_COUNT_ARG, SERVERS_COUNT_ARG,
        CUSTOMER_INTENSITY_ARG, SERVER_INTENSITY_ARG, HELP_ARG;
};


#endif //DISCRETESTOCHASTICQUEUINGSYSTEM_PARSER_H
