#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Узел для очереди
struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Очередь
struct Queue {
    Node* front;  // Указатель на голову очереди
    Node* rear;   // Указатель на хвост очереди

    Queue() : front(nullptr), rear(nullptr) {}

    // Добавление элемента в конец очереди
    void push(int value) {
        Node* newNode = new Node(value);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Удаление элемента с головы очереди
    void pop() {
        if (front == nullptr) {
            cout << "Очередь пуста, нечего удалять!" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;  // Если очередь стала пустой
        }
        delete temp;
    }

    // Вывод всех элементов очереди
    void print() const {
        if (front == nullptr) {
            cout << "Очередь пуста!" << endl;
            return;
        }
        Node* temp = front;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Запись очереди в файл
    void saveToFile(const string &filename) const {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            Node* temp = front;
            while (temp != nullptr) {
                outFile << temp->data << " ";
                temp = temp->next;
            }
            outFile.close();
            cout << "Очередь сохранена в файл " << filename << endl;
        } else {
            cout << "Не удалось открыть файл для записи!" << endl;
        }
    }

    // Загрузка очереди из файла
    void loadFromFile(const string &filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            int value;
            while (inFile >> value) {
                push(value);
            }
            inFile.close();
            cout << "Очередь загружена из файла " << filename << endl;
        } else {
            cout << "Не удалось открыть файл для чтения!" << endl;
        }
    }

    // Очистка очереди
    void clear() {
        while (front != nullptr) {
            pop();
        }
    }

    // Деструктор
    ~Queue() {
        clear();  // Освобождаем память при удалении очереди
    }
};

// Функция обработки команд
void processCommand(Queue &queue, const string &commandLine) {
    stringstream ss(commandLine);
    string command;
    ss >> command;

    if (command == "PUSH") {
        int value;
        ss >> value;
        queue.push(value);

    } else if (command == "POP") {
        queue.pop();

    } else if (command == "PRINT") {
        queue.print();

    } else if (command == "SAVE") {
        string filename;
        ss >> filename;
        queue.saveToFile(filename);

    } else if (command == "LOAD") {
        string filename;
        ss >> filename;
        queue.loadFromFile(filename);
    }
}

int main() {
    Queue queue;
    string commandLine;

    while (true) {
        getline(cin, commandLine);

        if (commandLine == "EXIT") {
            break;  // выход из программы
        }

        processCommand(queue, commandLine);  // обработка команды
    }

    return 0;
}

/*
PUSH <value> — добавляет элемент в конец очереди.
POP — удаляет элемент с головы очереди.
PEEK — показывает элемент на голове очереди.
PRINT — выводит все элементы очереди.
SAVE <filename> — сохраняет очередь в файл.
LOAD <filename> — загружает очередь из файла. 
EXIT — завершает выполнение программы.
*/