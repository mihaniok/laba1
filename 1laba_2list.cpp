#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

// Узел двусвязного списка
struct Node {
    int data;
    Node* next;
    Node* prev;
    
    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

// Двусвязный список
struct DoublyLinkedList {
    Node* head;
    Node* tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Добавление элемента в начало
    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Добавление элемента в конец
    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Удаление элемента с начала
    void pop_front() {
        if (!head) return;
        Node* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
    }

    // Удаление элемента с конца
    void pop_back() {
        if (!tail) return;
        Node* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
    }

    // Удаление элемента по значению
    void remove(int value) {
        Node* temp = head;
        while (temp && temp->data != value) {
            temp = temp->next;
        }
        if (!temp) return;

        if (temp == head) {
            pop_front();
        } else if (temp == tail) {
            pop_back();
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
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
            cout << "List saved in file: " << filename << endl;
        } else {
            cout << "Cannot open file for writing!" << endl;
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
            cout << "List loaded from file: " << filename << endl;
        } else {
            cout << "Cannot open file for reading!" << endl;
        }
    }
};

// Функция обработки команд
void processCommand(DoublyLinkedList &list, const string &commandLine) {
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
    DoublyLinkedList list;
    string commandLine;

    while (true) {
        getline(cin, commandLine);

        if (commandLine == "EXIT") {
            break;
        }

        processCommand(list, commandLine);
    }

    return 0;
}
