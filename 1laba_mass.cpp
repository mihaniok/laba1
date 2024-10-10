#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct StaticArray {
    static const int capacity = 10000;  // фиксированная вместимость
    int data[capacity];  // массив фиксированного размера
    int length;          // текущее количество элементов

    // Конструктор
    StaticArray() : length(0) {}

    // Добавление элемента в конец
    void push_back(int value) {
        data[length++] = value;  // добавляем элемент в конец
    }

    // Удаление элемента по индексу
    void remove(int index) {
        for (int i = index; i < length - 1; i++) {
            data[i] = data[i + 1];  // сдвигаем элементы влево
        }
        length--;
    }

    // Получение элемента по индексу
    int get(int index) const {
        return data[index];
    }

    // Получение длины массива
    int size() const {
        return length;
    }

    // Вывод элементов массива
    void print() const {
        for (int i = 0; i < length; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    // Запись массива в файл
    void saveToFile(const string &filename) const {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << length << endl;  // сначала записываем длину массива
            for (int i = 0; i < length; i++) {
                outFile << data[i] << " ";  // записываем элементы массива
            }
            outFile.close();
            cout << "Массив сохранен в файл " << filename << endl;
        } else {
            cout << "Не удалось открыть файл для записи!" << endl;
        }
    }

    // Чтение массива из файла
    void loadFromFile(const string &filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            inFile >> length;  // считываем количество элементов
            for (int i = 0; i < length; i++) {
                inFile >> data[i];  // считываем элементы массива
            }
            inFile.close();
            cout << "Массив загружен из файла " << filename << endl;
        } else {
            cout << "Не удалось открыть файл для чтения!" << endl;
        }
    }
};

// Функция обработки команд
void processCommand(StaticArray &arr, const string &commandLine) {
    stringstream ss(commandLine);
    string command;
    ss >> command;

    if (command == "MPUSH") {
        int value;
        ss >> value;
        arr.push_back(value);  // добавляем значение в конец массива

    } else if (command == "MDEL") {
        int index;
        ss >> index;
        if (index >= 0 && index < arr.size()) {
            arr.remove(index);  // удаляем элемент по индексу
        }

    } else if (command == "MGET") {
        int index;
        ss >> index;
        if (index >= 0 && index < arr.size()) {
            cout << arr.get(index) << endl;
        }

    } else if (command == "MPRINT") {
        arr.print();

    } else if (command == "SAVE") {
        string filename;
        ss >> filename;
        arr.saveToFile(filename);  // сохраняем массив в файл

    } else if (command == "LOAD") {
        string filename;
        ss >> filename;
        arr.loadFromFile(filename);  // загружаем массив из файла
    }
}

int main() {
    StaticArray arr;
    string commandLine;

    while (true) {
        getline(cin, commandLine);

        if (commandLine == "EXIT") {
            break;  // выход из программы
        }

        processCommand(arr, commandLine);  // обработка команды
    }

    return 0;
}
