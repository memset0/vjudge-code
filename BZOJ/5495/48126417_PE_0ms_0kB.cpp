#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
char cb[1<<15],*cs=cb,*ct=cb;
#define getc() (cs==ct&&(ct=(cs=cb)+fread(cb,1,1<<15,stdin),cs==ct)?0:*cs++)
template<class T>inline void read(T &res) {
    char ch; while(!isdigit(ch=getchar()));
    for(res=ch-'0';isdigit(ch=getchar());res=res*10+ch-'0');
}
const int MAXN = 500005;
const int MAXM = MAXN*32;
struct node {
    int id; LL val;
    node(){}
    node(int ii, LL vv):id(ii), val(vv){}
    bool operator <(const node &o)const {
        return val < o.val;
    }
};
priority_queue<node> q;
int ch[MAXM][2], sz[MAXM], cnt[MAXM], tot;
 
int n, k, now[MAXN];
LL s[MAXN];
 
inline void insert(LL x) {
    int r = 0;
    for(int i = 31, c; ~i; --i) {
        c = (x & (1ll<<i)) ? 1 : 0;
        if(!ch[r][c]) ch[r][c] = ++tot;
        ++sz[r = ch[r][c]]; 
    }
    ++cnt[r];
}
 
inline LL kth(LL x, int k) {
    int r = 0; LL re = 0;
    for(int i = 31, c; ~i; --i) {
        c = (x & (1ll<<i)) ? 0 : 1;
        if(sz[ch[r][c]] < k) k -= sz[ch[r][c]], r = ch[r][!c];
        else re ^= 1ll<<i, r = ch[r][c];
    }
    return re;
}
 
int main () {
    read(n), read(k), k<<=1;
    insert(0);
    for(int i = 1, x; i <= n; ++i)
        read(x), s[i] = s[i-1] ^ x, insert(s[i]);
    for(int i = 0; i <= n; ++i)
        q.push(node(i, kth(s[i], ++now[i])));
    LL ans = 0;
    while(k--) {
        node u = q.top(); q.pop();
        if(k&1) ans += u.val;
        if(now[u.id] < n) q.push(node(u.id, kth(s[u.id], ++now[u.id])));
    }
    printf("%lld\n", ans);
}