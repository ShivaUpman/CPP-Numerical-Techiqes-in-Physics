# Gnuplot script to plot Euler's method vs exact solution for each step size (h)

# Set plot title and labels
set xlabel "x"
set ylabel "y"
set grid

# Set line styles
set style line 1 lc rgb "blue" pt 7 ps 1.5 lt 1 lw 2 # Euler's method
set style line 2 lc rgb "red" pt 5 ps 1.5 lt 1 lw 2 # Exact solution

# Set the output image format (optional: save as PNG)
set terminal pngcairo enhanced font 'Verdana,10'

# Plot for h = 0.1
set output 'euler_method_h_0.1.png'
set title "Euler's Method vs Exact Solution (h = 0.1)"
plot "euler_data_h_0.100000.dat" using 1:2 with linespoints linestyle 1 title "Euler (h=0.1)", \
     "euler_data_h_0.100000.dat" using 1:3 with lines linestyle 2 title "Exact Solution"

# Plot for h = 0.05
set output 'euler_method_h_0.05.png'
set title "Euler's Method vs Exact Solution (h = 0.05)"
plot "euler_data_h_0.050000.dat" using 1:2 with linespoints linestyle 1 title "Euler (h=0.05)", \
     "euler_data_h_0.050000.dat" using 1:3 with lines linestyle 2 title "Exact Solution"

# Plot for h = 0.025
set output 'euler_method_h_0.025.png'
set title "Euler's Method vs Exact Solution (h = 0.025)"
plot "euler_data_h_0.025000.dat" using 1:2 with linespoints linestyle 1 title "Euler (h=0.025)", \
     "euler_data_h_0.025000.dat" using 1:3 with lines linestyle 2 title "Exact Solution"

# Unset output (optional: for interactive mode)
unset output
