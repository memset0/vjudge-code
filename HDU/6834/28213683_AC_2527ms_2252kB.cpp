#include <cstdio>
#include <cmath>
#include <algorithm>
#define int long long

long long n,sn,id[700001],top,h[700001],g[700001],prime[700001],cnt;
long long Id(long long x){
    return x<=sn?x:top-n/x+1;
}
int T;
long long k;
long long getfunc(long long a,long long b){
    if(a<prime[b])return 0;
    long long ans=(g[Id(a)]-g[prime[b-1]]),lim=sqrt(a);
    for(int i=b;i<=cnt&&prime[i]<=lim;i++)
        for(long long x=prime[i];x*prime[i]<=a;x*=prime[i])
            (ans+=getfunc(a/x,i+1)*(prime[i]<=k)+(prime[i]<=k));
    return ans;
}
int get(int n){
        ::n=n;
        top=cnt=0;
        sn=sqrt(n);
        for(int i=1;i<=n;i=id[top]+1){
            id[++top]=n/(n/i);
            g[top]=id[top]-1;
        }
        for(int i=2;i<=sn;i++)
            if(g[i]!=g[i-1]){
                prime[++cnt]=i;
                long long sq=(long long)i*i;
                for(int j=top;id[j]>=sq;j--){
                    long long t=Id(id[j]/i);
                    g[j]-=g[t]-(cnt-1);
                }
            }
        return g[top];
}
signed main(){
    scanf("%lld",&T);
    for(int fd=1;fd<=T;fd++){
        scanf("%lld%lld",&n,&k);
        int tem=n;
        int r=get(k);
        n=tem;
        top=cnt=0;
        sn=sqrt(n);
        for(int i=1;i<=n;i=id[top]+1){
            id[++top]=n/(n/i);
            g[top]=id[top]-1;
        }
        for(int i=2;i<=sn;i++)
            if(g[i]!=g[i-1]){
                prime[++cnt]=i;
                long long sq=(long long)i*i;
                for(int j=top;id[j]>=sq;j--){
                    long long t=Id(id[j]/i);
                    g[j]-=g[t]-(cnt-1);
                }
            }
        for(int i=1;i<=top;i++)
            if(id[i]>k){
                g[i]=r;
                for(int j=i+1;j<=top;j++)g[j]=g[i];
                break;
            }
//        for(int i=1;i<=top;i++)printf("%d %d\n",id[i],g[i]);
        printf("%lld\n",getfunc(n,1)+1);
    }
}