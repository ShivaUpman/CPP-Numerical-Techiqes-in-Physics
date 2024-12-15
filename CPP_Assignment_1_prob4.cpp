#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Function for the differential equation: y' = x^3 * e^(-2x) - 2y
double f(double x, double y) {
    return pow(x, 3) * exp(-2 * x) - 2 * y;
}

double exact_solution(double x) {
    return exp(-2 * x) * (pow(x, 4) + 4)/4;
}

// Euler's method
void euler_method(double h, double x0, double y0, double x_end) {
    double x = x0;
    double y = y0;
    cout << "Step size: " << h << endl;
    cout << "x\tApproximate y\tExact y\tError" << endl;

    while (x <= x_end) {
        double exact_y = exact_solution(x);
        double error = fabs(y - exact_y);

        cout << fixed << setprecision(4) << x << "\t"
             << fixed << setprecision(4) << y << "\t"
             << fixed << setprecision(4) << exact_y << "\t"
             << fixed << setprecision(4) << error << endl;

        y += h * f(x, y);
        x += h;
    }
}

int main() {
    double x0 = 0.0;   // Initial x value
    double y0 = 1.0;   // Initial y value
    double x_end = 1.0; // End value of x

    double step_sizes[] = {0.1, 0.05, 0.025};

    for (double h : step_sizes) {
        euler_method(h, x0, y0, x_end);
        cout << endl;
    }

    return 0;
}