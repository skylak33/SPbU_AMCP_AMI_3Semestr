#include <bits/stdc++.h>

const double EPS = 1e-4;

double f(double x) {
    return pow(x, 3) - exp(x) + 1;
}

double f_prime(double x) {
    return 3 * pow(x, 2) - exp(x);
}

double newton_method(double x0) {
    double x = x0;
    double x_next;

    while (true) {
        x_next = x - f(x) / f_prime(x);
        if (fabs(x_next - x) < EPSILON)
            break;
        x = x_next;
    }
    return x_next;
}

int main() {
    double x0 = -0.8;
    double root = newton_method(x0);
    std::cout << std::setprecision(5) << std::fixed << "Приближенное значение корня: " << root << std::endl;
    return 0;
}
