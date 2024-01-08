#include <iostream>
#include <cmath>
using namespace std;
int main() {
	double a, b, c;
	cin >> a >> b >> c;
	if (b == 0)
		cout << a << endl;
	else
		cout << a - min(int(a), int(ceil(c / b))) << endl;
	return 0;
}