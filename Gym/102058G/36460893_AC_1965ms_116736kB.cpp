#include <bits/stdc++.h>
#define ll long long
#define INF 1000000005
#define MOD 1000000007
#define EPS 1e-10
#define rep(i,n) for(int i=0;i<(int)(n);++i)
#define rrep(i,n) for(int i=(int)(n)-1;i>=0;--i)
#define srep(i,s,t) for(int i=(int)(s);i<(int)(t);++i)
#define each(a,b) for(const auto& (a): (b))
#define all(v) (v).begin(),(v).end()
#define len(v) (int)(v).size()
#define zip(v) sort(all(v)),v.erase(unique(all(v)),v.end())
#define cmx(x,y) x=max(x,y)
#define cmn(x,y) x=min(x,y)
#define fi first
#define se second
#define pb push_back
#define show(x) cout<<#x<<" = "<<(x)<<endl
#define sar(a,n) {cout<<#a<<":";rep(pachico,n)cout<<" "<<a[pachico];cout<<endl;}

using namespace std;

template<typename S,typename T>auto&operator<<(ostream&o,pair<S,T>p){return o<<"{"<<p.fi<<","<<p.se<<"}";}
template<typename T>auto&operator<<(ostream&o,set<T>s){for(auto&e:s)o<<e<<" ";return o;}
template<typename S,typename T,typename U>
auto&operator<<(ostream&o,priority_queue<S,T,U>q){while(!q.empty())o<<q.top()<<" ",q.pop();return o;}
template<typename K,typename T>auto&operator<<(ostream&o,map<K,T>&m){for(auto&e:m)o<<e<<" ";return o;}
template<typename T>auto&operator<<(ostream&o,vector<T>v){for(auto&e:v)o<<e<<" ";return o;}
void ashow(){cout<<endl;}template<typename T,typename...A>void ashow(T t,A...a){cout<<t<<" ";ashow(a...);}
template<typename S,typename T,typename U>
struct TRI{S fi;T se;U th;TRI(){}TRI(S f,T s,U t):fi(f),se(s),th(t){}
bool operator<(const TRI&_)const{return(fi==_.fi)?((se==_.se)?(th<_.th):(se<_.se)):(fi<_.fi);}};
template<typename S,typename T,typename U>
auto&operator<<(ostream&o,TRI<S,T,U>&t){return o<<"{"<<t.fi<<","<<t.se<<","<<t.th<<"}";}

typedef pair<int, int> P;
typedef pair<ll,ll> pll;
typedef TRI<int, int, int> tri;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<double> vd;
typedef vector<P> vp;
typedef vector<string> vs;

const int MAX_N = 300005;

template<typename T> class segtree {
private:
    int n,sz;
    vector<pair<T, int> > node;
public:
    segtree(const vector<T>& v) : n(1), sz((int)v.size()){
        while(n < sz) n *= 2;
        node.resize(2*n, make_pair(numeric_limits<T>::max(), sz));
        for(int i = 0; i < sz; i++){
            node[i+n] = make_pair(v[i], i);
        }
        for(int i=n-1; i>=1; i--){
            node[i] = min(node[2*i], node[2*i+1]);
        }
    }
    void update(int k, T a)
    {
        node[k+n] = make_pair(a, k);
        k += n;
        while(k>>=1){
            node[k] = min(node[2*k], node[2*k+1]);
        }
    }
    pair<T, int> query(int a,int b,int k=0,int l=0,int r=-1)
    {
        pair<T, int> res1 = make_pair(numeric_limits<T>::max(), sz);
        pair<T, int> res2 = make_pair(numeric_limits<T>::max(), sz);
        a += n, b += n;
        while(a != b){
            if(a % 2) res1 = min(res1, node[a++]);
            if(b % 2) res2 = min(res2, node[--b]);
            a >>= 1, b>>= 1;
        }
        return min(res1, res2);
    }
    void print()
    {
        for(int i = 0; i < sz; i++){
            pair<T, int> p;
            p = query(i,i+1);
            cout << "st[" << i << "]: " << p.first << " " << p.second << endl;
        }
    }
};

