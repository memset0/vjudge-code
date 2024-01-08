#include <cstdio>
#include <cctype>

inline char fgc() {
    static char buf[100], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100, stdin), p1 == p2) ? EOF : *p1++;
}

inline int readint() {
    register int res = 0;
    register char c = fgc();
    while(!isdigit(c)) {
        c = fgc();
    }
    while(isdigit(c)) {
        res = (res << 1) + (res << 3) + c - '0';
        c = fgc();
    }
    return res;
}

int n, t, cnt, ans;

int main() {
    n = readint();
    while(--n) {
        t = readint();
        if(ans == t) ++cnt;
        else if(!cnt) { ans = t; cnt = 1; }
        else --cnt;
    }
    printf("%d", ans);
}