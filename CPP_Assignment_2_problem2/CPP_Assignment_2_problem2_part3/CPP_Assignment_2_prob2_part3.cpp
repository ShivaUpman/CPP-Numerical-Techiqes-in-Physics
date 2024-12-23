#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

// Function prototypes for derivatives
double dx_dt(double x, double y, double mu) {
    return mu * (x - x * x * x / 3 - y);
}

double dy_dt(double x, double mu) {
    return x / mu;
}

int main() {
    const double dt = 0.1;        // Timestep
    const int steps = 1000;      // Number of steps per \(\mu\)
    const double mu_start = 0.1; // Initial value of \(\mu\)
    const double mu_end = 4.0;   // Final value of \(\mu\)
    const double mu_step = 0.1;  // Step size for \(\mu\)

    std::ofstream file("vary_mu_rk4_data.txt");

    if (!file) {
        std::cerr << "Error opening output file.\n";
        return 1;
    }

    file << std::fixed << std::setprecision(6);

    for (double mu = mu_start; mu <= mu_end; mu += mu_step) {
        double x = 1.0, y = 0.0, t = 0.0;

        for (int i = 0; i < steps; ++i) {
            // Write \(\mu\), \(x\), \(y\), and \(t\) to file
            file << mu << " " << x << " " << y << " " << t << "\n";

            // RK4 calculations
            double k1_x = dx_dt(x, y, mu);
            double k1_y = dy_dt(x, mu);

            double k2_x = dx_dt(x + 0.5 * dt * k1_x, y + 0.5 * dt * k1_y, mu);
            double k2_y = dy_dt(x + 0.5 * dt * k1_x, mu);

            double k3_x = dx_dt(x + 0.5 * dt * k2_x, y + 0.5 * dt * k2_y, mu);
            double k3_y = dy_dt(x + 0.5 * dt * k2_x, mu);

            double k4_x = dx_dt(x + dt * k3_x, y + dt * k3_y, mu);
            double k4_y = dy_dt(x + dt * k3_x, mu);

            double dx = (k1_x + 2 * k2_x + 2 * k3_x + k4_x) / 6.0;
            double dy = (k1_y + 2 * k2_y + 2 * k3_y + k4_y) / 6.0;

            x += dx * dt;
            y += dy * dt;
            t += dt;
        }
        file << "\n"; // Separate data for different \(\mu\) values
    }

    file.close();
    std::cout << "Data written to vary_mu_rk4_data.txt\n";
    return 0;
}
