#include <fstream>
#include <iostream>
#include <utility>
#include "Vector.h"

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    if (!fin || !fout) {
        std::cerr << "Не удалось открыть файлы input.txt или output.txt\n";
        return 1;
    }

    // 1. Пустой вектор (конструктор по умолчанию)
    fout << "1. Пустой вектор\n";
    Vector empty;
    fout << empty << "\n\n";

    // 2. Чтение данных из input.txt
    Vector a;
    fin >> a;                       // оператор >>

    int k = 0;
    fin >> k;                       // размер обычного массива
    double* p = new double[k];
    for (int i = 0; i < k; ++i) fin >> p[i];

    fout << "2. Входные данные\n";
    fout << "Вектор a: " << a << "\n";
    fout << "Массив p:";
    for (int i = 0; i < k; ++i) fout << ' ' << p[i];
    fout << "\n\n";

    if (k != a.size()) {
        fout << "Ошибка: размерности вектора и массива не совпадают\n";
        delete[] p;
        return 1;
    }

    // 3. Вариант 12: скалярное произведение a * p
    fout << "3. Скалярное произведение a * p (вариант 12)\n";
    double dot = a * p;
    fout << "a * p = " << dot << "\n\n";

    // 4. Оператор []
    fout << "4. Оператор []\n";
    fout << "a[0] = " << a[0] << ", a[2] = " << a[2] << "\n";
    a[0] = 100;                     // изменяем элемент через []
    fout << "После a[0] = 100: a = " << a << "\n\n";
    a[0] = 1;                       // возвращаем исходное значение

    // 5. Конструктор копирования: копия не связана с исходником
    fout << "5. Конструктор копирования\n";
    Vector c(a);
    c[0] = 555;
    fout << "c после c[0] = 555: c = " << c << "\n";
    fout << "a не изменился:     a = " << a << "\n\n";

    // 6. Конструктор перемещения: данные переходят к новому объекту
    fout << "6. Конструктор перемещения\n";
    Vector d(std::move(c));
    fout << "d = " << d << "\n";
    fout << "c после перемещения: " << c << "\n\n";

    // 7. Присваивание с копированием и с перемещением
    fout << "7. Присваивание\n";
    Vector e;
    e = a;                          // копирование: a остается
    fout << "После e = a:            e = " << e << ", a = " << a << "\n";
    e = std::move(d);               // перемещение: d становится пустым
    fout << "После e = std::move(d): e = " << e << ", d = " << d << "\n";

    delete[] p;
    return 0;
}
