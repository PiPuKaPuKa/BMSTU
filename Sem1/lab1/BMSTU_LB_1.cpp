#include <iostream>
#include <cmath>
#include <iomanip>
#include <windows.h>

using namespace std;

int main() {
    // фикс иероглифов в консле
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    double eps[3] = {1e-2, 1e-4, 1e-6};

    cout << fixed << setprecision(10);

    for (int i = 0; i < 3; ++i) {
        double e = eps[i];

        // ряд e = 1 + 1 + 1/2! + 1/3! + ...
        double sum = 1; // первое слагаемое 1/0!
        double term = 1; // текущее слагаемое
        int k = 0; // номер слагаемого
        do {
            ++k;
            term = term / k; // 1/k! из предыдущего слагаемого
            sum += term;
        } while (term >= e); // цикл с постусловием
        int n_series = k + 1; // сколько слагаемых учли

        // цепная дробь e = 1 + 1/(1 - 1/(2 + 1/(3 - 1/(2 + 1/(5 - ...)))))
        // A и B считаем по рекуррентным формулам для подходящих дробей
        double A2 = 1, B2 = 0; // A(n-2), B(n-2)
        double A1 = 1, B1 = 1; // A(n-1), B(n-1), сейчас n = 0
        double prev = 0; // предыдущее приближение
        double cur = 1; // текущее приближение
        int n = 0;

        while (fabs(cur - prev) >= e) // цикл с предусловием
        {
            ++n;
            double b = (n % 2 == 1) ? n : 2; // b_n
            double a = (n % 2 == 1) ? 1 : -1; // a_n
            double A = b * A1 + a * A2;
            double B = b * B1 + a * B2;
            A2 = A1;
            B2 = B1;
            A1 = A;
            B1 = B;
            prev = cur;
            cur = A / B;
        }
        int n_frac = n + 1; // сколько элементов дроби учли (b_0 ... b_n)

        cout << "eps = " << e << endl;
        cout << "ряд:   " << n_series << " слагаемых, e = " << sum << endl;
        cout << "дробь: " << n_frac << " элементов, e = " << cur << endl;
        cout << "точное e = " << exp(1.0) << endl << endl;
    }

    return 0;
}
