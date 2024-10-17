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

std::vector<std::vector<double>> initA() { // Задаю данный нам массив А
    std::vector<std::vector<double>> a(3, std::vector<double>(3, 1));
    a[0][0] = n + 2;
    a[1][1] = n + 4;
    a[2][2] = n + 6;

    return a;
}

std::vector<double> initB() { // Задаю данный нам массив В
    return {n + 4, n + 6, n + 8};
}

template<typename T> // функция вывода
void print(const std::vector<std::vector<T>>& a, char c) {
    std::cout << c << ":\n";
    for (const auto& i : a) {
        std::cout << "\t";
        for (const auto& j : i) {
            std::cout << j << "\t";
        }
        std::cout << "\n"; 
    }
    std::cout << "\n";
}

template<typename T> // функция вывода
void print(const std::vector<T>& b, char c) {
    std::cout << c << ":\t";
    for (const auto& i : b) {
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

std::vector<double> zeidelMethod(const std::vector<std::vector<double>>& a, const std::vector<double>& b) {
    std::vector<std::vector<double>> c(3, std::vector<double>(3));

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == j) c[i][j] = 0;
            else c[i][j] = -a[i][j] / (a[i][i]);
        }
    }
    std::vector<double> d(3);
    for (int i = 0; i < 3; ++i) {
        d[i] = b[i] / a[i][i];
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

std::vector<double> gaussMethod(std::vector<std::vector<double>> a, std::vector<double> b) {
    int size = a.size();

    // Прямой ход метода Гаусса (приведение к треугольному виду)
    for (int i = 0; i < size; ++i) {
        // Находим строку с максимальным элементом в столбце
        int maxRow = i;
        for (int k = i + 1; k < size; ++k) {
            if (fabs(a[k][i]) > fabs(a[maxRow][i])) {
                maxRow = k;
            }
        }

        // Меняем строки местами
        std::swap(a[i], a[maxRow]);
        std::swap(b[i], b[maxRow]);

        // Если главный элемент очень мал (почти 0), система, вероятно, несовместна или имеет бесконечно много решений
        if (fabs(a[i][i]) < eps) {
            std::cout << "Система не имеет единственного решения.\n";
            return {};
        }

        // Приводим главный элемент к 1 и зануляем элементы ниже главного
        for (int k = i + 1; k < size; ++k) {
            double coeff = a[k][i] / a[i][i];
            for (int j = i; j < size; ++j) {
                a[k][j] -= coeff * a[i][j];
            }
            b[k] -= coeff * b[i];
        }
    }

    // Обратный ход метода Гаусса (метод обратной подстановки)
    std::vector<double> x(size);
    for (int i = size - 1; i >= 0; --i) {
        x[i] = b[i] / a[i][i];
        for (int j = i - 1; j >= 0; --j) {
            b[j] -= a[j][i] * x[i];
        }
    }

    return x;
}

int main() {
    init();
    std::vector<std::vector<double>> A = initA();
    std::vector<double> B = initB();
    std::vector<double> answer = zeidelMethod(A, B);
    std::cout << "ЗЕЙДЕЛЬ\n";
    print<double>(answer, 'X'); // Пока что, реализован только Зейдель

    // Создаем копию матрицы A и вектора B для метода Гаусса
    std::vector<std::vector<double>> A_copy = A;
    std::vector<double> B_copy = B;
    std::vector<double> result = gaussMethod(A_copy, B_copy);

    std::cout << "ГАУСС\n";
    print<double>(result, 'X');
    
    return 0;
}
