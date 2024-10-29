#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct Array {
    static const int capacity = 10000;  // фиксированная вместимость
    int data[capacity];  // массив 
    int length;          // текущее количество элементов
    Array() : length(0) {} 

    // функция добавления эл. в конец
    void push_back(int value) {
        if (length < capacity) {
            data[length++] = value;  // добавляем элемент в конец
        } else {
            cout << "Array is full" << endl;
        }
    }

    // Удаление элемента по индексу
    void remove(int index) {
        if (index >= 0 && index < length) {
            for (int i = index; i < length - 1; i++) {
                data[i] = data[i + 1];  // сдвигаем элементы влево
            }
            length--;
        } else {
            cout << "Invalid index" << endl;
        }
    }

    // Замена элемента по индексу
    void replace(int index, int value) {
        if (index >= 0 && index < length) {
            data[index] = value;  // заменяем элемент
        } else {
            cout << "Invalid index" << endl;
        }
    }

    // Получение элемента по индексу
    int get(int index) const {
        return index >= 0 && index < length ? data[index] : -1;  // возвращает -1 при неверном индексе
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
            cout << "Array saved in file: " << filename << endl;
        } else {
            cout << "Cannot open file" << endl;
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
            cout << "Array loaded from file: " << filename << endl;
        } else {
            cout << "Cannot open file" << endl;
        }
    }
};

// Функция обработки команд
void processCommand(Array &arr, const string &commandLine) {
    stringstream ss(commandLine);
    string command;
    ss >> command;

    if (command == "PUSH") {
        int value;
        ss >> value;
        arr.push_back(value);  // добавляем значение в конец массива

    } else if (command == "DEL") {
        int index;
        ss >> index;
        arr.remove(index);  // удаляем элемент по индексу

    } else if (command == "REPLACE") {
        int index, value;
        ss >> index >> value;
        arr.replace(index, value);  // заменяем элемент по индексу

    } else if (command == "GET") {
        int index;
        ss >> index;
        int result = arr.get(index);
        if (result != -1) {
            cout << result << endl;
        } else {
            cout << "Invalid index" << endl;
        }

    } else if (command == "PRINT") {
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
    Array arr;
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
