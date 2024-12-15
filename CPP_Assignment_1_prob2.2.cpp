#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>  
#define PI 3.141592653589793238462643383279
using namespace std;


double df( double x) {
    return -1-2*cos(x);
}


double newtonRaphson(function<double(double)> func, double initialGuess, double tolerance, int maxIterations) {
    double x0 = initialGuess;
    double x1;
    int iteration = 0;
    
   
    while (iteration < maxIterations) {
     
        double derivative = df(x0);
        
        // Avoid division by zero (check if the derivative is too small)
        if (fabs(derivative) < 1e-10) {
            cout << "Derivative is too small, the method may fail." << endl;
            return x0;
        }
        
      
        x1 = x0 - func(x0) / derivative;
        if (fabs(sin(x1) - sin(x0)) < tolerance) {
            return x1;
        }

  
        x0 = x1;
        iteration++;
    }

    // If max iterations reached without convergence
    cout << "Max iterations reached without convergence." << endl;
    return x1;
}

int main() {
    double initialGuess, tolerance;
    int maxIterations;

    // cout << "Enter the initial guess: ";
    // cin >> initialGuess;

    // cout << "Enter the tolerance (for convergence): ";
    // cin >> tolerance;

    // cout << "Enter the maximum number of iterations: ";
    // cin >> maxIterations;

    function<double(double)> func = [](double x) { return (PI - x) - 2*sin(x) ;};

    double root = newtonRaphson(func, initialGuess=5, tolerance=1e-18, maxIterations=2000);

    cout<< fixed << setprecision(18) << "The root of the equation is: " << 2*abs(sin(root)) << endl;

    return 0;
}