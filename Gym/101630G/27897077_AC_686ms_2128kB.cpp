#include <bits/stdc++.h>
#define ll long long
namespace ringo {
template <class T> inline void read(T &x) {
    x = 0; register char c = getchar(); register bool f = 0;
    while (!isdigit(c)) f ^= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (f) x = -x;
}
template <class T> inline void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) print(x / 10);
    putchar('0' + x % 10);
}
template <class T> inline void print(T x, char c) { print(x), putchar(c); }
inline int rand() { return (::rand() << 16) | (::rand() << 1) | (::rand() & 1); }
 
const int N = 3e4 + 10;
int n, m, k, rt, top, nod;
int a[N], b[N], c[N], d[N], siz[N], ch[N][2], rnd[N];
ll ans, base, s_min, s_max, total_a, sa[N], sb[N], sc[N], sd[N], val[N];
 
inline ll sum_a(int l, int r) { return sa[r] - sa[l - 1]; }
inline ll sum_b(int l, int r) { return sb[r] - sb[l - 1]; }
inline ll sum_c(int l, int r) { return sc[r] - sc[l - 1]; }
inline ll sum_d(int l, int r) { return sd[r] - sd[l - 1]; }
 
//namespace Vactor {
//  std::vector <int> vet;
//  void clear() {
//      vet.clear();
//  }
//  void insert(ll v) {
//      vet.push_back(v);
////        printf("insert %lld\n", v);
//  }
//  void erase(ll v) {
//      for (std::vector <int> ::iterator it = vet.begin(); it != vet.end(); it++)
//          if (*it == v) { vet.erase(it); return; }
////        printf("erase %lld\n", v);
//  }
//  void modify(ll v) {
//      for (std::vector <int> ::iterator it = vet.begin(); it != vet.end(); it++)
//          *it += v;
////        printf("modify %lld\n", v);
//  }
//  int query(ll v) {
//      int ans = 0;
//      for (std::vector <int> ::iterator it = vet.begin(); it != vet.end(); it++)
//          ans += *it < v;
////        printf("query %lld => %d\n", v, ans);
//      return ans;
//  }
//} // using namespace Vactor;
 
namespace HyTree {
    inline void clear() { rt = nod = base = 0; }
    inline void update(int u) { siz[u] = siz[ch[u][0]] + siz[ch[u][1]] + 1; }
    inline int new_node(ll v) {
        int u = ++nod;
        val[u] = v, siz[u] = 1, ch[u][0] = ch[u][1] = 0;
        if (!rnd[u]) rnd[u] = rand();
        return u;
    }
    int merge(int x, int y) {
        if (!x || !y) return x | y;
        if (rnd[x] < rnd[y]) { ch[x][1] = merge(ch[x][1], y), update(x); return x; }
        else { ch[y][0] = merge(x, ch[y][0]), update(y); return y; }
    }
    void split(int u, ll k, int &x, int &y) {
        if (!u) { x = y = 0; return; }
        if (k < val[u]) y = u, split(ch[u][0], k, x, ch[y][0]);
        else x = u, split(ch[u][1], k, ch[x][1], y);
        update(u);
    }
    int query(int u, ll v) {
        if (!u) return 0;
//      printf(">> query %d %lld\n", u, v);
        if (v <= val[u]) return query(ch[u][0], v);
        return query(ch[u][1], v) + siz[ch[u][0]] + 1;
    }
    inline void insert(ll v) {
//      Vactor::insert(v);
//      printf("insert %lld [%d] [%lld]\n", v, rt, val[rt]);
        int x, y; v -= base;
        split(rt, v, x, y), rt = merge(x, merge(new_node(v), y));
//      printf("    rt %d : %d\n", rt, val[rt]);
    }
    inline void erase(ll v) {
//      Vactor::erase(v);
//      printf("erase %lld [%d] [%lld]\n", v, rt, val[rt]);
        int x, y, z; v -= base;
        split(rt, v - 1, x, y), split(y, v, y, z);
//      printf("%d %d %d : %lld %lld %lld\n", x, y, z, val[x], val[y], val[z]);
        y = merge(ch[y][0], ch[y][1]);
        rt = merge(x, merge(y, z));
    }
    inline void modify(ll v) {
//      Vactor::modify(v);
        base += v;
//      printf("modify %lld\n", v);
    }
    inline int query(ll v) {
        int ans = query(rt, v - base);
//      printf("query %lld -> %d %d\n", v, ans, Vactor::query(v));
        return ans;
    }
} using namespace HyTree;
 
bool check(ll mid) {
    int cnt = 0; clear();
    for (int i = n - m + 1; i; i--) {
        if (i + m + m - 1 <= n) insert(sum_a(1, i + m - 1) + sum_b(i + m, i + m + m - 1) + sum_a(i + m + m, n));
        cnt += query(mid - sum_b(i, i + m - 1) + sum_a(i, i + m - 1));
    } clear();
    for (int i = 1; i + m - 1 <= n; i++) {
//      printf(">>> %d\n", i);
        if (i == 1) {
            for (int i = 2; i <= m; i++) if (i + m - 1 <= n)
                insert(total_a - sum_a(i, i + m - 1) + sum_b(i, i + m - 1) + sum_d(i, m));
        } else {
            if (i + (m - 1) * 2 <= n)
                insert(total_a - sum_a(i + m - 1, i + (m - 1) * 2) + sum_b(i + m - 1, i + (m - 1) * 2));
            modify(d[i + m - 1]);
            erase(total_a - sum_a(i, i + m - 1) + sum_b(i, i + m - 1) + sum_d(i, i + m - 1));
        }
        cnt += query(mid + sum_a(i, i + m - 1) - sum_b(i, i + m - 1));
    }
//  printf("=> %lld : %d\n", mid, cnt);
    return cnt < k;
}
 
void main() {
    read(n), read(m), read(k), srand(20040725);
    for (int i = 1; i <= n; i++) read(a[i]), sa[i] = sa[i - 1] + a[i];
    for (int i = 1; i <= n; i++) read(b[i]), sb[i] = sb[i - 1] + b[i];
    for (int i = 1; i <= n; i++) read(c[i]), sc[i] = sc[i - 1] + c[i];
    for (int i = 1; i <= n; i++) {
        s_min += std::min(a[i], std::min(b[i], c[i]));
        s_max += std::max(a[i], std::max(b[i], c[i]));
        d[i] = c[i] - (b[i] << 1) + a[i], sd[i] = sd[i - 1] + d[i];
    } total_a = sum_a(1, n);
    for (ll l = s_min, r = s_max, mid; (mid = l + r >> 1), l <= r; )
        if (check(mid)) l = mid + 1, ans = mid;
        else r = mid - 1;
    print(ans, '\n');
}
 
} signed main() { return ringo::main(), 0; }
 
/**************************************************************
    Problem: 5216
    User: w15
    Language: C++
    Result: 正确
    Time:1144 ms
    Memory:3656 kb
****************************************************************/