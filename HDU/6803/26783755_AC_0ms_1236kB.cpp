#include <cstdio>
#include <algorithm>
#define int long long 
// 123123131213
int t,n,A[1001],D[1001],T[1001];
signed main(){
    scanf("%lld",&t);
    for(int fd=1;fd<=t;fd++){
        scanf("%lld",&n);
        int mn=1e18,cnt=0;
        for(int i=1;i<=n;i++)scanf("%lld%lld",A+i,D+i),T[i]=1ll*(((100ll+A[i]-1ll)/A[i])-1)*(D[i]),mn=std::min(mn,T[i]);
//        for(int i=1;i<=n;i++)printf("%lld\n",T[i]);
        for(int i=1;i<=n;i++)if(T[i]==mn)++cnt;
        printf("%lf\n",1.0-(((double)(cnt)/(double)(n))*0.5));
    }
}