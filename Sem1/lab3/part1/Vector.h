#pragma once
#include <iostream>

// Класс "вектор" с динамическим массивом
class Vector {
public:
    Vector();                              // пустой вектор
    Vector(const double* arr, int size);   // вектор из обычного массива
    Vector(const Vector& other);           // конструктор копирования
    Vector(Vector&& other) noexcept;       // конструктор перемещения
    ~Vector();                             // деструктор

    Vector& operator=(const Vector& other);      // присваивание с копированием
    Vector& operator=(Vector&& other) noexcept;  // присваивание с перемещением

    double& operator[](int i);                   // обращение к элементу
    const double& operator[](int i) const;

    double operator*(const double* p) const;     // вариант 12: скалярное произведение

    int size() const { return n; }

    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
    friend std::istream& operator>>(std::istream& is, Vector& v);

private:
    double* data;   // указатель на динамический массив
    int n;          // количество элементов
};
