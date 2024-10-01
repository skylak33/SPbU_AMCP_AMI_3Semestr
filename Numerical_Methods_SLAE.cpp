#include <bits/stdc++.h>

const int n = 2; // меняем n на свой номер в списке
const long double eps = 1e-6; // Погрешность для Зейделя

template<typename T> // Тут я бинарно возвожу число в степень (Асимптотика O(log(n)) вместо O(n) у встроенной функции std::pow())
T binpow(T a, int n) {
    if (n == 0) return 1.0;
    if (n == 1) return a;
    if (n < 0) {
        a = 1 / a;
        n = -n;
    }
    T res = 1.0;
    while (n) {
        if (n & 1) {
            res *= a;
        }
        a *= a;
        n >>= 1;
    }
    return res;
}

void init() { // Задаю параметры для вывода
    std::cout << std::setprecision(3) << std::fixed;
}

std::vector<std::vector<int>> initA() { // Задаю данный нам массив А
    std::vector<std::vector<int>> a(3, std::vector<int>(3, 1));
    a[0][0] = n+ 2;
    a[1][1] = n + 4;
    a[2][2] = n + 6;

    return a;
}

std::vector<int> initB() { // Задаю данный нам массив В
    return {n + 4, n + 6, n + 8};
}
template<typename T> // функция вывода
void print(std::vector<std::vector<T>>& a, char c) {
    std::cout << c << ":\n";
    for (auto i : a) {
        std::cout << "\t";
        for (auto j : i) {
            std::cout << j << "\t";
        }
        std::cout << "\n"; 
    }
    std::cout << "\n";
}
template<typename T> // функция вывода
void print(std::vector<T>& b, char c) {
    std::cout << c << ":\t";
    for (auto i : b) {
        std::cout << i << "\t"; 
    }
    std::cout << "\n\n"; 
}

template<typename T>
T calculateAccuracy(const std::vector<T>& old_X, const std::vector<T>& new_X) {
    T max_diff = 0;
    for (size_t i = 0; i < old_X.size(); ++i) {
        max_diff = std::max(max_diff, std::abs(new_X[i] - old_X[i]));
    }
    return max_diff;
}

std::vector<double> zeidelMethod(std::vector<std::vector<int>>& a, std::vector<int>& b) {
    std::vector<std::vector<double>> c(3, std::vector<double>(3));

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == j) c[i][j] = 0;
            else c[i][j] = double(-a[i][j]) / double (a[i][i]);
        }
    }
    std::vector<double> d(3);
    for (int i = 0; i < 3; ++i) {
        d[i] = double(b[i]) / double(a[i][i]);
    }
    
    std::vector<double> old_X = {1, 1, 1}; // так как x^0 = 1
    std::vector<double> new_X = {1000, 100, 1203}; // ставлю любое число, так как первой итерацией буду высчитывать это
    int k = 1;
    while (calculateAccuracy<double>(old_X, new_X) > 3 * eps) {
        for (int i = 0; i < int(new_X.size()); ++i) {
            double new_Xi = d[i]; 
            for (int j = 0; j < i; ++j) {
                new_Xi += c[i][j] * new_X[j];
            }
            for (int j = i + 1; j < int(new_X.size()); ++j) {
                new_Xi += c[i][j] * old_X[j];
            }

            old_X[i] = new_X[i];
            new_X[i] = new_Xi;
        }
        k++;
    }
    //std::cout << "itterations :" << k << "\n";
    return new_X;

}

int main() {
    init();
    std::vector<std::vector<int>> A = initA();
    std::vector<int> B = initB();
    std::vector<double> answer = zeidelMethod(A, B);
    print<double>(answer, 'X'); // Пока что, реализован только Зейдель
}
