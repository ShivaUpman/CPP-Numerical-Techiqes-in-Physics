#include <iostream>
#include <fstream>
#include <cmath>

const double mu = 7.0;   // Parameter value
const double dt = 0.1;   // Timestep
const int steps = 1000;  // Number of steps

// Functions for derivatives
double dx_dt(double x, double y) {
    return mu * (x - x * x * x / 3 - y);
}

double dy_dt(double x) {
    return x / mu;
}

int main() {
    // Initial conditions
    double x = 1.0, y = 0.0, t = 0.0;

    // Open files for output
    std::ofstream xyFile("xy_data_rk4.txt");
    std::ofstream xtFile("xt_data_rk4.txt");
    std::ofstream ytFile("yt_data_rk4.txt");

    if (!xyFile || !xtFile || !ytFile) {
        std::cerr << "Error opening output files.\n";
        return 1;
    }

    // RK4 method loop
    for (int i = 0; i < steps; ++i) {
        // Write current state to files
        xyFile << x << " " << y << "\n";
        xtFile << t << " " << x << "\n";
        ytFile << t << " " << y << "\n";

        // RK4 calculation for x
        double k1_x = dx_dt(x, y);
        double k1_y = dy_dt(x);

        double k2_x = dx_dt(x + 0.5 * dt * k1_x, y + 0.5 * dt * k1_y);
        double k2_y = dy_dt(x + 0.5 * dt * k1_x);

        double k3_x = dx_dt(x + 0.5 * dt * k2_x, y + 0.5 * dt * k2_y);
        double k3_y = dy_dt(x + 0.5 * dt * k2_x);

        double k4_x = dx_dt(x + dt * k3_x, y + dt * k3_y);
        double k4_y = dy_dt(x + dt * k3_x);

        double dx = (k1_x + 2 * k2_x + 2 * k3_x + k4_x) / 6.0;
        double dy = (k1_y + 2 * k2_y + 2 * k3_y + k4_y) / 6.0;

        // Update variables
        x += dx * dt;
        y += dy * dt;
        t += dt;
    }

    // Close files
    xyFile.close();
    xtFile.close();
    ytFile.close();

    std::cout << "Data written to xy_data_rk4.txt, xt_data_rk4.txt, yt_data_rk4.txt.\n";
    return 0;
}
