#include <iostream>
#include <fstream>
#include <cmath>

const double mu = 7.0;   // Parameter value
const double dt = 0.1;   // Timestep
const int steps = 1000;  // Number of steps

int main() {
    // Initial conditions
    double x = 1.0, y = 0.0, t = 0.0;

    // Open files for output
    std::ofstream xyFile("xy_data.txt");
    std::ofstream xtFile("xt_data.txt");
    std::ofstream ytFile("yt_data.txt");

    if (!xyFile || !xtFile || !ytFile) {
        std::cerr << "Error opening output files.\n";
        return 1;
    }

    // Euler's method loop
    for (int i = 0; i < steps; ++i) {
        double dx = mu * (x - x * x * x / 3 - y);
        double dy = x / mu;

        // Write data to files
        xyFile << x << " " << y << "\n";
        xtFile << t << " " << x << "\n";
        ytFile << t << " " << y << "\n";

        // Update variables
        x += dx * dt;
        y += dy * dt;
        t += dt;
    }

    // Close files
    xyFile.close();
    xtFile.close();
    ytFile.close();

    std::cout << "Data written to xy_data.txt, xt_data.txt, yt_data.txt.\n";
    return 0;
}
