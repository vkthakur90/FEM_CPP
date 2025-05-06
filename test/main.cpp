#ifndef MAX_N
#define MAX_N 100
#endif

#include "parse_input.hpp"
#include "fem_solver.hpp"
#include <memory>
#include <iostream>


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
        
        FemSolver<double, MAX_N> solver(params["len_x"], params["len_y"]);
        
        solver.set_k_xx([&params](double x, double y){
            return params["k_xx"];
        });
        
        solver.set_k_xy([&params](double x, double y){
            return params["k_xy"];
        });
        
        solver.set_k_yy([&params](double x, double y){
            return params["k_yy"];
        });
        
        solver.set_q_rate([&params](double x, double y){
            return params["q_rate"];
        });
        
        solver.set_boundary_top([&params](double x, double y){
            return params["top"];
        });
        
        solver.set_boundary_top([&params](double x, double y){
            return params["top"];
        });
        
        solver.set_boundary_bottom([&params](double x, double y){
            return params["bottom"];
        });

        solver.set_boundary_left([&params](double x, double y){
            return params["left"];
        });

        solver.set_boundary_right([&params](double x, double y){
            return params["right"];
        });
        
        solver.compute();
        
        solver.write_to_file(output_filename);        
    }
    catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

