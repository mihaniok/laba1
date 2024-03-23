#include <iostream>
#include <cmath>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	int a, b, P, S;// P - периметр, S - площадь
	double D;// D - диагональ

	cout << "Введите длину прямоугольника ";
	cin >> a;
	cout << "Введите ширину прямоугольника ";
	cin >> b;
	P = 2 * (a + b);
	S = a * b;
	D = pow((pow(a, 2) + pow(b, 2)), 0.5);
	cout << " Площадь прямоугольника = " << S << endl;
	cout << " Периметр прямоугольника = " << P << endl;
	cout << " Диагональ прямоугольника = " << D << endl;
	return 0;
}
