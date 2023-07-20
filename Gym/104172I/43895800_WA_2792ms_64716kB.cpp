#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;

namespace fox {
template <class T>
constexpr T pow(T x, ll y) {
    T r = 1;
    for (; y > 0; y /= 2, x = x * x)
        if (y % 2 == 1) r = x * r;
    return r;
}
} // namespace fox

struct Scanner {
    FILE* stream;
    Scanner(FILE* s) : stream(s) {}
    char buf[1 << 20], *l = buf, *r = buf;
    bool flush() { l = buf; r = l + fread(buf, 1, 1 << 20, stream); return l == r; }
    void get(char& c) { c = l == r && flush() ? ' ' : *l++; }
    friend Scanner& operator >>(Scanner& in, char& c) { return in.get(c), in; }
    friend Scanner& operator >>(Scanner& in, char* s) {
        for (in.get(s[0]); isspace(s[0]); in.get(s[0]));
        for (int i = 0; !isspace(s[i]) || (s[i] = '\0'); i++) in.get(s[i + 1]);
        return in;
    }
    friend Scanner& operator >>(Scanner& in, std::string& s) {
        char c;
        for (in.get(c); isspace(c); in.get(c));
        for (s = ""; !isspace(c); in.get(c)) s += c;
        return in;
    }
    template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
    friend Scanner& operator >>(Scanner& in, T& x) {
        char c, f = '+';
        for (in.get(c); !isdigit(c); in.get(c))
            if constexpr (std::is_signed_v<T>) f = c;
        for (x = 0; isdigit(c); in.get(c)) x = x * 10 + c - '0';
        if constexpr (std::is_signed_v<T>) x = f == '-' ? -x : x;
        return in;
    }
    template <class T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
    friend Scanner& operator >>(Scanner& in, T& x) {
        std::string s; in >> s; x = std::stod(s);
        return in;
    }
    template <class T, class U>
    friend Scanner& operator >>(Scanner& in, std::pair<T, U>& a) {
        return in >> a.first >> a.second;
    }
    template <class T, size_t S>
    friend Scanner& operator >>(Scanner& in, std::array<T, S>& a) {
        for (int i = 0, n = S; i < n; i++) in >> a[i];
        return in;
    }
    template <class T>
    friend Scanner& operator >>(Scanner& in, std::vector<T>& a) {
        for (int i = 0, n = a.size(); i < n; i++) in >> a[i];
        return in;
    }
};

struct Printer {
    FILE* stream;
    Printer(FILE* s) : stream(s) {}
    char buf[1 << 20], *l = buf, *r = buf + (1 << 20) - 1;
    int format = 0, precision = 15;
    ~Printer() { flush(); }
    void flush() { fwrite(buf, 1, l - buf, stream); l = buf; }
    void put(const char& c) { *l++ = c; if (l == r) flush(); }
    friend Printer& operator <<(Printer& out, const char& c) { return out.put(c), out; }
    friend Printer& operator <<(Printer& out, const char* s) {
        for (int i = 0; s[i] != '\0'; i++) out.put(s[i]);
        return out;
    }
    friend Printer& operator <<(Printer& out, const std::string& s) {
        for (int i = 0, n = s.size(); i < n; i++) out.put(s[i]);
        return out;
    }
    template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
    friend Printer& operator <<(Printer& out, T x) {
        static char s[40];
        static int i = 0;
        if (x == 0) { out.put('0'); return out; }
        if constexpr (std::is_signed_v<T>) x = x < 0 ? out.put('-'), -x : x;
        while (x > 0) s[++i] = x % 10 + '0', x /= 10;
        while (i > 0) out.put(s[i--]);
        return out;
    }
    template <class T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
    friend Printer& operator <<(Printer& out, T x) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(out.precision) << x;
        return out << oss.str();
    }
    template <class T, class U>
    friend Printer& operator <<(Printer& out, const std::pair<T, U>& a) {
        return out << a.first << " \n"[out.format > 1] << a.second;
    }
    template <class T, size_t S>
    friend Printer& operator <<(Printer& out, const std::array<T, S>& a) {
        out << a[0];
        for (int i = 1, n = S; i < n; i++) out << " \n"[out.format > 1] << a[i];
        return out;
    }
    template <class T>
    friend Printer& operator <<(Printer& out, const std::vector<T>& a) {
        if (!a.empty()) out << a[0];
        for (int i = 1, n = a.size(); i < n; i++) out << " \n"[out.format > 0] << a[i];
        return out;
    }
};

