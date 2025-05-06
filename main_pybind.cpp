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
        .def("set_dimensions", &Solver::set_dimensions, py::arg("length_x"), py::arg("length_y"),
             "Set Dimension of 2D box with len_x and len_y")     
        .def("set_k_xx", &Solver::set_k_xx, py::arg("val"),
             "Set k_xx over the grid with value val.")
        .def("set_k_xy", &Solver::set_k_xy, py::arg("val"),
             "Set k_xy over the grid with value val.")
        .def("set_k_yy", &Solver::set_k_yy, py::arg("val"),
             "Set k_yy over the grid with value val.")
        .def("set_q_rate", &Solver::set_q_rate, py::arg("val"),
             "Set q_rate over the grid with value val.")
        .def("set_boundary_top", &Solver::set_boundary_top, py::arg("val"),
             "Set top boundary with value val.")
        .def("set_boundary_bottom", &Solver::set_boundary_bottom, py::arg("val"),
             "Set bottom boundary with value val.")
        .def("set_boundary_left", &Solver::set_boundary_left, py::arg("val"),
             "Set left boundary with a function f(x,y).")
        .def("set_boundary_right", &Solver::set_boundary_right, py::arg("val"),
             "Set right boundary with value val.")
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