#include <bits/stdc++.h> 
using namespace std;
int n = 0, a[100010];
int main() {
	char c = getchar();
	while (!(c == 'W' || c == 'L' || c == 'E')) c = getchar();
	while (c != 'E') {
		if (c == 'W') a[++n] = 1;
		else a[++n] = 0;
		c = getchar();
		while (!(c == 'W' || c == 'L' || c == 'E')) c = getchar();
	}
	int i = 1, j = 0, x = 0, y = 0;
	while (i <= n) {
		j++;
		if (a[i]) x++;
		else y++;
		if (j >= 11 && (x - y >= 2 || y - x >= 2)) {
			printf("%d:%d\n", x, y);
			x = y = j = 0;
		}
		i++;
	}
	printf("%d:%d\n", x, y);
	puts("");
	i = 1, j = 0, x = 0, y = 0;
	while (i <= n) {
		j++;
		if (a[i]) x++;
		else y++;
		if (j >= 21 && (x - y >= 2 || y - x >= 2)) {
			printf("%d:%d\n", x, y);
			x = y = j = 0;
		}
		i++;
	}
	printf("%d:%d\n", x, y);
	return 0;
}  
