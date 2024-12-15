#include <iostream>
#include <cmath>
#include <iomanip> 
#include <functional>
using namespace std;


double df(double x) {
    return 2*x - 8;
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
        
       
        if (fabs(x1 - x0) < tolerance) {
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
    // Function input and parameters
    double initialGuess, tolerance;
    int maxIterations;

    // cout << "Enter the initial guess: ";
    // cin >> initialGuess;

    // cout << "Enter the tolerance (for convergence): ";
    // cin >> tolerance;

    // cout << "Enter the maximum number of iterations: ";
    // cin >> maxIterations;

    // Define the function 
    function<double(double)> func = [](double x) { return x*x - 8*x + 11 ;};

    double root = newtonRaphson(func, initialGuess = 6, tolerance = 1e-5, maxIterations = 2000);

    cout << "The root of the equation is: " << root << endl;

    return 0;
}
