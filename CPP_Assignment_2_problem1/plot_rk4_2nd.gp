# Set common labels and grid
set xlabel "Time (t)"
set ylabel "y(t)"
set grid

# Set line styles (optional: customize colors, points, and line width)
set style line 1 lc rgb "blue" pt 7 ps 1.5 lt 1 lw 2 # Euler (h=0.1)
set style line 2 lc rgb "green" pt 7 ps 1.5 lt 1 lw 2 # Euler (h=0.01)
set style line 3 lc rgb "red" pt 7 ps 1.5 lt 1 lw 2 # RK4 (h=0.1)
set style line 4 lc rgb "black" pt 7 ps 1.5 lt 1 lw 2 # Exact Solution

# Plot Euler's method with h=0.1
set terminal pngcairo enhanced font 'Arial,10'
set output 'euler_h0.1_plot.png'
set title "Euler's Method (h=0.1) vs Exact Solution"
plot 'euler_h0.1.dat' with lines linestyle 1 title 'Euler (h=0.1)', \
     'exact_solution.dat' with lines linestyle 4 title 'Exact Solution'
unset output

# Plot Euler's method with h=0.01
set output 'euler_h0.01_plot.png'
set title "Euler's Method (h=0.01) vs Exact Solution"
plot 'euler_h0.01.dat' with lines linestyle 2 title 'Euler (h=0.01)', \
     'exact_solution.dat' with lines linestyle 4 title 'Exact Solution'
unset output

# Plot RK4 method with h=0.1
set output 'rk4_h0.1_plot.png'
set title "Runge-Kutta 4th Order (h=0.1) vs Exact Solution"
plot 'rk4_h0.1.dat' with lines linestyle 3 title 'RK4 (h=0.1)', \
     'exact_solution.dat' with lines linestyle 4 title 'Exact Solution'
unset output
