import femsolver

# pick the templated version you need, e.g. float, N=100
Solver = femsolver.FemSolver_f100

# create solver
sol = Solver()    # len_x=1.0, len_y=2.0

sol.set_dimensions(1.0, 1.0)

# set material tensors and boundary conditions
sol.set_k_xx(0.1)
sol.set_k_xy(0.0)
sol.set_k_yy(0.1)
sol.set_q_rate(0.0)

sol.set_boundary_top(1)
sol.set_boundary_bottom(0)
sol.set_boundary_left(1)
sol.set_boundary_right(0)

# run the FEM solve
sol.compute()

# write output to text file
sol.write_to_file("fem_soln.csv")

