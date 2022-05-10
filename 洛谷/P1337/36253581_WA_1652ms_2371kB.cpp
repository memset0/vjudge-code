#include <bits/stdc++.h>
#define sqr(x) ((x)*(x))
#define ll long long
using namespace std;

int read() {
    int x = 0; bool m = 0; char c = getchar();
    while (!isdigit(c) && c != '-') c = getchar();
    if (c == '-') m = 1, c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (m) return -x; else return x;
}

const int maxn = 1010;
const double tstart = 20000, tend = 1e-13, tdelta = 0.9995;
int n;
double a[maxn], b[maxn], w[maxn];
double t, ux, uy, uans, vx, vy, vans;

double calc(double x, double y) {
	double sum = 0;
	for (int i = 1; i <= n; i++)
		sum += sqrt(sqr(a[i] - x) + sqr(b[i] - y)) * w[i];
	return sum;
}


int main() {
	srand(20040214);
	n = read();
	for (int i = 1; i <= n; i++)
		a[i] = read(), b[i] = read(), w[i] = read();
	for (int i = 1; i <= n; i++)	
		ux += a[i], uy += b[i];
	ux /= n, uy /= n;
	uans = calc(ux, uy);
	t = tstart;
	while (t > tend) {
//		printf("%.3lf %.3lf %.3lf %.3lf\n", ux, uy, vx, vy);
		vx = ux + (rand() *  2 - RAND_MAX) * t;
		vy = uy + (rand() *  2 - RAND_MAX) * t;
		vans = calc(vx, vy);
		if (vans < uans) {
			ux = vx, uy = vy, uans = vans;
		} else if (exp((uans - vans) / t) * RAND_MAX > rand()) {
			ux = vx, uy = vy, uans = vans;
		}
		t *= tdelta;
	}
	printf("%.3lf %.3lf", ux, uy);
	return 0;
}