# Gnuplot script for animating RK4 trajectory with varying µ

set term gif animate delay 10 size 800, 600
set output "animated_trajectory_vary_mu.gif"

set xrange [-2:2]
set yrange [-2:2]
set title "y vs x Trajectory Animation with Varying µ"
set xlabel "x"
set ylabel "y"

# Define initial and final µ values
mu_startx10 = 1
mu_endx10 = 40

# Loop through the range of µ
do for [mux10=mu_startx10:mu_endx10] {
    mu = mux10/10.0
    set title sprintf("y vs x Trajectory (µ = %.2f)", mu)
    plot "vary_mu_rk4_data.txt" using ($1==mu ? $2 : 1/0):($1==mu ? $3 : 1/0) with lines title "Trajectory (RK4)"
}
