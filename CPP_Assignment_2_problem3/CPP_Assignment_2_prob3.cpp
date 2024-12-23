#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

const double sigma = 10.0;
const double beta = 8.0 / 3.0;

struct LorenzState {
    double x, y, z;
};

void lorenz_derivatives(const LorenzState &state, LorenzState &deriv, double rho) {
    deriv.x = sigma * (state.y - state.x);
    deriv.y = state.x * (rho - state.z) - state.y;
    deriv.z = state.x * state.y - beta * state.z;
}

void euler_step(LorenzState &state, double dt, double rho) {
    LorenzState deriv;
    lorenz_derivatives(state, deriv, rho);
    state.x += dt * deriv.x;
    state.y += dt * deriv.y;
    state.z += dt * deriv.z;
}

void rk4_step(LorenzState &state, double dt, double rho) {
    LorenzState k1, k2, k3, k4;

    lorenz_derivatives(state, k1, rho);
    LorenzState temp = {state.x + 0.5 * dt * k1.x, state.y + 0.5 * dt * k1.y, state.z + 0.5 * dt * k1.z};
    lorenz_derivatives(temp, k2, rho);
    temp = {state.x + 0.5 * dt * k2.x, state.y + 0.5 * dt * k2.y, state.z + 0.5 * dt * k2.z};
    lorenz_derivatives(temp, k3, rho);
    temp = {state.x + dt * k3.x, state.y + dt * k3.y, state.z + dt * k3.z};
    lorenz_derivatives(temp, k4, rho);

    state.x += dt / 6.0 * (k1.x + 2.0 * k2.x + 2.0 * k3.x + k4.x);
    state.y += dt / 6.0 * (k1.y + 2.0 * k2.y + 2.0 * k3.y + k4.y);
    state.z += dt / 6.0 * (k1.z + 2.0 * k2.z + 2.0 * k3.z + k4.z);
}

void solve_lorenz(const std::string &filename, double rho, double dt, int steps, bool use_rk4 = false) {
    std::ofstream file(filename);

    LorenzState state = {1.0, 1.0, 1.0};
    file << 0 << " " << state.x << " " << state.y << " " << state.z << "\n";

    for (int i = 1; i <= steps; ++i) {
        if (use_rk4) {
            rk4_step(state, dt, rho);
        } else {
            euler_step(state, dt, rho);
        }

        file << i * dt << " " << state.x << " " << state.y << " " << state.z << "\n";
    }

    file.close();
}

void compare_trajectories(const std::string &filename, double rho, double dt, int steps) {
    std::ofstream file(filename);

    LorenzState state1 = {1.0, 1.0, 1.0};
    LorenzState state2 = {1.0 + 1e-5, 1.0, 1.0};

    for (int i = 0; i <= steps; ++i) {
        file << i * dt << " " << state1.x << " " << state1.y << " " << state1.z << " ";
        file << state2.x << " " << state2.y << " " << state2.z << "\n";

        rk4_step(state1, dt, rho);
        rk4_step(state2, dt, rho);
    }

    file.close();
}

int main() {
    double dt = 0.01;
    int steps = 10000;

    // Solve with different rho values
    solve_lorenz("lorenz_rho28_euler.dat", 28.0, dt, steps);
    solve_lorenz("lorenz_rho28_rk4.dat", 28.0, dt, steps, true);
    solve_lorenz("lorenz_rho14.dat", 14.0, dt, steps, true);
    solve_lorenz("lorenz_rho99.96.dat", 99.96, dt, steps, true);

    // Compare trajectories with rho = 28
    compare_trajectories("lorenz_compare_trajectories.dat", 28.0, dt, steps);

    std::cout << "Simulation complete. Data written to files." << std::endl;

    return 0;
}
