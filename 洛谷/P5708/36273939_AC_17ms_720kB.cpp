#include <bits/stdc++.h>
int main() {
	double a, b, c, p, s;
	scanf("%lf %lf %lf", &a, &b, &c);
	p = 0.5 * (a + b + c);
	s = sqrt(p * (p - a) * (p - b) * (p - c));
	printf("%.1f", s);
}
