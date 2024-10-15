#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// Структура для хранения пары ключ-значение
struct KeyValuePair {
    int key;
    string value;
    KeyValuePair* next;

    KeyValuePair(int k, const string &v) : key(k), value(v), next(nullptr) {}
};

// Размер хеш-таблицы
const int capacity = 10;

// Структура для хеш-таблицы
struct HashTable {
    KeyValuePair* table[capacity];

    // Инициализация
    HashTable() {
        for (int i = 0; i < capacity; ++i) {
            table[i] = nullptr;  // Изначально все ячейки пусты
        }
    }
};

// Хеш-функция
int hashFunction(int key) {
    return key % capacity;
}

// Добавление элемента (ключ-значение) в хеш-таблицу
void insert(HashTable &hashTable, int key, const string &value) {
    int index = hashFunction(key);
    KeyValuePair* newNode = new KeyValuePair(key, value);

    // Если в ячейке еще нет элементов
    if (hashTable.table[index] == nullptr) {
        hashTable.table[index] = newNode;
    } else {
        // Обрабатываем коллизию методом цепочек
        KeyValuePair* current = hashTable.table[index];
        while (current->next != nullptr) {
            if (current->key == key) {
                current->value = value;  // Обновляем значение, если ключ уже существует
                delete newNode;
                return;
            }
            current = current->next;
        }
        // Если достигли конца цепочки
        if (current->key == key) {
            current->value = value;  // Обновляем значение
            delete newNode;
        } else {
            current->next = newNode;  // Добавляем новый элемент в конец цепочки
        }
    }
}

// Получение значения по ключу
string get(const HashTable &hashTable, int key) {
    int index = hashFunction(key);
    KeyValuePair* current = hashTable.table[index];

    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return "Ключ не найден";  // Если ключ не найден
}

// Удаление элемента по ключу
void remove(HashTable &hashTable, int key) {
    int index = hashFunction(key);
    KeyValuePair* current = hashTable.table[index];
    KeyValuePair* prev = nullptr;

    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                hashTable.table[index] = current->next;  // Удаляем первый элемент в цепочке
            } else {
                prev->next = current->next;  // Удаляем элемент из середины или конца цепочки
            }
            delete current;  // Освобождаем память
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "Ключ не найден" << endl;
}

// Вывод всей хеш-таблицы
void print(const HashTable &hashTable) {
    for (int i = 0; i < capacity; ++i) {
        cout << "[" << i << "]: ";
        KeyValuePair* current = hashTable.table[i];
        while (current != nullptr) {
            cout << "{" << current->key << ": " << current->value << "} ";
            current = current->next;
        }
        cout << endl;
    }
}

// Сохранение хеш-таблицы в файл
void saveToFile(const HashTable &hashTable, const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл для записи!" << endl;
        return;
    }

    for (int i = 0; i < capacity; ++i) {
        KeyValuePair* current = hashTable.table[i];
        while (current != nullptr) {
            file << current->key << " " << current->value << endl;  // Сохраняем ключ-значение в файл
            current = current->next;
        }
    }
    file.close();
    cout << "Данные сохранены в файл " << filename << endl;
}

// Загрузка хеш-таблицы из файла
void loadFromFile(HashTable &hashTable, const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл для чтения!" << endl;
        return;
    }

    // Очищаем текущую таблицу
    for (int i = 0; i < capacity; ++i) {
        while (hashTable.table[i] != nullptr) {
            KeyValuePair* temp = hashTable.table[i];
            hashTable.table[i] = hashTable.table[i]->next;
            delete temp;
        }
    }

    int key;
    string value;
    while (file >> key >> value) {
        insert(hashTable, key, value);  // Вставляем ключ-значение в хеш-таблицу
    }

    file.close();
    cout << "Данные загружены из файла " << filename << endl;
}

// Функция обработки команд
void processCommand(HashTable &hashTable, const string &commandLine) {
    stringstream ss(commandLine);
    string command;
    ss >> command;

    if (command == "INSERT") {
        int key;
        string value;
        ss >> key >> value;
        insert(hashTable, key, value);

    } else if (command == "GET") {
        int key;
        ss >> key;
        cout << "Значение: " << get(hashTable, key) << endl;

    } else if (command == "REMOVE") {
        int key;
        ss >> key;
        remove(hashTable, key);

    } else if (command == "PRINT") {
        print(hashTable);

    } else if (command == "SAVE") {
        string filename;
        ss >> filename;
        saveToFile(hashTable, filename);

    } else if (command == "LOAD") {
        string filename;
        ss >> filename;
        loadFromFile(hashTable, filename);
    }
}

int main() {
    HashTable hashTable;  // Инициализация хеш-таблицы
    string commandLine;

    while (true) {
        getline(cin, commandLine);

        if (commandLine == "EXIT") {
            break;  // Выход из программы
        }

        processCommand(hashTable, commandLine);  // Обработка команды
    }

    return 0;
}

/*
INSERT <key> <value> — добавляет элемент с ключом и значением. 
GET <key> — получает значение элемента по ключу. 
REMOVE <key> — удаляет элемент по ключу. 
PRINT — выводит текущее состояние хеш-таблицы.
SAVE <filename> — сохраняет текущую таблицу в файл.
LOAD <filename> — загружает данные в таблицу из файла.
EXIT — завершает выполнение программы.
*/
