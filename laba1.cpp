#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int a, b, P, S;
	double D;
	a = 10;
	b = 8;
	P = 2 * (a + b);
	S = a * b;
	D = pow((pow(a, 2) + pow(b, 2)), 0.5);
	cout << " S = " << S << endl;
	cout << " P = " << P << endl;
	cout << " D = " << D << endl;
	return 0;
}
