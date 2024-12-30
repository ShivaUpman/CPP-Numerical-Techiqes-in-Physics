#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <ctime>

// Define the size of the grid (n x n)
const int n = 50;

// Function to convert a 2D grid to a 1D flat vector
void flatten(const std::vector<std::vector<double>>& grid, std::vector<double>& flat) {
    int size = grid.size();
    flat.resize(size * size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            flat[i * size + j] = grid[i][j];
        }
    }
}

// Function to convert a 1D flat vector back to a 2D grid
void flat2grid(const std::vector<double>& flat, std::vector<std::vector<double>>& grid) {
    int size = grid.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            grid[i][j] = flat[i * size + j];
        }
    }
}

// Function to create the Laplacian operator matrix M
void make_laplacian_operator(std::vector<std::vector<double>>& operator_matrix) {
    int size = n * n;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            operator_matrix[i][j] = 0.0;
        }
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int idx = i * n + j;
            operator_matrix[idx][idx] = -4.0; // Diagonal element
            
            // Neighboring elements (up, down, left, right)
            if (i > 0) operator_matrix[idx][(i-1) * n + j] = 1.0; // Up
            if (i < n-1) operator_matrix[idx][(i+1) * n + j] = 1.0; // Down
            if (j > 0) operator_matrix[idx][i * n + (j-1)] = 1.0; // Left
            if (j < n-1) operator_matrix[idx][i * n + (j+1)] = 1.0; // Right
        }
    }
}

// Function to perform the Gauss-Seidel iterative solver
void solve_system_lineq(std::vector<std::vector<double>>& M, std::vector<double>& U_flat, const std::vector<double>& rho_flat, int max_iterations = 10000, double tolerance = 1e-5) {
    int size = n * n;
    for (int iter = 0; iter < max_iterations; ++iter) {
        double max_error = 0.0;
        
        for (int i = 0; i < size; ++i) {
            double sum = 0.0;
            for (int j = 0; j < size; ++j) {
                if (i != j) {
                    sum += M[i][j] * U_flat[j];
                }
            }
            double new_value = (rho_flat[i] - sum) / M[i][i];
            max_error = std::max(max_error, std::abs(U_flat[i] - new_value));
            U_flat[i] = new_value;
        }
        
        if (max_error < tolerance) {
            break;
        }
    }
}

// Function to write the field data to a text file
void write_field_data(const std::vector<std::vector<double>>& field_grid) {
    std::ofstream field_file("field.txt");
    for (int i = 0; i < n; ++i) {
        field_file << "\n";
        for (int j = 0; j < n; ++j) {
            field_file << field_grid[i][j];  // Write value at (i, j)
            if (j < n - 1) {
                field_file << " ";  // Add space between values in the same row
            }
        }
    }
    field_file.close();
}

int main() {
    // Charge distribution grid (ρ(x, y)) and potential field (U(x, y))
    std::vector<std::vector<double>> cd_grid(n, std::vector<double>(n, 0.0));
    std::vector<std::vector<double>> U_grid(n, std::vector<double>(n, 0.0));

    // Set the boundary charge distribution
    cd_grid[n / 2 + 10][n / 2] = 1.0; // Positive charge
    cd_grid[n / 2 - 10][n / 2] = -1.0; // Negative charge

    // Set boundary conditions for Poisson equation (for simplicity, boundary charge is 1.0 and -1.0)
    for (int j = 0; j < n; ++j) {
        cd_grid[0][j] = 1.0;
        cd_grid[n-1][j] = -1.0;
    }

    // Flatten charge distribution grid into a 1D vector
    std::vector<double> rho_flat;
    flatten(cd_grid, rho_flat);

    // Construct the Laplacian operator matrix M
    std::vector<std::vector<double>> M(n * n, std::vector<double>(n * n, 0.0));
    make_laplacian_operator(M);

    // Solve the linear system: M * U_flat = -rho_flat
    std::vector<double> U_flat(n * n, 0.0); // Initial guess for U_flat
    solve_system_lineq(M, U_flat, rho_flat);

    // Convert U_flat back to a 2D grid
    flat2grid(U_flat, U_grid);

    // Write the field data to a file for visualization
    write_field_data(U_grid);

    std::cout << "Simulation complete. Data written to 'field.txt'. Now visualize using Gnuplot.\n";

    return 0;
}