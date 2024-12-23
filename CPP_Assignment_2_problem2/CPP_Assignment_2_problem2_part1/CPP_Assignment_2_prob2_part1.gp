set term png size 800, 600
set output 'y_vs_x.png'
set title "y vs x"
set xlabel "x"
set ylabel "y"
plot "xy_data.txt" using 1:2 with lines title "y vs x", \
     x - x**3 / 3 with lines title "y = x - x^3/3"

set output 'x_vs_t.png'
set title "x vs t"
set xlabel "t"
set ylabel "x"
plot "xt_data.txt" using 1:2 with lines title "x vs t"

set output 'y_vs_t.png'
set title "y vs t"
set xlabel "t"
set ylabel "y"
plot "yt_data.txt" using 1:2 with lines title "y vs t"

unset output

# Set the terminal for GIF output
set term gif animate delay 5 size 800, 600
set output "animated_trajectory.gif"

# Axes ranges and labels
set xrange [-2:2]
set yrange [-2:2]
set title "y vs x Trajectory Animation"
set xlabel "x"
set ylabel "y"

# Loop through data points to create animation
do for [i=1:1000] {
    plot "xy_data.txt" every ::1::i using 1:2 with lines title "y vs x trajectory", \
         x - x**3 / 3 with lines title "y = x - x^3/3"
}
