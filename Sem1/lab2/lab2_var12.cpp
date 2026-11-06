#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Структура «океанское судно»
struct Ship {
    string name;     // название
    string captain;  // ФИО капитана
    double tonnage;  // водоизмещение, тыс. тонн
    int crew;        // численность экипажа
};

// Запись одного судна в файл (bin = true - двоичный режим, false - текстовый)
void writeShip(ofstream& f, Ship& s, bool bin) {
    if (bin) {
        f << s.name << '\0' << s.captain << '\0';      // строки с нулём в конце
        f.write((char*)&s.tonnage, sizeof(s.tonnage));
        f.write((char*)&s.crew, sizeof(s.crew));
    } else {
        f << s.name << endl << s.captain << endl << s.tonnage << ' ' << s.crew << endl;
    }
}

// Чтение одного судна из файла
void readShip(ifstream& f, Ship& s, bool bin) {
    if (bin) {
        getline(f, s.name, '\0');
        getline(f, s.captain, '\0');
        f.read((char*)&s.tonnage, sizeof(s.tonnage));
        f.read((char*)&s.crew, sizeof(s.crew));
    } else {
        f >> ws;                // пропуск перевода строки
        getline(f, s.name);
        getline(f, s.captain);
        f >> s.tonnage >> s.crew;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Use: write|read text|binary file" << endl;
        return 1;
    }
    string mode = argv[1];
    bool bin = string(argv[2]) == "binary";
    string file = argv[3];

    int n;
    vector<Ship> ships;

    if (mode == "write") {
        cout << "n = ";
        cin >> n;
        ships.resize(n);
        for (int i = 0; i < n; ++i) {
            cout << "Ship " << i + 1 << endl;
            cout << "Name: ";      cin >> ws; getline(cin, ships[i].name);
            cout << "Captain: ";   getline(cin, ships[i].captain);
            cout << "Tonnage: ";   cin >> ships[i].tonnage;
            cout << "Crew: ";      cin >> ships[i].crew;
        }

        ofstream f(file, bin ? ios::binary : ios::out);
        if (bin) f.write((char*)&n, sizeof(n));
        else f << n << endl;
        for (int i = 0; i < n; ++i)
            writeShip(f, ships[i], bin);
        f.close();
    }
    else if (mode == "read") {
        ifstream f(file, bin ? ios::binary : ios::in);
        if (!f) {
            cout << "File not found" << endl;
            return 1;
        }
        if (bin) f.read((char*)&n, sizeof(n));
        else f >> n;
        ships.resize(n);
        for (int i = 0; i < n; ++i)
            readShip(f, ships[i], bin);
        f.close();

        for (int i = 0; i < n; ++i)
            cout << ships[i].name << ", " << ships[i].captain << ", "
                 << ships[i].tonnage << " thous. t, " << ships[i].crew << " crew" << endl;
    }
    return 0;
}
