#include "Vector.h"
#include <stdexcept>
#include <utility>

// Пустой вектор: памяти нет, размер 0
Vector::Vector() : data(nullptr), n(0) {}

// Вектор из обычного массива: выделяем память и копируем элементы
Vector::Vector(const double* arr, int size) : data(nullptr), n(size) {
    if (n > 0) {
        data = new double[n];
        for (int i = 0; i < n; ++i) data[i] = arr[i];
    }
}

// Копирование: создаем новую память и копируем данные.
// Исходный вектор не меняется.
Vector::Vector(const Vector& other) : data(nullptr), n(other.n) {
    if (n > 0) {
        data = new double[n];
        for (int i = 0; i < n; ++i) data[i] = other.data[i];
    }
}

// Перемещение: забираем чужую память, у исходного вектора ее не остается.
Vector::Vector(Vector&& other) noexcept : data(other.data), n(other.n) {
    other.data = nullptr;
    other.n = 0;
}

// Деструктор: освобождаем память
Vector::~Vector() {
    delete[] data;
}

// Присваивание с копированием
Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {               // защита от a = a
        double* newData = nullptr;
        if (other.n > 0) {
            newData = new double[other.n];
            for (int i = 0; i < other.n; ++i) newData[i] = other.data[i];
        }
        delete[] data;                  // старую память удаляем только после создания новой
        data = newData;
        n = other.n;
    }
    return *this;
}

// Присваивание с перемещением
Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;              // забираем память
        n = other.n;
        other.data = nullptr;           // у источника памяти больше нет
        other.n = 0;
    }
    return *this;
}

double& Vector::operator[](int i) {
    if (i < 0 || i >= n) throw std::out_of_range("индекс вне диапазона");
    return data[i];
}

const double& Vector::operator[](int i) const {
    if (i < 0 || i >= n) throw std::out_of_range("индекс вне диапазона");
    return data[i];
}

// Вариант 12: скалярное произведение вектора и обычного массива.
// Результат - одно число: сумма произведений соответствующих элементов.
double Vector::operator*(const double* p) const {
    if (n > 0 && p == nullptr) throw std::invalid_argument("нулевой указатель");

    double sum = 0.0;
    for (int i = 0; i < n; ++i) sum += data[i] * p[i];
    return sum;
}

// Вывод: сначала размер, потом элементы
std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "Vector(" << v.n << "):";
    for (int i = 0; i < v.n; ++i) os << ' ' << v.data[i];
    return os;
}

// Ввод: сначала размер, потом элементы
std::istream& operator>>(std::istream& is, Vector& v) {
    int size = 0;
    if (!(is >> size) || size < 0) {
        is.setstate(std::ios::failbit);
        return is;
    }

    Vector tmp;
    if (size > 0) {
        tmp.data = new double[size];
        tmp.n = size;
        for (int i = 0; i < size; ++i) {
            if (!(is >> tmp.data[i])) return is;
        }
    }

    v = std::move(tmp);      // присваивание с перемещением
    return is;
}
