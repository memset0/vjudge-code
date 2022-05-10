#include <bits/stdc++.h>
#define u q[l]
#define v q[r]
using namespace std;
const int mov[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int l, r, i, j, t, ans;
char a[5][5];
bool mrk, find_ans;
struct Node {
	char a[5][5];
	int x, y, h;
} q[1000000];
int main() {
	for (i = 1; i <= 4; i++)
		for (j = 1; j <= 4; j++)
			cin >> a[i][j];
	int sx1 = -1, sx2 = -1, sy1 = -1, sy2 = -1, sfound = 0;
	for (i = 1; i <= 4; i++)
		for (j = 1; j <= 4; j++)
			if (a[i][j] == 'O')
				if (sfound) sx2 = i, sy2 = j;
				else sx1 = i, sy1 = j, sfound = 1;
				
	l = 1, r = 2;
	for (i = 1; i <= 4; i++)
		for (j = 1; j <= 4; j++)
			q[1].a[i][j] = q[2].a[i][j] = a[i][j];
	q[1].x = sx1, q[1].y = sy1, q[1].h = 0;
	q[2].x = sx2, q[2].y = sy2, q[2].h = 0;
	int t, i, j;
	bool mrk;
	while (l <= r) {
		
//		if (u.h == 5) {
//			printf("=====\n%d %d %d\n", u.x, u.y, u.h);
//			for (i = 1; i <= 4; i++) {
//				for (j = 1; j <= 4; j++)
//					printf("%c ", u.a[i][j]);
//				puts("");
//			}
//		}
		
		for (t = 0; t < 4; t++) {
			r++;
			v.x = u.x + mov[t][0];
			v.y = u.y + mov[t][1];
			v.h = u.h + 1;
			if (v.x < 1 || v.y < 1 || v.x > 4 || v.y > 4) {
				r--;
				continue;
			}
			for (i = 1; i <= 4; i++)
				for (j = 1; j <= 4; j++)
					v.a[i][j] = u.a[i][j];
			swap(v.a[u.x][u.y], v.a[v.x][v.y]);
			
			for (i = 1; i <= 4; i++) {
				mrk = 1;
				for (j = 2; j <= 4; j++)
					if (v.a[i][j] != v.a[i][j - 1]) {
						mrk = 0;
						break;
					}
				if (mrk) {
					find_ans = 1;
					ans = v.h;
					break;
				}
			}
			
			for (i = 1; i <= 4; i++) {
				mrk = 1;
				for (j = 1; j <= 4; j++)
					if (v.a[j][i] != v.a[j - 1][i]) {
						mrk = 0;
						break;
					}
				if (mrk) {
					find_ans = 1;
					ans = v.h;
					break;
				}
			}
			
			mrk = 1;
			for (i = 2; i <= 4; i++)
				if (v.a[i][i] != v.a[i - 1][i - 1]) {
					mrk = 0;
				}
			if (mrk) {
				find_ans = 1;
				ans = v.h;
				break;
			}
			
			mrk = 1;
			for (i = 2; i <= 4; i++)
				if (v.a[i][5 - i] != v.a[i - 1][6 - i]) {
					mrk = 0;
				}
			if (mrk) {
				find_ans = 1;
				ans = v.h;
				break;
			}
			
			
		}
		if (find_ans) break;
		l++;
	}
	
	printf("%d\n", ans);
	
	return 0;
}