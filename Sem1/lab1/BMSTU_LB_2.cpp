// Лабораторная работа №1, часть 2, вариант 12
// Варианты 1, 2, 3, 4, 5, 6, 7, 9, 10, 12

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>   // для настройки кодировки консоли
#include <iomanip>     // для setprecision

using namespace std;

// Дисциплина: название и оценка
struct discipline {
    string name;
    int grade;
};

// Студент: ФИО и список его дисциплин
struct student {
    string full_name;
    vector<discipline> disciplines;
};

// Сколько студентов имеют хотя бы одну двойку
int check_neud(vector<student> &students) {
    int count_discipline = 0;
    for (auto &st: students) {
        // перебираем студентов
        for (auto &d: st.disciplines) {
            // перебираем его дисциплины
            if (d.grade == 2) {
                // нашли двойку
                ++count_discipline; // этот студент с долгом
                break; // дальше его не смотрим
            }
        }
    }
    return count_discipline;
}

// Сколько студентов сдали все экзамены на 5
int check_all_perfect(vector<student> &students) {
    int count_discipline = 0;
    for (auto &st: students) {
        bool flag = true; // предполагаем, что все пятерки

        for (auto &d: st.disciplines) {
            if (d.grade != 5) {
                // нашли не пятерку
                flag = false;
                break;
            }
        }
        if (flag) // все оценки были 5
            ++count_discipline;
    }
    return count_discipline;
}

// Ввод одной дисциплины с клавиатуры
void input_discipline(discipline &disc) {
    cout << "Введит название дисциплины: ";
    getline(cin, disc.name);

    do {
        cout << "Введите оценку (2-5): ";
        cin >> disc.grade;
        cin.clear(); // сбрасываем флаги ошибок ввода
        cin.ignore(10000, '\n'); // очищаем буфер до конца строки
    } while (disc.grade < 2 || disc.grade > 5 || !cin >> disc.grade); // повторяем, пока оценка не в диапазоне 2-5
}

// Ввод одного студента: ФИО и дисциплины
void input_student(student &st) {
    int count_discipline = 0;
    cout << "Введите ФИО студента: ";
    getline(cin, st.full_name);
    do {
        cout << "Введите количество дисциплин (не менее 4): ";
        cin >> count_discipline;
        cin.clear();
        cin.ignore(10000, '\n');
    } while (count_discipline < 4 || !cin >> count_discipline); // минимум 4 дисциплины


    st.disciplines.resize(count_discipline); // выделяем место под все дисциплины

    for (int i = 0; i < count_discipline; i++) {
        cout << "\nДисциплина " << i + 1 << ":\n";
        input_discipline(st.disciplines[i]);
    }
}

// Средний балл группы по заданной дисциплине
double middle_mark(vector<student> &group, string &disc_name) {
    double sum = 0;
    int count = 0;
    for (auto &student: group) {
        for (auto &d: student.disciplines) {
            if (disc_name == d.name) {
                // нашли нужную дисциплину у студента
                sum += d.grade;
                ++count;
                break; // у одного студента она одна
            }
        }
    }
    if (count == 0) {
        // ни одной оценки по предмету
        cout << "Пока нет оценок по этой дисциплине";
    } else
        return sum / count;
}

// Количество отличных оценок по всем предметам группы
int all_perfect(vector<student> &group) {
    int count = 0;
    for (auto &student: group) {
        for (auto &g: student.disciplines) {
            if (g.grade == 5) {
                ++count;
            }
        }
    }
    return count;
}

// Количество двоек по заданной дисциплине
int neud_counter(vector<student> &group, string &disc_name) {
    int count = 0;
    for (auto &student: group) {
        for (auto &g: student.disciplines) {
            if (g.grade == 2 and disc_name == g.name) {
                // двойка по нужному предмету
                ++count;
            }
        }
    }
    return count;
}

// Сколько студентов имеют средний балл от 4 до 5
int middle_grade_45(vector<student> &group) {
    int count = 0;

    for (auto &student: group) {
        double sum = 0;
        int nums = 0;
        for (auto &g: student.disciplines) {
            sum += g.grade;
            ++nums;
        }
        if (sum / nums <= 5 and sum / nums >= 4) {
            // средний балл в диапазоне [4, 5]
            ++count;
        }
    }
    return count;
}

// Общее количество двоек у всей группы
int neud_counter_all(vector<student> &group) {
    int count = 0;
    for (auto &student: group) {
        for (auto &g: student.disciplines) {
            if (g.grade == 2) {
                ++count;
            }
        }
    }
    return count;
}

// Сколько студентов без задолженностей
int students_without_neud(vector<student> &group) {
    int count = 0;
    for (auto &student: group) {
        bool flag = true; // считаем, что долгов нет
        for (auto &g: student.disciplines) {
            if (g.grade == 2) {
                // нашли двойку
                flag = false;
                break;
            }
        }
        if (flag) {
            ++count;
        }
    }
    return count;
}

// Сколько студентов сдали сессию на 4 и 5
int session_on_4or5(vector<student> &group) {
    int count = 0;
    for (auto &student: group) {
        bool flag = true;

        for (auto &g: student.disciplines) {
            if (g.grade <= 4) {
                // оценка 2 или 3 - не подходит
                flag = false;
            }
        }
        if (flag) {
            ++count;
        }
    }
    return count;
}

// Вывод среднего балла каждого студента
void cout_middle_grades(vector<student> &group) {
    cout << "12. Средние баллы студентов: " << endl;
    for (auto &student: group) {
        double sum = 0;
        int nums = 0;
        for (auto &g: student.disciplines) {
            sum += g.grade;
            ++nums;
        }
        cout << student.full_name << ":" << sum / nums << endl;
    }
}



int main() {
    // фикс иероглифов в консле
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // ввод количества студентов в группе (не меньше 1)
    int group_size;
    do {
        cout << "Введите количество студентов в группе: ";
        cin >> group_size;
        cin.clear();
        cin.ignore(10000, '\n');
    } while (group_size < 1 || !cin >> group_size);

    vector<student> students(group_size); // массив студентов нужного размера
    for (int i = 0; i < group_size; i++) {
        input_student(students[i]); // вводим каждого студента
    }
    cout << "1. Студенты с неудовлетворительной оценкой: " << check_neud(students) << endl;
    cout << "2. Студенты - отличники: " << check_all_perfect(students) << endl;
    string disc_name;
    cout << "Ведите название дисциплины для подсчета средней оценки: ";
    getline(cin, disc_name);
    cout << setprecision(3) << "3. Средний балл по дисциплине " << disc_name << ": " << middle_mark(students, disc_name)
            << endl;
    cout << "4. Количество пятерок за все предметы: " << all_perfect(students) << endl;

    cout << "Ведите название дисциплины для подсчета неудов: ";
    getline(cin, disc_name);
    cout << "5. Количество неудов по дисциплине " << disc_name << ": " << neud_counter(students, disc_name)
            << endl;
    cout << "6. Cтудентов имеют средний балл от 4 до 5: " << middle_grade_45(students) << endl;
    cout << "7. Неудов получено: " << neud_counter_all(students) << endl;
    cout << "8. Не буду делать!" << endl;
    cout << "9. Cтудентов без задолженностей: " << students_without_neud(students) << endl;
    cout << "10. Студентов, сдавших сессию на 4-5: " << session_on_4or5(students) << endl;
    cout << "11. Тоже не хочу!" << endl;
    cout_middle_grades(students);
    return 0;
}
