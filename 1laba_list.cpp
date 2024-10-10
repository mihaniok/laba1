#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

// Узел односвязного списка
struct Node {
    int data;
    Node* next;
    
    Node(int value) : data(value), next(nullptr) {}
};

// Односвязный список
struct SinglyLinkedList {
    Node* head;

    SinglyLinkedList() : head(nullptr) {}

    // Добавление элемента в голову
    void push_front(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Добавление элемента в хвост
    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Удаление элемента с головы
    void pop_front() {
        if (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Удаление элемента с хвоста
    void pop_back() {
        if (!head) return;
        if (!head->next) {
            delete head;
            head = nullptr;
        } else {
            Node* temp = head;
            while (temp->next->next) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
    }

    // Удаление элемента по значению
    void remove(int value) {
        if (!head) return;
        if (head->data == value) {
            pop_front();
            return;
        }
        Node* temp = head;
        while (temp->next && temp->next->data != value) {
            temp = temp->next;
        }
        if (temp->next) {
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }
    }

    // Поиск элемента по значению
    bool find(int value) const {
        Node* temp = head;
        while (temp) {
            if (temp->data == value) return true;
            temp = temp->next;
        }
        return false;
    }

    // Вывод всех элементов списка
    void print() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Запись списка в файл
    void saveToFile(const string& filename) const {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            Node* temp = head;
            while (temp) {
                outFile << temp->data << " ";
                temp = temp->next;
            }
            outFile.close();
            cout << "Список сохранен в файл " << filename << endl;
        } else {
            cout << "Не удалось открыть файл для записи!" << endl;
        }
    }

    // Загрузка списка из файла
    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            int value;
            while (inFile >> value) {
                push_back(value);
            }
            inFile.close();
            cout << "Список загружен из файла " << filename << endl;
        } else {
            cout << "Не удалось открыть файл для чтения!" << endl;
        }
    }
};

// Функция обработки команд
void processCommand(SinglyLinkedList &list, const string &commandLine) {
    stringstream ss(commandLine);
    string command;
    ss >> command;

    if (command == "PUSHFRONT") {
        int value;
        ss >> value;
        list.push_front(value);

    } else if (command == "PUSHBACK") {
        int value;
        ss >> value;
        list.push_back(value);

    } else if (command == "POPFRONT") {
        list.pop_front();

    } else if (command == "POPBACK") {
        list.pop_back();

    } else if (command == "REMOVE") {
        int value;
        ss >> value;
        list.remove(value);

    } else if (command == "FIND") {
        int value;
        ss >> value;
        cout << (list.find(value) ? "Found" : "Not Found") << endl;

    } else if (command == "PRINT") {
        list.print();

    } else if (command == "SAVE") {
        string filename;
        ss >> filename;
        list.saveToFile(filename);

    } else if (command == "LOAD") {
        string filename;
        ss >> filename;
        list.loadFromFile(filename);
    }
}

int main() {
    SinglyLinkedList list;
    string commandLine;

    while (true) {
        getline(cin, commandLine);

        if (commandLine == "EXIT") {
            break;  // выход из программы
        }

        processCommand(list, commandLine);  // обработка команды
    }

    return 0;
}

/*
PUSHFRONT <value> — добавляет элемент в голову списка.
PUSHBACK <value> — добавляет элемент в хвост списка.
POPFRONT — удаляет элемент с головы списка.
POPBACK — удаляет элемент с хвоста списка.
REMOVE <value> — удаляет первый элемент со значением <value>.
FIND <value> — ищет элемент в списке.
PRINT — выводит текущие элементы списка.
SAVE <filename> — сохраняет список в файл.
LOAD <filename> — загружает список из файла.
EXIT — завершает программу.
*/