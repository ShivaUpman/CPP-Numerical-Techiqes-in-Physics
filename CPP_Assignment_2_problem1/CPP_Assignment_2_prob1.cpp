#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

// Define the system of first-order ODEs for the damped-driven harmonic oscillator
// y'' + 4y' + 3y = sin(x) + 2cos(x)
void f(double t, double z1, double z2, double &dz1, double &dz2) {
    dz1 = z2;
    dz2 = sin(t) + 2 * cos(t) - 4 * z2 - 3 * z1;
}

// Exact solution 
double exact_solution(double t) {
    return 0.75 * exp(-t) + 0.5 * sin(t) + 0.25 * exp(-3 * t) ;
}

// Euler method to solve the system of first-order ODEs
void euler_method(double h, double t_max, double y0, double yp0, double* time, double* y_vals, int n) {
    double z1 = y0, z2 = yp0;
    
    for (int i = 0; i < n; ++i) {
        time[i] = i * h;
        y_vals[i] = z1;
        
        // Update z1 and z2 using Euler's method
        double dz1, dz2;
        f(time[i], z1, z2, dz1, dz2);
        
        z1 += h * dz1;
        z2 += h * dz2;
    }
}

// Runge-Kutta 4th order method (RK4) to solve the system of first-order ODEs
void runge_kutta_4(double h, double t_max, double y0, double yp0, double* time, double* y_vals, int n) {
    double z1 = y0, z2 = yp0;
    
    for (int i = 0; i < n; ++i) {
        time[i] = i * h;
        y_vals[i] = z1;
        
        // Calculate the RK4 steps
        double k1_1, k1_2, k2_1, k2_2, k3_1, k3_2, k4_1, k4_2;
        
        f(time[i], z1, z2, k1_1, k1_2);
        f(time[i] + 0.5 * h, z1 + 0.5 * h * k1_1, z2 + 0.5 * h * k1_2, k2_1, k2_2);
        f(time[i] + 0.5 * h, z1 + 0.5 * h * k2_1, z2 + 0.5 * h * k2_2, k3_1, k3_2);
        f(time[i] + h, z1 + h * k3_1, z2 + h * k3_2, k4_1, k4_2);
        
        // Update z1 and z2 using RK4 formula
        z1 += (h / 6.0) * (k1_1 + 2.0 * k2_1 + 2.0 * k3_1 + k4_1);
        z2 += (h / 6.0) * (k1_2 + 2.0 * k2_2 + 2.0 * k3_2 + k4_2);
    }
}

// Function to write data to a file (for plotting with gnuplot)
void write_data(const string& filename, double* time, double* y_vals, int n) {
    ofstream file(filename);
    for (int i = 0; i < n; ++i) {
        file << time[i] << " " << y_vals[i] << endl;
    }
    file.close();
}

int main() {
    // Initial conditions
    double y0 = 1.0;
    double yp0 = -1.0;
    double t_max = 10.0;
    
    // Step sizes
    double h1 = 0.1;
    double h2 = 0.01;
    
    // Number of time steps for each method (n = t_max / h + 1)
    int n1 = static_cast<int>(t_max / h1) + 1;
    int n2 = static_cast<int>(t_max / h2) + 1;
    
    // Arrays to store results
    double* time1 = new double[n1];
    double* time2 = new double[n2];
    double* euler_vals_1 = new double[n1];
    double* euler_vals_2 = new double[n2];
    double* rk4_vals_1 = new double[n1];
    double* exact_vals_1 = new double[n1];
    double* exact_vals_2 = new double[n2];
    
    // Solve using Euler method with h = 0.1 and h = 0.01
    euler_method(h1, t_max, y0, yp0, time1, euler_vals_1, n1);
    euler_method(h2, t_max, y0, yp0, time2, euler_vals_2, n2);
    
    // Solve using Runge-Kutta 4th order method with h = 0.1
    runge_kutta_4(h1, t_max, y0, yp0, time1, rk4_vals_1, n1);
    
    // Exact solution
    for (int i = 0; i < n1; ++i) {
        exact_vals_1[i] = exact_solution(time1[i]);
    }
    for (int i = 0; i < n2; ++i) {
        exact_vals_2[i] = exact_solution(time2[i]);
    }
    
    // Write the data to files for gnuplot
    write_data("euler_h0.1.dat", time1, euler_vals_1, n1);
    write_data("euler_h0.01.dat", time2, euler_vals_2, n2);
    write_data("rk4_h0.1.dat", time1, rk4_vals_1, n1);
    write_data("exact_solution.dat", time1, exact_vals_1, n1);
    
    // Cleanup dynamically allocated memory
    delete[] time1;
    delete[] time2;
    delete[] euler_vals_1;
    delete[] euler_vals_2;
    delete[] rk4_vals_1;
    delete[] exact_vals_1;
    delete[] exact_vals_2;
    
    return 0;
}