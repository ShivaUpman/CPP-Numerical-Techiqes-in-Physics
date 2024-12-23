# Gnuplot script to visualize RK4 data

set term png size 800, 600
set output 'y_vs_x_rk4.png'
set title "y vs x (RK4)"
set xlabel "x"
set ylabel "y"
plot "xy_data_rk4.txt" using 1:2 with lines title "RK4 y vs x", \
     x - x**3 / 3 with lines title "y = x - x^3/3"

set output 'x_vs_t_rk4.png'
set title "x vs t (RK4)"
set xlabel "t"
set ylabel "x"
plot "xt_data_rk4.txt" using 1:2 with lines title "RK4 x vs t"

set output 'y_vs_t_rk4.png'
set title "y vs t (RK4)"
set xlabel "t"
set ylabel "y"
plot "yt_data_rk4.txt" using 1:2 with lines title "RK4 y vs t"

unset output

# Set the terminal for GIF output
set term gif animate delay 5 size 800, 600
set output "animated_trajectory_rk4.gif"

# Axes ranges and labels
set xrange [-2:2]
set yrange [-2:2]
set title "y vs x Trajectory Animation (RK4)"
set xlabel "x"
set ylabel "y"

# Loop through data points to create animation
do for [i=1:1000] {
    plot "xy_data_rk4.txt" every ::1::i using 1:2 with lines title "RK4 y vs x trajectory", \
         x - x**3 / 3 with lines title "y = x - x^3/3"
}
