#include <iostream>
#include <cmath>

using namespace std;

void prmglnk() {
	int P, S, a, b; // P - периметр, S - площадь, D - диагональ 
	double D;

	cout << "Введите длину прямоугольника ";
	cin >> a;
	cout << "Введите ширину прямоугольника ";
	cin >> b;

	P = 2 * (a + b);
	S = a * b;
	D = pow((pow(a, 2) + pow(b, 2)), 0.5);

	cout << " Периметр прямоугольника = " << P << endl;
	cout << " Площадь прямоугольника = " << S << endl;
	cout << " Диагональ прямоугольника = " << D << endl;
}

void trglnk() {
    int a, b, c, P;
    double S, p; // P - периметр, S - площадь, p - полупериметр

    cout << "Введите первую сторону треугольника ";
    cin >> a;
    cout << "Введите вторую сторону треугольника ";
    cin >> b;
    cout << "Введите третью сторону треугольника ";
    cin >> c;

    if ((a + b > c) && (a + c > b) && (b + c > a))
    {
        P = a + b + c;
        cout << " Периметр прямоугольника = " << P << endl;
        p = P / 2;
        S = sqrt(p * (p - a) * (p - b) * (p - c));//формула Герона
        cout << " Площадь прямоугольника = " << S << endl;
        if ((a == b) || (b == c) || (a == c))
        {
            if ((a == b) && (b == c))
            {
                cout << "Частный случай равнобедренности: треугольник равносторонний";
            }
            else
            {
                cout << "Треугольник равнобедренный";
            }
        }
	cout << "Треугольник неравнобедренный";
    }
    else
    {
        cout << "Треугольник не может существовать";
    }
}

int main() {
	setlocale(LC_ALL, "Russian");
	int figura;
	cout << "выберите фигуру: прямоугольник (1) или треугольник (2)" << endl;
	cin >> figura;
	switch (figura) {
	case (1):
		prmglnk();
		break;
	case (2):
		trglnk();
		break;
	default:
		cout << "вы ввели недопустимое число" << endl;
		break;
	}
	return 0;
}

