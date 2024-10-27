#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Структура для хранения пары ключ-значение
struct KeyValuePair {
    string key;
    string value;
    KeyValuePair* next;

    KeyValuePair(const string& k, const string& v) : key(k), value(v), next(nullptr) {}
};

// Размер хеш-таблицы
const int capacity = 10;

// Структура для хеш-таблицы
struct HashTable {
    KeyValuePair* table[capacity];

    // Конструктор, инициализирующий массив пустыми цепочками
    HashTable() {
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    // Деструктор для освобождения памяти
    ~HashTable() {
        for (int i = 0; i < capacity; i++) {
            KeyValuePair* current = table[i];
            while (current != nullptr) {
                KeyValuePair* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
    }
};

// Хеш-функция: вычисляет индекс по сумме ASCII-кодов символов ключа
int hashFunction(const string& key) {
    int sum = 0;
    for (char c : key) {
        sum += static_cast<int>(c);
    }
    return sum % capacity;
}

// Добавление элемента (ключ-значение) в хеш-таблицу
void insert(HashTable& hashTable, const string& key, const string& value) {
    int index = hashFunction(key);
    KeyValuePair* newNode = new KeyValuePair(key, value);
    KeyValuePair* current = hashTable.table[index];

    // Проверяем, существует ли элемент с таким же ключом
    while (current != nullptr) {
        if (current->key == key) {
            current->value = value;  // Обновляем значение, если ключ уже существует
            delete newNode;
            return;
        }
        current = current->next;
    }

    // Вставляем новый элемент в начало цепочки
    newNode->next = hashTable.table[index];
    hashTable.table[index] = newNode;
}

// Получение значения по ключу
string get(const HashTable& hashTable, const string& key) {
    int index = hashFunction(key);
    KeyValuePair* current = hashTable.table[index];
    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return "Key not found";
}

// Удаление элемента по ключу
void remove(HashTable& hashTable, const string& key) {
    int index = hashFunction(key);
    KeyValuePair* current = hashTable.table[index];
    KeyValuePair* prev = nullptr;

    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                hashTable.table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            cout << "Key removed." << endl;
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "Key not found." << endl;
}

// Вывод всей хеш-таблицы
void print(const HashTable& hashTable) {
    for (int i = 0; i < capacity; i++) {
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
void saveToFile(const HashTable& hashTable, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    for (int i = 0; i < capacity; i++) {
        KeyValuePair* current = hashTable.table[i];
        while (current != nullptr) {
            file << current->key << " " << current->value << endl;
            current = current->next;
        }
    }
    file.close();
    cout << "Hash table saved to file." << endl;
}

// Загрузка хеш-таблицы из файла
void loadFromFile(HashTable& hashTable, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file for reading!" << endl;
        return;
    }
    string key, value;
    while (file >> key >> value) {
        insert(hashTable, key, value);
    }
    file.close();
    cout << "Hash table loaded from file." << endl;
}

// Функция обработки команд
void processCommand(HashTable& hashTable, const string& commandLine) {
    stringstream ss(commandLine);
    string command, key, value;
    ss >> command;

    if (command == "INSERT") {
        ss >> key >> value;
        insert(hashTable, key, value);
    } else if (command == "GET") {
        ss >> key;
        cout << "Value: " << get(hashTable, key) << endl;
    } else if (command == "REMOVE") {
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
    HashTable hashTable;
    string commandLine;

    while (true) {
        getline(cin, commandLine);
        if (commandLine == "EXIT") {
            break;
        }
        processCommand(hashTable, commandLine);
    }

    return 0;
}


/*
INSERT <ключ> <значение>: Вставка пары "ключ-значение" в хеш-таблицу
GET <ключ>: Получение значения по ключу
REMOVE <ключ>: Удаление элемента по ключу
PRINT: Вывод текущего состояния хеш-таблицы
SAVE <имя_файла>: Сохранение хеш-таблицы в файл
LOAD <имя_файла>: Загрузка хеш-таблицы из файла
EXIT: Завершение программы
*/
