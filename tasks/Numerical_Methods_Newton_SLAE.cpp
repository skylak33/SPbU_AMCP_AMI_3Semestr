#include <bits/stdc++.h>

const double EPS = 1e-4;

double f1(double x, double y) {
    return sin(y) + 2 * x - 2;
}

double f2(double x, double y) {
    return y + cos(x - 1) - 0.7;
}

double f1_x(double x, double y) {
    return 2;
}

double f1_y(double x, double y) {
    return cos(y);
}

double f2_x(double x, double y) {
    return -sin(x - 1);
}

double f2_y(double x, double y) {
    return 1;
}

void newton_method(double &x, double &y) {
    double dx, dy;
    while (true) {
        double J = f1_x(x, y) * f2_y(x, y) - f1_y(x, y) * f2_x(x, y);
        dx = (-f1(x, y) * f2_y(x, y) + f1_y(x, y) * f2(x, y)) / J;
        dy = (-f2(x, y) * f1_x(x, y) + f2_x(x, y) * f1(x, y)) / J;

        x += dx;
        y += dy;

        if (sqrt(dx * dx + dy * dy) < EPS)
            break;
    }
}

int main() {
    double x = 1.0, y = -0.25;
    newton_method(x, y);
    std::cout << "Приближенное значение корней: x = " << x << ", y = " << y << std::endl;
    return 0;
}
