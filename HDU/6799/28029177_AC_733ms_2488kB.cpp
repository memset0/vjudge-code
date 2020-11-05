#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') { fu = -1; } c = getchar(); }
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

const int N = 1e5 + 5;

vector <int> pos;
char c[N], ans[N];
int T, n, cnt1, cnt2;

bool check(int mid) {
    for (int i = 1; i <= n; i++) ans[i] = c[i];
    for (int i = 0; i < mid - cnt1; i++) ans[pos[i]] = '(';
    for (int i = (int)pos.size() - 1; i >= (int)pos.size() - (mid - cnt2); i--) ans[pos[i]] = ')';
    int now = 0;
    // cout << mid << " : ";
    // for (int i = 1; i <= n; i++) putchar(ans[i]);
    // putchar('\n');
    for (int i = 1; i <= n; i++) {
        if (ans[i] == '(') ++now;
        if (ans[i] == ')') {
            if (!now) return 0;
            --now;
        }
    }
    return 1;
}

int main() {
    read(T);
    while (T--) {
        cnt1 = cnt2 = 0;
        pos.clear();
        scanf("%s", c + 1); n = strlen(c + 1);
        for (int i = 1; i <= n; i++) {
            if (c[i] == '*') pos.push_back(i);
            if (c[i] == '(') ++cnt1;
            if (c[i] == ')') ++cnt2;
        }
        int tmp = max(cnt1, cnt2);
        int l = tmp, r = n / 2, res = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) res = mid, r = mid - 1;
            else l = mid + 1;
        }
        if (res == -1) {
            puts("No solution!");
            continue;
        }
        check(res);
        for (int i = 1; i <= n; i++) if (ans[i] != '*') putchar(ans[i]);
        putchar('\n');
    }
    return 0;
}