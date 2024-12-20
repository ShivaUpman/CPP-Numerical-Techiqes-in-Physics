#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Function to perform Jacobi Iteration
void jacobi_method(double A[3][3], double b[3], double x[3], int n, double tolerance = 1e-5, int max_iterations = 100) {
    double x_new[3];  // Temporary array to store new values of x
    int iterations = 0;
    double diff = tolerance + 1.0;  // Initialize to a value greater than tolerance

    while (iterations < max_iterations && diff > tolerance) {
        // Perform one iteration of the Jacobi method
        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    sum += A[i][j] * x[j];
                }
            }
            // Update the new value for x[i]
            x_new[i] = (b[i] - sum) / A[i][i];
        }

        // Calculate the maximum difference between the old and new solution
        diff = 0.0;
        for (int i = 0; i < n; ++i) {
            diff = max(diff, fabs(x_new[i] - x[i]));
        }

        // Update the solution vector
        for (int i = 0; i < n; ++i) {
            x[i] = x_new[i];
        }

        iterations++;
    }

    cout << "Jacobi Method completed in " << iterations << " iterations." << endl;
}

// Function to perform Gauss-Seidel Iteration
void gauss_seidel_method(double A[3][3], double b[3], double x[3], int n, double tolerance = 1e-5, int max_iterations = 100) {
    int iterations = 0;
    double diff = tolerance + 1.0;  // Initialize to a value greater than tolerance

    while (iterations < max_iterations && diff > tolerance) {
        // Perform one iteration of the Gauss-Seidel method
        double x_old[3];  // Store the old values of x for convergence check
        for (int i = 0; i < n; ++i) {
            x_old[i] = x[i];
        }

        diff = 0.0;

        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    sum += A[i][j] * x[j];
                }
            }
            // Update the solution vector x[i] immediately
            x[i] = (b[i] - sum) / A[i][i];
            // Track the maximum difference
            diff = max(diff, fabs(x[i] - x_old[i]));
        }

        iterations++;
    }

    cout << "Gauss-Seidel Method completed in " << iterations << " iterations." << endl;
}

// Helper function to print the solution vector
void print_solution(double x[3], int n) {
    for (int i = 0; i < n; ++i) {
        cout << "x" << i + 1 << " = " << fixed << setprecision(5) << x[i] << endl;
    }
}

int main() {
    // Define the matrix A and vector b for the system of equations
    double A[3][3] = {
        {4.0, -1.0, -1.0},   // 4x - y - z = 3
        {-2.0, 6.0, 1.0},    // -2x + 6y + z = 9
        {-1.0, 1.0, 7.0}     // -x + y + 7z = -6
    };

    double b[3] = {3.0, 9.0, -6.0};  // Right-hand side vector

    int n = 3;  // Dimension of the system (3x3 in this case)

    // Initial guess (0, 0, 0)
    double x[3] = {0.0, 0.0, 0.0};

    // Solve using Jacobi method
    double x_jacobi[3] = {0.0, 0.0, 0.0};  // Reset initial guess
    cout << "Solving using Jacobi Method:" << endl;
    jacobi_method(A, b, x_jacobi, n);
    print_solution(x_jacobi, n);

    // Solve using Gauss-Seidel method
    double x_gauss_seidel[3] = {0.0, 0.0, 0.0};  // Reset initial guess
    cout << "\nSolving using Gauss-Seidel Method:" << endl;
    gauss_seidel_method(A, b, x_gauss_seidel, n);
    print_solution(x_gauss_seidel, n);

    return 0;
}
