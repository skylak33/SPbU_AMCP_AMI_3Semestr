#include <bits/stdc++.h>

const long double eps1 = (1e-6) / 1.2, eps2 = (1e-6) / 1.59, eps3 = (1e-6) / 1.86;
const long double pi = 3.14159265358979323846;

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

template<typename T> // Тут я вычисляю факториал
T factorial(int n) {
    T res = 1;
    for (int i = 1; i <= n; i++) {
        res *= i;
    }
    return res;
}
template<typename T> // Тут я использую разложение в ряд Тейлора для arctg(x)
T arctgTaylor(T x, T eps) {
    T answer = pi / 2;
    T term = binpow(x, -1) / 1;
    int n = 0;

    while (std::abs(term) > eps) {
        answer -= term;
        n++;
        term = binpow(-1, n % 2) * binpow<T>(x, -(2 * n + 1)) / (2 * n + 1);
    }
    return answer;
}
template<typename T> // Тут я используя разложение в ряд Тейлора для cos(x) (почему написано sin, см. ниже)
T sinTaylor(T x, T eps) {
    // так как у меня |x| > pi / 4, то я буду использовать разложение в ряд Тейлора для cos(x)
    // а значит мне нужно перейти в него с помощью sin(pi/2 - x) = cos(x)
    T new_x = pi / 2 - x;
    T answer = 0;
    T term = 1;
    int n = 0;

    while (std::abs(term) > eps) {
        answer += term;
        n++;
        term = binpow(-1,  n % 2) * binpow(new_x, 2 * n) / factorial<T>(2 * n);
    }
    return answer;
}
template<typename T> // Тут я вычисляю корень с помощью формулы Геронаы
T sqrtHeron(T phi, T eps) {
    T answer = 1;
    T next = 0.5 * (answer + phi / answer);
    while (std::abs(next - answer) > eps) {
        answer = next;
        next = 0.5 * (answer + phi / answer);
    }
    return answer;
}

// Киллер-фича
void printRainbowText(const std::string& text) {
    const std::string colors[] = {
        "\033[31m",
        "\033[33m", 
        "\033[32m",
        "\033[36m",
        "\033[34m", 
        "\033[35m", 
    };
    int colorIndex = 0;
    for (char c : text) {
        std::cout << colors[colorIndex] << c;
        colorIndex = (colorIndex + 1) % 6;
    }
    std::cout << "\033[0m";
}

int main() { // Главное тело программы
    std::cout << std::setprecision(8); // выставляю точность вывода
    // На 94, 95 строке я вывожу параметры, с которыми буду работать + фрагменты таблички
    printRainbowText("\t\t\tesp1: " + std::to_string(eps1) + "\teps2: " + std::to_string(eps2) + "\teps3: " + std::to_string(eps3) + "\n");
    printRainbowText("\tx\t\tphi(x)\t\tg(x)\t\theron\t\tanswer\t\ttime (ms))\n");
    int i = 0;
    for (long double x = 0.01; x <= 0.061; x += 0.005) {
        // Засекаем время (необязательно)
        auto start = std::chrono::high_resolution_clock::now();

        long double phi = 1 + arctgTaylor<long double>((6.4 * x + 1.1), eps1);
        long double g = sinTaylor<long double>((2 * x + 1.05), eps2); 
        long double heron = sqrtHeron<long double>(phi, eps3);

        // Засекаем время (необязательно)
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<long double, std::milli> duration = end - start;

        printRainbowText("x" + std::to_string(i) + ":\t" + std::to_string(x) + '\t' + std::to_string(phi) + 
                    '\t' + std::to_string(g) + '\t' + std::to_string(heron) + '\t' + std::to_string(heron / g) + 
                    '\t' + std::to_string(duration.count()) + " ms\n");
        // Просто для проверки
        //std::cout << "|x" << i <<": " << x << '\t' << 1 + atan(6.4 * x + 1.1) << '\t' << sin(2 * x + 1.05) << '\t' << sqrt(1 + atan(6.4 * x + 1.1)) << '\t' << sqrt(1 + atan(6.4 * x + 1.1)) /  sin(2 * x + 1.05)<< '\t' << duration.count() << " ms" << std::endl;
        i++;
    }

    return 0;
}
