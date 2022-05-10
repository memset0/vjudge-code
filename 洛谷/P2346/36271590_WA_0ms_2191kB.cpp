#include <bits/stdc++.h>
#define u q[l]
#define v q[r]
using namespace std;
const int mov[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int l, r, i, j, t, f, ans;
char a[5][5];
bool mrk, find_ans;
struct Node {
    char a[5][5];
    int x[2], y[2], h;
} q[1000000];
bool judge(Node x)
{
    for (int i=1;i<=4;i++) {
        if (x.a[i][1] == x.a[i][2] && x.a[i][3] == x.a[i][2] && x.a[i][3] == x.a[i][4]) return 1;
        if (x.a[1][i] == x.a[2][i] && x.a[3][i] == x.a[2][i] && x.a[3][i] == x.a[4][i]) return 1;
    }
    if (x.a[1][1] == x.a[2][2] && x.a[3][3] == x.a[2][2] && x.a[3][3] == x.a[4][4]) return 1;
    if (x.a[4][1] == x.a[3][2] && x.a[2][3] == x.a[3][2] && x.a[2][3] == x.a[1][4]) return 1;
    return 0;
}
int main() {
    for (i = 1; i <= 4; i++)
        for (j = 1; j <= 4; j++)
            cin >> a[i][j];
    int sx1 = -1, sx2 = -1, sy1 = -1, sy2 = -1, sfound = 0;
    for (i = 1; i <= 4; i++)
        for (j = 1; j <= 4; j++)
            if (a[i][j] == 'O') {
                if (sfound) sx2 = i, sy2 = j;
                else sx1 = i, sy1 = j;
				sfound++;
            }
	if (sfound < 2) while(1);
                
    l = r = 1;
    for (i = 1; i <= 4; i++)
        for (j = 1; j <= 4; j++)
            q[1].a[i][j] = a[i][j];
    q[1].x[0] = sx1, q[1].y[0] = sy1, q[1].x[1] = sx2, q[1].y[1] = sy2, q[1].h = 0;
    bool mrk;
    
    while (l <= r) {
        
//		printf("=====\n%d %d %d %d %d\n", u.x[0], u.y[0], u.x[1], u.y[1], u.h);
//		for (i = 1; i <= 4; i++) {
//			for (j = 1; j <= 4; j++)
//				printf("%c ", u.a[i][j]);
//			puts("");
//		}
        
        for (f = 0; f < 2; f++) {
            for (t = 0; t < 4; t++) {
                r++;
                v.x[f] = u.x[f] + mov[t][0];
                v.y[f] = u.y[f] + mov[t][1];
                v.x[f ^ 1] = u.x[f ^ 1];
                v.y[f ^ 1] = u.y[f ^ 1];
                v.h = u.h + 1;
                if (v.x[f] < 1 || v.y[f] < 1 || v.x[f] > 4 || v.y[f] > 4) {
                    r--;
                    continue;
                }
                for (i = 1; i <= 4; i++)
                    for (j = 1; j <= 4; j++)
                        v.a[i][j] = u.a[i][j];
                swap(v.a[u.x[f]][u.y[f]], v.a[v.x[f]][v.y[f]]);
                
				if (judge(v)) {
					find_ans = 1;
					ans = v.h;
					break;
				}
				
            }
        }
        if (find_ans) break;
        l++;
    }
    
    printf("%d\n", ans);
    
    return 0;
}



/*

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
                
                
                
                
                */