#include<bits/stdc++.h>
const int N=2010;
int T,n,a[N],b[N],i,j,ans;
long long f[N][N],s[N];
int main(){
    for(scanf("%d",&T);T--;){
        scanf("%d",&n);
        for(i=1;i<=n;++i)scanf("%d",a+i);
        for(i=1;i<=n;++i)scanf("%d",b+i),s[i]=s[i-1]+b[i];
        ans=0;
        for(i=0;i<N;++i)for(j=1;j<N;++j)f[i][j]=1ll<<60;
        for(i=1;i<=n;++i)for(j=1;j<=i;++j){
            f[i][j]=f[i-1][j];
            if(f[i-1][j-1]+a[i]<=s[i])f[i][j]=std::min(f[i][j],f[i-1][j-1]+a[i]);
            if(f[i][j]<1ll<<60)ans=std::max(ans,j);
        }
        printf("%d\n",ans);
    }
}