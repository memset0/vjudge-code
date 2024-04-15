// luogu-judger-enable-o2
#include <bits/stdc++.h>
#define CIOS ios::sync_with_stdio(false);
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> ";
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template <typename T>
inline void read(T &f) {
    f = 0; T fu = 1; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') fu = -1; c = getchar(); }
    while (c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int md = 2009;

struct mat { int a[91][91]; };

mat now;
int n, t;

mat operator * (const mat a, const mat b) {
    mat ans; memset(ans.a, 0, sizeof(ans.a));
    for(register int i = 1; i <= n * 9; i++)
        for(register int k = 1; k <= n * 9; k++) {
            for(register int j = 1; j <= n * 9; j++)
                ans.a[i][j] += a.a[i][k] * b.a[k][j];
        }
    for (register int i = 1; i <= n * 9; i++)
        for (register int j = 1; j <= n * 9; j++)
            ans.a[i][j] %= md;
    return ans;
}

mat fpow(mat x, int y) {
    mat ans = x; y--;
    while(y) {
        if(y & 1) ans = ans * x;
        y >>= 1; x = x * x;
    }
    return ans;
}

inline int calc(int x, int y) { return (x - 1) * 9 + y + 1; }

int main() {
    read(n); read(t);
    for(register int i = 1; i <= n; i++) {
        for(register int j = 1; j <= 8; j++) now.a[calc(i, j)][calc(i, j - 1)] = 1; 
        for(register int j = 1; j <= n; j++) {
            char c = getchar();
            while(c < '0' || c > '9') c = getchar();
            int val = c - '0';
            if(val) now.a[calc(i, 0)][calc(j, val - 1)] = 1;
        }
    }
    /*
    for(register int i = 1; i <= n * 9; i++) {
        for(register int j = 1; j <= n * 9; j++) {
            print(now.a[i][j], j == (n * 9) ? '\n' : ' ');
        }
    }
    */
    cout << fpow(now, t).a[calc(1, 0)][calc(n, 0)] << endl;
    return 0;
}

// Rotate Flower Round.