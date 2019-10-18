#include "model_parameters_parser.h"
#include <sstream>

const std::string model_parameters_parser::TIME_INTERVAL_ARG("interval-length"),
    model_parameters_parser::TIME_INTERVALS_COUNT_ARG("intervals-count"),
    model_parameters_parser::CUSTOMERS_COUNT_ARG("customers"),
    model_parameters_parser::SERVERS_COUNT_ARG("servers"),
    model_parameters_parser::CUSTOMER_INTENSITY_ARG("customer-intensity"),
    model_parameters_parser::SERVER_INTENSITY_ARG("server-intensity"),
    model_parameters_parser::HELP_ARG("help");

model_parameters_parser::model_parameters_parser(int argc, char **argv)
    : args_count(argc),
    args(argv),
    time_interval(0),
    time_intervals_count(0),
    customers_count(0),
    servers_count(0),
    customer_intensity(0),
    server_intensity(0),
    desc("Discrete-stohastic queuing system model")
{
    desc.add_options()
        (
            HELP_ARG.c_str(),
            "Print help")
        (
            TIME_INTERVAL_ARG.c_str(),
            boost::program_options::value<unsigned int>(&time_interval),
            "Time interval length in milliseconds"
        )
        (
            TIME_INTERVALS_COUNT_ARG.c_str(),
            boost::program_options::value<unsigned int>(&time_intervals_count),
            "Time intervals count to model")
        (
            CUSTOMERS_COUNT_ARG.c_str(),
            boost::program_options::value<size_t>(&customers_count)->default_value(6),
            "Customers count"
        )
        (
            SERVERS_COUNT_ARG.c_str(),
            boost::program_options::value<size_t>(&servers_count)->default_value(2),
            "Servers count"
        )
        (
            CUSTOMER_INTENSITY_ARG.c_str(),
            boost::program_options::value<double>(&customer_intensity)->default_value(2.5),
            "Customer intensity"
        )
        (
            SERVER_INTENSITY_ARG.c_str(),
            boost::program_options::value<double>(&server_intensity)->default_value(9),
            "Server intensity"
        );
}

model_parameters_parser::parse_result model_parameters_parser::parse()
{
    parse_result result = parse_result::wrong_arguments;
    try {
        boost::program_options::store(boost::program_options::parse_command_line(args_count, args, desc), parser);
        boost::program_options::notify(parser);

        const bool has_help = this->has_help(),
            has_time_interval = this->has_time_interval(),
            has_time_intervals_count = this->has_time_intervals_count();

        if (has_help && !has_time_interval && !has_time_intervals_count) {
            result = parse_result::help;
        }

        if (has_time_interval && has_time_intervals_count && !has_help) {
            result = parse_result::ok;
        }
    } catch (const std::exception &) {
        result = parse_result::wrong_arguments;
    }

    return result;
}

bool model_parameters_parser::has_help() const
{
    return parser.count(HELP_ARG) > 0;
}


bool model_parameters_parser::has_time_intervals_count() const
{
    return parser.count(TIME_INTERVALS_COUNT_ARG) > 0;
}

bool model_parameters_parser::has_time_interval() const
{
    return parser.count(TIME_INTERVAL_ARG) > 0;
}


std::string model_parameters_parser::get_help_message() const
{
    std::ostringstream msg_stream;
    desc.print(msg_stream);
    return msg_stream.str();
}

size_t model_parameters_parser::get_servers_count() const
{
    return servers_count;
}

double model_parameters_parser::get_customer_intensity() const
{
    return customer_intensity;
}

size_t model_parameters_parser::get_customers_count() const
{
    return customers_count;
}

double model_parameters_parser::get_server_intensity() const
{
    return server_intensity;
}

std::chrono::milliseconds model_parameters_parser::get_time_interval() const
{
    return std::chrono::milliseconds(time_interval);
}

unsigned int model_parameters_parser::get_time_intervals_count() const
{
    return time_intervals_count;
}
