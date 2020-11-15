#include<bits/stdc++.h>
using namespace std; 
const int N=5007,p=998244353;
int t,n,k,q,g[N][N],ans[N],fac[N],ifac[N],dp[N][N];
inline int pows(long long u,int v){
    long long ans=1;
    while(v>0){
        if(v&1) ans=ans*u%p; u=u*u%p,v=v>>1; 
    }
    return ans;
}
inline int binom(int a,int b){
    if(a<b) return 0;
    return 1ll*fac[a]*ifac[b]%p*ifac[a-b]%p;
}
int main(){
    cin>>t;
    while(t--){
        memset(ans,0,sizeof(ans));
        cin>>n>>k,fac[0]=fac[1]=ifac[0]=ifac[1]=1;
        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++) dp[i][j]=0,g[i][j]=0;
        g[1][1]=1;
        for(int i=2;i<=n;i++) fac[i]=1ll*fac[i-1]*i%p,ifac[i]=pows(fac[i],p-2);
        if(k>=n){
            for(int i=1;i<=n;i++){
                putchar('1');
                if(i!=n) putchar(' ');
            }
            puts(""); continue;
        }
        int c=n; q=0;
        while(c>k) c-=(k+1),q++;
        for(int i=1;i<q;i++){
            for(int j=1;j<=n;j++){
                g[i][j+1]=(g[i][j+1]+1ll*g[i][j]*((i*k+i-j)))%p;
            }
            for(int j=1;j<=n;j++) g[i+1][j+1]=g[i][j];
        }
        for(int i=1;i<=n;i++) dp[i][q*(k+1)-i]=g[q][i];
        for(int i=1;i<n;i++)
            for(int j=0;j<=n;j++){
                dp[i+1][j]=(dp[i+1][j]+dp[i][j])%p;
                ans[i+1]=(ans[i+1]+1ll*dp[i][j]*binom(n-i-1,j)%p*fac[j])%p;
                if(j>=1) dp[i+1][j-1]=(dp[i+1][j-1]+1ll*dp[i][j]*j)%p;
            }
        long long inv=1; int z=n;
        for(int i=1;i<=q;i++)
            for(int j=1;j<=k+1;j++){
                if(j!=1) inv=inv*z%p; z--;
            }
        inv=pows(inv,p-2); int sum=0;
        for(int i=1;i<=n;i++){
            printf("%d",1ll*ans[i]*inv%p),sum=(sum+ans[i])%p;
            if(i!=n) putchar(' ');
        }
        puts("");
//        cout<<sum*inv%p<<endl; 
    }
}
//4
//5 2
//7 2
//9 2
//11 4