#ifndef MAX_N
#define MAX_N 100
#endif

#include "read_inputs.hpp"
#include "subroutines.hpp"
#include <memory>
#include <iostream>

#ifdef DEBUG
#include "test/test.hpp"
#endif

void print_usage(const char* progname) {
    std::cerr
        << "Usage: " << progname
        << " <param_file> <output_filename>\n"
        << "\n"
        << "  <param_file>     Path to your configuration file containing lines of\n"
        << "                    the form: set key = value;\n"
        << "  <output_filename>  Path where results will be written.\n"
        << std::endl;
}

int main(int argc, char** argv){
    // Expect exactly two extra args: argv[1]=param file, argv[2]=output name
    if (argc != 3) {
        std::cerr << "Error: Incorrect number of command-line arguments.\n";
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    const char* param_file     = argv[1];
    const char* output_filename = argv[2];

    try {
        auto data_ptr = std::make_unique<ProgramData<double, MAX_N>>();
        auto params   = parse_params_from_file<double>(param_file);
        
        ProgramData_readInputs(data_ptr, params);
        ProgramData_compute(data_ptr);
        ProgramData_displayResults(data_ptr, output_filename);
    }
    catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

