#include<bits/stdc++.h>
using namespace std;
const int N=3e3;
int T,n,mod;
struct z{
    int x;
    z(){}
    z(int v):x(v){}
    void operator-=(const z &rhs){x-=rhs.x;if(x<0)x+=mod;}
    void operator*=(const z &rhs){x=(long long)x*rhs.x%mod;}
    void operator+=(const z &rhs){x+=rhs.x;if(x>=mod)x-=mod;}
    friend z operator-(z a,const z &b){a.x-=b.x; return {a.x<0?a.x+mod:a.x};}
    friend z operator+(z a,const z &b){a.x+=b.x; return {a.x>=mod?a.x-mod:a.x};}
    friend z operator*(const z &a,const z &b){return {(int)((long long)a.x*b.x%mod)};}
}f[N+10][N+10],g[N+10][N+10],g2[N+10][N+10],ss[N+10][N+10],ss2[N+10][N+10],ans;
inline z cho(int x){return {x*(x-1)>>1};}
inline z power(z a,int b){
    int s=1;
    for(;b;b>>=1,a.x=(long long)a.x*a.x%mod)
        if(b&1)s=(long long)s*a.x%mod;
    return {s};
}
int main(){
    cin.sync_with_stdio(0),cin.tie(0);
    cin>>T;
    for(int fr=1;fr<=T;++fr){
        cout<<"Case #"<<fr<<":\n";
        cin>>n>>mod;
        f[1][1]=f[0][0]=1;
        for(int i=2;i<=n;++i){
            for(int j=i;j>=1;--j)f[i][j]=f[i-1][j]*j+f[i-1][j-1];
        }
        for(int i=1;i<=n;++i)g[n][i]=i+1;
        for(int i=1;i<n;++i)g2[n-1][i]=i+1;
        for(int i=1;i<=n;++i)g[n+1][i]=g2[n][i]=1;
        for(int i=n-1;i>=1;--i){
            for(int j=1;j<=i;++j)g[i][j]=g[i+1][j+1]+g[i+1][j]*j;
            if(i!=n-1)for(int j=1;j<=i;++j)g2[i][j]=g2[i+1][j+1]+g2[i+1][j]*j;
        }
        g[1][0]=1;
        for(int i=1;i<=n;++i)for(int j=i-1;j>=1;--j){
            ss[i][j]=ss[i][j+1]+f[i-1][j]*g[i+1][j];
            ss2[i][j]=ss2[i][j+1]+f[i-1][j]*g2[i+1][j];
        }
        for(int i=1;i<=n;++i){
            ans=0;
            for(int j=i;j<=n-1;++j)ans+=(f[j-1][i-1]*g2[j+1][i]+ss2[j][i])*(n-j<<1);
            for(int j=i;j<=n;++j)ans+=(f[j-1][i-1]*g[j+1][i]+ss[j][i]);
            cout<<ans.x<<" \n"[i==n];
        }
        for(int i=1;i<=n;++i)for(int j=1;j<=i;++j)f[i][j]=g[i][j]=ss[i][j]=0;
    }
    return 0;
}