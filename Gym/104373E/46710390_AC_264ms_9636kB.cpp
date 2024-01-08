#include<bits/stdc++.h>
#ifndef memset0
    #define endl '\n'
#endif
using namespace std;
const int N=1e5+9,S=300,p1=998244353,p2=1004535809;
int n,m,p[N];
bool vis[N];
long long pre[S+5][S+5];
vector<vector<long long>> big;
template<const int p> constexpr int power(int a,int b){
    int s=1;
    for(;b;b>>=1,a=(long long)a*a%p)
        if(b&1)s=(long long)s*a%p;
    return s;
}
const int ip1=power<p2>(p1%p2,p2-2);
const int ip2=power<p1>(p2%p1,p1-2);
vector<int> rev,w1,w2;
template<const int p> int sub(int a,int b){a-=b; return a<0?a+p:a;}
template<const int p> int add(int a,int b){a+=b; return a>=p?a-p:a;}
template<const int p> void ntt(vector<int> &f,int n,const vector<int> &w){
    f.resize(n);
    for(int i=0;i<n;i++)if(i<rev[i])swap(f[i],f[rev[i]]);
    for(int len=1;len<n;len<<=1)
        for(int i=0;i<n;i+=len<<1)
            for(int j=0;j<len;j++){
                int x=f[i+j],y=(long long)f[i+j+len]*w[j+len]%p;
                f[i+j]=add<p>(x,y),f[i+j+len]=sub<p>(x,y);
            }
}
template<const int p> void init(int n,vector<int> &w){
    int m=__lg(n);
    rev.resize(n);
    for(int i=1;i<n;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(m-1));
    w.resize(n);
    for(int len=1;len<n;len<<=1){
        int uni=power<p>(3,(p-1)/(len<<1));
        w[len]=1;
        for(int i=1;i<len;i++)w[i+len]=(long long)w[i+len-1]*uni%p;
    }
}
template<const int p> vector<int> polymul(vector<int> a,vector<int> b,vector<int> &w){
    int n=1,m=(int)(a.size()+b.size()-1);
    while(n<m)n<<=1;
    int invn=power<p>(n,p-2);
    init<p>(n,w),ntt<p>(a,n,w),ntt<p>(b,n,w);
    for(int i=0;i<n;i++)a[i]=(long long)a[i]*b[i]%p;
    reverse(a.begin()+1,a.end()),ntt<p>(a,n,w),a.resize(m);
    for(int i=0;i<m;i++)a[i]=(long long)a[i]*invn%p;
    return a;
}
void solve(vector<int> a){
    int n=a.size();
    vector<int> b=a;
    reverse(b.begin(),b.end());
    vector<int> f=polymul<p1>(a,b,w1);
    vector<int> g=polymul<p2>(a,b,w2);
    vector<long long> c(n);
    for(int i=0;i<f.size();i++){
        long long x=((__int128)p2*ip2*f[i]+(__int128)p1*ip1*g[i])%((long long)p1*p2);
        int t=i>=n?i-n:i;
        c[n-t-1]+=x;
    }
    // cerr<<"a: ";for(auto x:a)cerr<<x<<' ';cerr<<endl;
    // cerr<<"c: ";for(auto x:c)cerr<<x<<' ';cerr<<endl;
    // cerr<<"f: ";for(auto x:f)cerr<<x<<' ';cerr<<endl;
    // cerr<<"g: ";for(auto x:g)cerr<<x<<' ';cerr<<endl;
    if(n<S){
        for(int i=0;i<n;i++)pre[n][i]+=c[i];
    }else{
        big.push_back(c);
    }
}
int main(){
#ifdef memset0
    freopen("E.in","r",stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    for(int i=1;i<=n;i++)
        if(!vis[i]){
            int u=i;
            vis[u]=true;
            vector<int> a={u};
            while(!vis[p[u]]){
                u=p[u];
                vis[u]=true;
                a.push_back(u);
            }
            solve(a);
        }
    for(int k,i=1;i<=m;i++){
        cin>>k;
        long long ans=0;
        for(int i=2;i<S;i++)ans+=pre[i][k%i];
        for(const vector<long long> &v:big)ans+=v[k%v.size()];
        cout<<ans<<endl;
    }
}