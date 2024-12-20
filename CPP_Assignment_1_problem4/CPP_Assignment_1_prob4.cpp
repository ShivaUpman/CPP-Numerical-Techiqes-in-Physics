#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>  

using namespace std;

// Function for the differential equation: y' = x^3 * e^(-2x) - 2y
double f(double x, double y) {
    return pow(x, 3) * exp(-2 * x) - 2 * y;
}

// Exact solution of the differential equation
double exact_solution(double x) {
    return exp(-2 * x) * (pow(x, 4) + 4) / 4;
}

// Euler's method
void euler_method(double h, double x0, double y0, double x_end, const string& filename) {
    double x = x0;
    double y = y0;
    
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Error opening file!" << endl;
        return;
    }
    
    // Write header to the file
    outfile << "# x \t\t Approximate y \t Exact y \t Error" << endl;

    // Perform Euler's method and output results to file
    while (x <= x_end) {
        double exact_y = exact_solution(x);
        double error = fabs(y - exact_y);

        // Write data to the file
        outfile << fixed << setprecision(4) << x << "\t"
                << fixed << setprecision(4) << y << "\t"
                << fixed << setprecision(4) << exact_y << "\t"
                << fixed << setprecision(4) << error << endl;

        y += h * f(x, y);  // Euler update
        x += h;  // Increment x
    }

    outfile.close();
}

int main() {
    double x0 = 0.0;   // Initial x value
    double y0 = 1.0;   // Initial y value
    double x_end = 1.0; // End value of x

    // Step sizes to test
    double step_sizes[] = {0.1, 0.05, 0.025};

    // Loop through each step size and call Euler's method
    for (double h : step_sizes) {
        // Generate output filename for each step size
        string filename = "euler_data_h_" + to_string(h) + ".dat";
        euler_method(h, x0, y0, x_end, filename);
        cout << "Data for step size h = " << h << " saved to " << filename << endl;
        cout << endl;
    }

    return 0;
}
