#include <iostream>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif

// Базовый класс: круг
class Circle {
protected:
    double radius;   // радиус доступен производному классу

public:
    // Конструктор: задает радиус
    Circle(double r) : radius(r) {}

    // Виртуальный деструктор нужен, когда объекты удаляются через указатель на базовый класс
    virtual ~Circle() {}

    // Статический полиморфизм: обычная (не виртуальная) функция.
    // Какая функция вызовется, определяет компилятор по ТИПУ указателя или объекта.
    void printStatic() const {
        std::cout << "Круг: радиус = " << radius << "\n";
    }

    // Динамический полиморфизм: виртуальная функция.
    // Какая функция вызовется, определяется во время работы по ТИПУ самого объекта.
    virtual void printDynamic() const {
        std::cout << "Круг: радиус = " << radius << "\n";
    }
};

// Производный класс: эллипс
class Ellipse : public Circle {
private:
    double secondAxis;   // вторая полуось

public:
    // Конструктор: первая полуось - это унаследованный радиус, вторая - отдельное поле
    Ellipse(double firstAxis, double second) : Circle(firstAxis), secondAxis(second) {}

    // Переопределение (статическое): скрывает функцию базового класса
    void printStatic() const {
        Circle::printStatic();                       // сначала функция базового класса
        std::cout << "   Вторая полуось = " << secondAxis << "\n";
    }

    // Переопределение (динамическое): override проверяет, что функция действительно переопределена
    void printDynamic() const override {
        Circle::printDynamic();                      // сначала функция базового класса
        std::cout << "   Вторая полуось = " << secondAxis << "\n";
    }
};

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    // 1. По одному объекту каждого класса
    Circle circle(3);
    Ellipse ellipse(5, 2);

    std::cout << "=== 1. Вызов функций у объектов ===\n";
    std::cout << "Объект Circle, printStatic:\n";
    circle.printStatic();
    std::cout << "Объект Ellipse, printStatic:\n";
    ellipse.printStatic();
    std::cout << "Объект Circle, printDynamic:\n";
    circle.printDynamic();
    std::cout << "Объект Ellipse, printDynamic:\n";
    ellipse.printDynamic();

    // 2. Указатель базового класса на объект производного класса
    Circle* ptr = &ellipse;

    std::cout << "\n=== 2. Статический полиморфизм (указатель Circle* на Ellipse) ===\n";
    ptr->printStatic();      // вызвана функция Circle: тип указателя определяет выбор

    std::cout << "\n=== 3. Динамический полиморфизм (указатель Circle* на Ellipse) ===\n";
    ptr->printDynamic();     // вызвана функция Ellipse: тип объекта определяет выбор

    // 4. Вектор указателей на объекты базового и производного классов
    std::cout << "\n=== 4. Вектор указателей ===\n";
    Circle* heapFigure = new Ellipse(7, 4);   // объект в динамической памяти

    std::vector<Circle*> figures;
    figures.push_back(&circle);      // базовый класс
    figures.push_back(&ellipse);     // производный класс
    figures.push_back(heapFigure);   // производный класс в динамической памяти

    for (std::size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Объект " << i + 1 << ":\n";
        figures[i]->printDynamic();
    }

    delete heapFigure;   // освобождаем память, выделенную через new
    return 0;
}

