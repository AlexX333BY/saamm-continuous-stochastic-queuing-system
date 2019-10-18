#include <iostream>
#include "closed_queuing_system.h"
#include "model_parameters_parser.h"

int main(int argc, char** argv)
{
    int result_code = 1;
    model_parameters_parser parser(argc, argv);

    switch(parser.parse()) {
        case model_parameters_parser::parse_result::ok:
        {
            closed_queuing_system qs(parser.get_customers_count(), parser.get_customer_intensity(),
                                     parser.get_servers_count(), parser.get_server_intensity(), parser.get_time_interval());
            closed_queuing_system::run_result qs_result = qs.run_for(parser.get_time_intervals_count());

            std::cout << "Average number of pending customers: " << qs_result.average_number_of_pending_customers << std::endl
                      << "Average response time: " << qs_result.average_response_time << std::endl
                      << "Absolute bandwidth: " << qs_result.absolute_bandwidth << std::endl;
            result_code = 0;
            break;
        }
        case model_parameters_parser::parse_result::help:
            std::cout << parser.get_help_message() << std::endl;
            result_code = 0;
            break;
        case model_parameters_parser::parse_result::wrong_arguments:
            std::cerr << parser.get_help_message() << std::endl;
            result_code = 1;
            break;
    }

    return result_code;
}
