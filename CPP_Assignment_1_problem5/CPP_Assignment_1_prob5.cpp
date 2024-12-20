#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

// Define the function f(x, y) as given in the problem
double f(double x, double y) {
    return pow(x, 3) * exp(-2 * x) - 2 * y;
}

// Exact solution y(x) as given in the problem
double exact_solution(double x) {
    return exp(-2 * x) * (pow(x, 4) + 4) / 4;
}

// Runge-Kutta 4th Order Method
void runge_kutta_4(double (*f)(double, double), double y0, double x0, double h, int n_steps, const std::string& filename) {
    double x = x0;
    double y = y0;

    // Open the file to write the results
    std::ofstream outfile(filename);

    // Write the header
    outfile << "# x    y (RK4)    Exact y    Error" << std::endl;

    // Store the initial condition
    outfile << std::fixed << std::setprecision(6) << x << " " << y << " " << exact_solution(x) << " 0.000000" << std::endl;

    // Apply RK4 for each step
    for (int i = 0; i < n_steps; ++i) {
        double k1 = h * f(x, y);
        double k2 = h * f(x + h / 2, y + k1 / 2);
        double k3 = h * f(x + h / 2, y + k2 / 2);
        double k4 = h * f(x + h, y + k3);

        // Update y and x for the next step
        y = y + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        x = x + h;

        // Calculate exact solution and error
        double exact_y = exact_solution(x);
        double error = fabs(y - exact_y);

        // Write the results to the file
        outfile << std::fixed << std::setprecision(6) << x << " " << y << " " << exact_y << " " << error << std::endl;
    }

    // Close the file
    outfile.close();
}

int main() {
    // Initial conditions
    double x0 = 0.0;   // Initial x value
    double y0 = 1.0;   // Initial y value
    double h = 0.1;    // Step size
    int n_steps = 10;  // Number of steps (to reach x = 1.0)

    // File to store the results for Gnuplot
    std::string filename = "rk4_results.txt";

    // Solve the differential equation using the RK4 method and write the results to a file
    runge_kutta_4(f, y0, x0, h, n_steps, filename);

    std::cout << "Runge-Kutta 4 Results saved in " << filename << std::endl;

    return 0;
}
