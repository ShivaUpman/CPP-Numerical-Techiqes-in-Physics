set term gif animate delay 10 loop 0 size 800,600
set xlabel 'X'
set ylabel 'Y'
set zlabel 'Z'
set title 'Lorenz Attractor'

# Set up view
set view 60, 30, 1, 1

# Generate animation for rho = 28 (Euler method)
set output 'lorenz_rho28_euler.png'
set title 'Lorenz Attractor (rho=28 - Euler)'
splot 'lorenz_rho28_euler.dat' using 2:3:4 with lines lw 2 title "Euler - rho=28"

# Generate animation for rho = 28 (RK4 method)
set output 'lorenz_rho28_rk4.png'
set title 'Lorenz Attractor (rho=28 - RK4)'
splot 'lorenz_rho28_rk4.dat' using 2:3:4 with lines lw 2 title "RK4 - rho=28"

# Generate animation for rho = 14 (RK4 method)
set output 'lorenz_rho14.png'
set title 'Lorenz Attractor (rho=14)'
splot 'lorenz_rho14.dat' using 2:3:4 with lines lw 2 title "RK4 - rho=14"

# Generate animation for rho = 99.96 (RK4 method)
set output 'lorenz_rho99_96.png'
set title 'Lorenz Attractor (rho=99.96)'
splot 'lorenz_rho99.96.dat' using 2:3:4 with lines lw 2 title "RK4 - rho=99.96"

# Generate comparison of two trajectories (rho = 28)
set output 'compare_trajectories.png'
set title 'Comparing Two Trajectories (rho = 28)'

splot 'lorenz_compare_trajectories.dat' using 2:3:4 with lines lw 2 title "Trajectory 1", \
     'lorenz_compare_trajectories.dat' using 5:6:7 with lines lw 2 title "Trajectory 2"

# Add a message for completion
print "Animations created successfully!"
