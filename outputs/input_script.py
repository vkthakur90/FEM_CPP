import femsolver as fs

# create solver
sol = fs.FemSolver_f100() 

sol.length_x(1.0)
sol.length_y(2.0)

# set material tensors and boundary conditions
sol.k_xx(0.1)
sol.k_xy(0.0)
sol.k_yy(0.1)
sol.q_rate(1.0)

sol.boundary_top(0.0)
sol.boundary_bottom(0.0)
sol.boundary_left(0.0)
sol.boundary_right(0.0)

# run the FEM solve
sol.compute()

# write output to text file
sol.write_to_file("fem_soln.csv")

