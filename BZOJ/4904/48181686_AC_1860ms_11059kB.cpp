// ?

#include<bits/stdc++.h>

using namespace std;

#define ll  long long
#define ld  double

#define sz(x)   (int)x.size()
#define all(x)  x.begin(),x.end()

#define pb  emplace_back
#define X   first
#define Y   second

const int   N   = 2e5 + 5;

typedef pair<int,int>   ii;

int t[N];
int a[N];
int Siz;

int upd(int p,int v)    {
    for(; p < N ; p += p & -p)
        t[p] += v;
    
    return  1;
}
int get(int p)  {
    int ans = 0;
    for(; p > 0 ; p -= p & -p)
        ans += t[p];
    
    return  ans;
}
struct Table    {
    bool sign;
    vector<int> vec[300];

    void add(int x) {
        for(int i = 1 ; i <= Siz ; ++i) {
            int r;

            if (sign)   r = lower_bound(all(vec[i]),x) - vec[i].begin();
            else        r = upper_bound(all(vec[i]),x) - vec[i].begin();

            if (vec[i].size() == r) {
                vec[i].pb(x);
                if (sign)   {
                    if (r >= Siz)
                        upd(r + 1,1);
                }
                else    upd(i,1);

                break;
            }
            swap(x,vec[i][r]);
        }
    }
}   T1, T2;
int ans[N];

vector<ii>  Q[N];

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;  cin >> n;   Siz = sqrt(n);
    int q;  cin >> q;

    for(int i = 1 ; i <= n ; ++i)   cin >> a[i];
    for(int i = 1 ; i <= q ; ++i)   {
        int m;  cin >> m;
        int k;  cin >> k;

        Q[m].pb(k,i);
    }
    T1.sign = 0;
    T2.sign = 1;

    for(int i = 1 ; i <= n ; ++i)   {
        T1.add(-a[i]);
        T2.add( a[i]);

        for(ii  T : Q[i])
            ans[T.Y] = get(T.X);
    }
    for(int i = 1 ; i <= q ; ++i)
        cout << ans[i] << "\n";
}