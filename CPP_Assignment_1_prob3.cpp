#include <iostream>
#include <cmath>

using namespace std;

double f(double x) {
    // function: f(x) = (e^2x) + x − 5 with x0 = 0 and x1 = 1.
    return exp(2 * x) + x - 5;
}


double secantMethod(double x0, double x1, double tol, int maxIter) {
    double x2;
    int iter = 0;

    while (iter < maxIter) {
        double f0 = f(x0);
        double f1 = f(x1);
        if (f0==f1){ cout<<"Error"<<endl; break;}

        x2 = x1 - (f1 * (x1 - x0)) / (f1 - f0);

        if ((fabs(x2 - x1) <= tol) || (fabs(x2 - x1) == fabs(x1 - x0))) {
            cout << "Root found: " << x2 << endl;
            cout << "Number of iterations: " << iter + 1 << endl;
            return x2;
        }

        double f2 = f(x2);
        
        if (f0 * f2 < 0) {
            // Root lies between x0 and x2, so update x1 to x2
            x1 = x2;
        } else {
            // Root lies between x1 and x2, so update x0 to x2
            x0 = x2;
        }

        iter++;
    }

    cout << "Max iterations reached" << endl;
    return x2;
}

int main() {
    double x0, x1, tol;
    int maxIter;

    // cout << "Enter the first initial guess (x0): ";
    // cin >> x0;
    // cout << "Enter the second initial guess (x1): ";
    // cin >> x1;
    // cout << "Enter the tolerance: ";
    // cin >> tol;
    // cout << "Enter the maximum number of iterations: ";
    // cin >> maxIter;

    double root = secantMethod(x0=0, x1=1, tol=1e-6, maxIter=2000);

    cout << "Approximated root: " << root << endl;

    return 0;
}