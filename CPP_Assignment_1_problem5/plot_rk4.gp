# Gnuplot script to plot Euler's method vs exact solution

# Set plot title and labels
set title "Runge-Kutta Method vs Exact Solution"
set xlabel "x"
set ylabel "y"
set grid

# Set line styles
set style line 1 lc rgb "blue" pt 7 ps 1.5 lt 1 lw 2 # RK4 method
set style line 2 lc rgb "red" pt 5 ps 1.5 lt 1 lw 2 # Exact solution

# Set the output image format (optional: save as PNG)
set terminal pngcairo enhanced font 'Verdana,10'
set output 'rk4_method_vs_exact_solution.png'

# Plot the data file for the RK4 results and exact solution
plot "rk4_results.txt" using 1:2 with linespoints linestyle 1 title "RK4 (h=0.1)", \
     "rk4_results.txt" using 1:3 with lines linestyle 2 title "Exact Solution"

# Unset output to display in terminal (optional)
unset output
