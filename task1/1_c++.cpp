#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double func(double x) {
    return x * log(x + 1) - 1;
}

double diff(double x) {
    return log(x + 1) + x / (x + 1);
}

double phi(double x) {
    return exp(1/x) - 1;}

void bisection(double a, double b, double eps) {
    cout << "\n BISECTION METHOD \n";
    cout << setw(5) << "N" << setw(15) << "an" << setw(15) << "bn" << setw(15) << "bn - an" << endl;
    cout << "------------------------------------------------------------\n";
    
    int n = 0;
    while ((b - a) > eps) {
        n++;
        double c = (a + b) / 2.0;
        cout << setw(5) << n << setw(15) << a << setw(15) << b << setw(15) << b - a << endl;
        
        if (func(a) * func(c) < 0) 
            b = c;
        else 
            a = c;
    }
    cout << "Result: Root = " << (a + b) / 2.0 << " | Iterations = " << n << endl;
}

void newton(double x0, double eps) {
    cout << "\n NEWTON'S METHOD \n";
    cout << setw(5) << "N" << setw(15) << "Xn" << setw(15) << "Xn+1" << setw(15) << "|Xn+1 - Xn|" << endl;
    cout << "------------------------------------------------------------\n";
    
    double xn = x0;
    double x_next;
    int n = 0;
    
    do {
        n++;
        x_next = xn - func(xn) / diff(xn);
        cout << setw(5) << n << setw(15) << xn << setw(15) << x_next << setw(15) << abs(x_next - xn) << endl;
        if (abs(x_next - xn) < eps) break;
        xn = x_next;
    } while (true);
    
    cout << "Result: Root = " << x_next << " | Iterations = " << n << endl;
}

void simple_iteration(double x0, double eps) {
    cout << "\n SIMPLE ITERATION METHOD \n";
    cout << setw(5) << "N" << setw(15) << "Xn" << setw(15) << "Xn+1" << setw(15) << "|Xn+1 - Xn|" << endl;
    cout << "------------------------------------------------------------\n";
    
    double xn = x0;
    double x_next;
    int n = 0;
    
    do {
        n++;
        x_next = phi(xn);
        cout << setw(5) << n << setw(15) << xn << setw(15) << x_next << setw(15) << abs(x_next - xn) << endl;
        if (abs(x_next - xn) < eps) break;
        xn = x_next;
    } while (true);
    
    cout << "Result: Root = " << x_next << " | Iterations = " << n << endl;
}

int main() {
    double a = -0.9, b = 2.0; 
    double eps = 1e-4;
    
    cout << fixed << setprecision(6);
    
    bisection(a, b, eps);
    
    newton(a, eps);            
    
    simple_iteration(a, eps); 
    
    return 0;
}