#include <bits/stdc++.h>

template<typename T> // Тут я бинарно возвожу число в степень (Асимптотика O(log(n)) вместо O(n) у встроенной функции std::pow())
T binpow(T a, int n) {
    if (n == 0) return 1.0;
    if (n == 1) return a;
    if (n < 0) {
        a = 1 / a;
        n = -n;
    }
    T res = 1.0;
    while (n) {rf
        if (n & 1) {
            res *= a;
        }
        a *= a;
        n >>= 1;
    }
    return res;
}

// Функция f(x) = x^3 - e^x + 1
double f(double x) {
    return binpow(x, 3) - std::exp(x) + 1;
}

// Производная функции f'(x) = 3x^2 - e^x
double f_derevative(double x) {
    return 3 * x * x - std::exp(x);
}

double newtonMethod() {
    double x = 0.5; // Начальное приближение
    double x_next = 0.0;
    double eps = 1e-4; // Точность

    while (true) {
        x_next = x - f(x) / f_derevative(x);
        if (std::abs(x_next - x) < eps) {
            break;
        }
        x = x_next;
    }

    return x_next;
}

int main() {
    double root = newtonMethod();
    std::cout << std::setprecision(4) << std::fixed;
    std::cout << "Минимальный по модулю ненулевой корнь: " << root << std::endl;

    return 0;
}