Scanner in(stdin);
Printer out(stdout), err(stderr);

namespace souvenirs {
    using namespace std;
    const int N=250005;
    const ll oo=2e18;
    int n,m,dq;
    ll a[N];
    struct data{
        int l,r,id;
    }q[N];
    struct info{
        ll x;
        int i,j;
    };
    info d,tree[N<<2],ans[N];
    vector<info> v[N<<2];
    bool operator <(const info &a, const info &b) {
        return a.x < b.x;
    }
    inline bool cmp(data a,data b){
        return a.r<b.r;
    }
    void build(int l,int r,int nod){
        tree[nod]={oo,0,0}; v[nod].clear();
        if(l==r){v[nod].push_back({a[l],l,l}); return;} int mid=(l+r)>>1;
        build(l,mid,nod<<1); build(mid+1,r,nod<<1|1);
        v[nod].resize(r-l+1);
        merge(v[nod<<1].begin(),v[nod<<1].end(),v[nod<<1|1].begin(),v[nod<<1|1].end(),v[nod].begin());
    }
    inline info ask(int l,int r,int i,int j,int nod){
        if (l==i&&j==r) return tree[nod];
        int mid=(l+r)>>1;
        if (j<=mid) return ask(l,mid,i,j,nod<<1);
        else if(i>mid) return ask(mid+1,r,i,j,nod<<1|1);
        return min(ask(l,mid,i,mid,nod<<1),ask(mid+1,r,mid+1,j,nod<<1|1));
    }
    inline void insert(int l,int r,int pos,int nod){
        if(l>=pos)return;
        if(l==r){
            d=min(d,tree[nod]=min(tree[nod],(info){abs(a[l]-a[pos]),l,pos})); return;
        }
        int t=lower_bound(v[nod].begin(),v[nod].end(),(info){a[pos],pos,pos})-v[nod].begin();
        info ans={oo,0,0};
        if(t<v[nod].size())ans=min((info){v[nod][t].x-a[pos],v[nod][t].i,pos},ans);
        if(t)ans=min((info){a[pos]-v[nod][t-1].x,pos,v[nod][t-1].i},ans);
        if(!(ans<d)){d=ask(l,r,l,min(pos,r),nod); return;} int mid=(l+r)>>1;
        insert(mid+1,r,pos,nod<<1|1); insert(l,mid,pos,nod<<1); 
        tree[nod]=min(tree[nod<<1],tree[nod<<1|1]);
    }
    void main(){
        build(1,n,1);
        sort(&q[1],&q[m+1],cmp);
        dq=0;
        for(int i=1;i<=m;i++){
            while(dq<q[i].r)d={oo,0,0},insert(1,n,++dq,1);
            ans[q[i].id]=ask(1,n,q[i].l,q[i].r,1);
        }
    }
};

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

const int N = 250005;

int n, q, ax[N], ay[N], ql[N], qr[N];
ll b[N], ans[N];

void solve(ll vx, ll vy) {
    souvenirs::n = n;
    for (int i = 1; i <= n; i++) {
        b[i] = vx * ax[i] + vy * ay[i];
        souvenirs::a[i] = b[i];
    }
    souvenirs::m = q;
    for (int i = 1; i <= q; i++) {
        souvenirs::q[i] = {ql[i], qr[i], i};
    }
    souvenirs::main();
    for (int i = 1; i <= q; i++) {
        int u = souvenirs::ans[i].i, v = souvenirs::ans[i].j;
        ans[i] = std::min(ans[i], 1ll * (ax[u] - ax[v]) * (ax[u] - ax[v]) + 1ll * (ay[u] - ay[v]) * (ay[u] - ay[v]));
    }
}

void run() {
    in >> n >> q;
    for (int i = 1; i <= n; i++) {
        in >> ax[i] >> ay[i];
    }
    for (int i = 1; i <= q; i++) {
        in >> ql[i] >> qr[i]; ans[i] = 1e18;
    }
    int T = 30;
    for (int t = 0; t < T; t++) {
        solve(rng() % 1073741824 - 536870912, rng() % 1073741824 - 536870912);
    }
    for (int i = 1; i <= q; i++) {
        out << ans[i] << "\n";
    }
}

int main() {
#ifdef SULFOX
    freopen("#.in", "r", stdin);
    freopen("#.out", "w", stdout);
#endif
    int t = 1;
    // in >> t;
    for (int i = 0; i < t; i++) { run(); }
    return 0;
}