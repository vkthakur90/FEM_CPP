#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include "fem_solver.hpp"   // your header that defines template<class Type, size_t N> FemSolver

namespace py = pybind11;

// Helper to register one instantiation
// General binding function template
template <typename Type, size_t N>
void register_fem_solver(py::module &m, const std::string &suffix) {
    using Solver = FemSolver<Type, N>;
    std::string pyname = "FemSolver_" + suffix;
    
    py::class_<Solver>(m, pyname.c_str())
        .def(py::init<>(),
             "Construct a FemSolver")
        .def_property("length_x", nullptr, &Solver::set_length_x)
        .def_property("length_y", nullptr, &Solver::set_length_y)             
        .def_property("k_xx", nullptr, &Solver::set_k_xx)
        .def_property("k_xy", nullptr, &Solver::set_k_xy)
        .def_property("k_yy", nullptr, &Solver::set_k_yy)
        .def_property("q_rate", nullptr, &Solver::set_q_rate)
        .def_property("boundary_top", nullptr, &Solver::set_boundary_top)
        .def_property("boundary_bottom", nullptr, &Solver::set_boundary_bottom)
        .def_property("boundary_left", nullptr, &Solver::set_boundary_left)
        .def_property("boundary_right", nullptr, &Solver::set_boundary_right)
        .def("compute", &Solver::compute,
             "Run the solver (assemble & conjugate gradient).")
        .def("write_to_file", &Solver::write_to_file, py::arg("filename"),
             "Dump the solution (x,y,T) to a file.");
}

PYBIND11_MODULE(femsolver, m) {
    m.doc() = "pybind11 bindings for FemSolver<Type, N>";

    // float instantiations
    register_fem_solver<float, 10>(m,   "f10");
    register_fem_solver<float, 100>(m,  "f100");
    register_fem_solver<float, 1000>(m, "f1000");

    // double instantiations
    register_fem_solver<double, 10>(m,   "d10");
    register_fem_solver<double, 100>(m,  "d100");
    register_fem_solver<double, 1000>(m, "d1000");
}