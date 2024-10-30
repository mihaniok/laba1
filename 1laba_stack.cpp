#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Узел для стека
struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Стек
struct Stack {
    Node* top;  // Указатель на вершину стека

    Stack() : top(nullptr) {}

    // Добавление элемента на вершину стека
    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    // Удаление элемента с вершины стека
    void pop() {
        if (top == nullptr) {
            cout << "Стек пуст, нечего удалять!" << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    // Вывод всех элементов стека
    void print() const {
        if (top == nullptr) {
            cout << "Стек пуст!" << endl;
            return;
        }
        Node* temp = top;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Запись стека в файл
    void saveToFile(const string &filename) const {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            Node* temp = top;
            while (temp != nullptr) {
                outFile << temp->data << " ";
                temp = temp->next;
            }
            outFile.close();
            cout << "Стек сохранён в файл " << filename << endl;
        } else {
            cout << "Не удалось открыть файл для записи!" << endl;
        }
    }

    // Загрузка стека из файла
    void loadFromFile(const string &filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            int value;
            while (inFile >> value) {
                push(value);  // добавляем элементы в стек
            }
            inFile.close();
            cout << "Стек загружен из файла " << filename << endl;
        } else {
            cout << "Не удалось открыть файл для чтения!" << endl;
        }
    }

    // Очистка стека
    void clear() {
        while (top != nullptr) {
            pop();
        }
    }

    // Деструктор
    ~Stack() {
        clear();  // Освобождаем память при удалении стека
    }
};

// Функция обработки команд
void processCommand(Stack &stack, const string &commandLine) {
    stringstream ss(commandLine);
    string command;
    ss >> command;

    if (command == "PUSH") {
        int value;
        ss >> value;
        stack.push(value);

    } else if (command == "POP") {
        stack.pop();

    } else if (command == "PRINT") {
        stack.print();

    } else if (command == "SAVE") {
        string filename;
        ss >> filename;
        stack.saveToFile(filename);

    } else if (command == "LOAD") {
        string filename;
        ss >> filename;
        stack.loadFromFile(filename);
    }
}

int main() {
    Stack stack;
    string commandLine;

    while (true) {
        getline(cin, commandLine);

        if (commandLine == "EXIT") {
            break;  // выход из программы
        }

        processCommand(stack, commandLine);  // обработка команды
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