map<int, vector<tri> > mp;
// (長さ, 個数)
P ot[MAX_N], mem[MAX_N];
int id;

void dfs(int l, int r, segtree<int>& sg){
    if(l >= r) return;
    const auto res = sg.query(l, r);
    int u = res.se - l + 1, v = r - res.se;
    if(u > v) swap(u, v);
    ot[id] = {u, v};
    mp[res.fi].emplace_back(u, v, id++);
    dfs(l, res.se, sg);
    dfs(res.se + 1, r, sg);
}

ll solve(ll mid){
    ll cnt = 0;
    for(const auto& e : mp){
        for(const auto& f : e.se){
            const ll hoge = mid / e.fi;
            if(hoge == 0) continue;
            if(hoge <= f.fi){
                cnt += hoge * (hoge + 1) / 2;
            }else if(hoge <= f.se){
                cnt += (ll)f.fi * (f.fi + 1) / 2;
                cnt += (ll)f.fi * (hoge - f.fi);
            }else{
                cnt += (ll)f.fi * (f.fi + 1) / 2;
                cnt += (ll)f.fi * (f.se - f.fi);
                const ll bue = min(hoge, (ll)f.fi + f.se - 1);
                cnt += (ll)(2 * f.fi + f.se - bue - 1) * (bue - f.se) / 2;
            }
        }
    }
    return cnt;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vi h(n);
    rep(i,n){
        cin >> h[i];
    }
    segtree<int> sg(h);
    dfs(0, n, sg);
    ll L, R;
    cin >> L >> R;
    --L;
    ll l = 0, r = 300000000000000LL;
    ll num = (ll)n * (n + 1) / 2;
    while(r - l > 1){
        ll mid = (l + r) / 2;
        const ll res = solve(mid);
        if(res <= L) l = mid;
        else r = mid, num = res;
    }
    if(R <= num){
        rep(i, R - L) cout << r << " ";
        cout << "\n";
        return 0;
    }
    // r からスタート(R - num 個)
    rep(i,num-L) cout << r << " ";
    priority_queue<pll, vector<pll>, greater<pll> > que;
    for(const auto& e : mp){
        for(const auto& f : e.se){
            const ll hoge = r / e.fi + 1;
            if(hoge > f.fi + f.se - 1) continue;
            que.emplace(e.fi * hoge, f.th);
            mem[f.th] = {hoge, 1};
        }
    }
    // for(const auto& e : mp){
    //     show(e.fi);
    //     for(const auto& f : e.se){
    //         cout << f.fi << " " << f.se << "\n";
    //     }
    // }
    rep(i,R-num){
        assert(!que.empty());
        auto res = que.top();
        que.pop();
        cout << res.fi << " ";
        const auto e = mem[res.se];
        const auto f = ot[res.se];
        const ll piyo = res.fi / e.fi;
        if(e.fi <= f.fi){
            if(e.se < e.fi) que.emplace(piyo * e.fi, res.se), mem[res.se] = {e.fi, e.se + 1};
            else if(e.fi + 1 <= f.fi + f.se - 1) que.emplace(piyo * (e.fi + 1), res.se), mem[res.se] = {e.fi + 1, 1};
        }else if(e.fi <= f.se){
            if(e.se < f.fi) que.emplace(piyo * e.fi, res.se), mem[res.se] = {e.fi, e.se + 1};
            else if(e.fi + 1 <= f.fi + f.se - 1) que.emplace(piyo * (e.fi + 1), res.se), mem[res.se] = {e.fi + 1, 1};
        }else{
            if(e.se < f.fi + f.se - e.fi) que.emplace(piyo * e.fi, res.se), mem[res.se] = {e.fi, e.se + 1};
            else if(e.fi + 1 <= f.fi + f.se - 1) que.emplace(piyo * (e.fi + 1), res.se), mem[res.se] = {e.fi + 1, 1};
        }
    }
    cout << "\n";
    return 0;
}