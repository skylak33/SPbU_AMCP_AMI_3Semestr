#include <bits/stdc++.h>

// Функция f(x, y) = sin(y) + 2x = 2;
// Функция g(x, y) = y + cos(x - 1) = 0.7;

// Функция f(x, y) = sin(y) + 2x = 2;
double f(double x, double y) {
    return std::sin(y) + 2 * x - 2;
}

// Производная функции f'x(x, y) = 2
double fdx(double x, double y) {
    return 2;
}

// Производная функции f'y(x, y) = cos(y)
double fdy(double x, double y) {
    return std::cos(y);
}

// Функция g(x, y) = y + cos(x - 1) = 0.7;
double g(double x, double y) {
    return y + std::cos(x - 1) - 0.7;
}

// Производная g'x(x,y) = -sin(x - 1)
double gdx(double x, double y) {
    return -std::sin(x - 1);
}

// Производная g'y(x,y) = 1
double gdy(double x, double y) {
    return 1;
}

// Метод Ньютона для системы уравнений
void newtonMethod(double &x, double &y, double eps, int max_iterations) {
    for (int i = 0; i < max_iterations; ++i) {
        double J[2][2] = {
            {fdx(x, y), fdy(x, y)},
            {gdx(x, y), gdy(x, y)}
        };

        double F[2] = {f(x, y), g(x, y)};

        double detJ = J[0][0] * J[1][1] - J[0][1] * J[1][0];
        if (std::abs(detJ) < eps) {
            throw std::runtime_error("Якобиан вырожден");
        }

        double dx = (F[0] * J[1][1] - F[1] * J[0][1]) / detJ;
        double dy = (F[1] * J[0][0] - F[0] * J[1][0]) / detJ;

        x -= dx;
        y -= dy;

        if (std::sqrt(dx * dx + dy * dy) < eps) {
            return;
        }
    }
    throw std::runtime_error("Метод Ньютона не сошелся");
}


int main() {
    std::cout << std::setprecision(4) << std::fixed;

    // Начальное приближение (найденное графическим методом)
    double x = 0.5;
    double y = 0.5;

    double eps = 1e-4;
    int max_iterations = 1000;

    try {
        newtonMethod(x, y, eps, max_iterations);
        std::cout << "Решение: x = " << x << ", y = " << y << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}