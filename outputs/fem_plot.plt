set pm3d map
set size ratio -1
set datafile separator ','
set key autotitle columnhead

splot 'fem_soln.csv' u 1:2:3