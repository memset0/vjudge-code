#include<bits/stdc++.h>
using namespace std;
const int N=3e5,M=6e5;
int n,m,a[N+10],sum[N+10],fl,nw;
long long ss,tot;
char op[M+10],ans[M+10];
void Ins(int x){
    while(x<=n)++sum[x],x+=(x&-x);
}
int Que(int x){
    int ret=0;
    while(x)ret+=sum[x],x-=(x&-x);
    return ret;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)scanf("%d",&a[i]);
    for(int i=n;i>=1;--i)tot+=Que(a[i]),Ins(a[i]);
    printf("%lld\n",tot);
    scanf("%s",op+1);
    nw=1;
    ss=(1ll*n*(n-1)>>1);
    fl=1;
    for(int i=1;i<=m;++i){
        if(op[i]=='R')fl^=1;
        else{
            if(fl)tot+=n-a[nw]-(a[nw]-1),nw=nw%n+1;
            else nw=(nw-2+n)%n+1,tot+=a[nw]-1-(n-a[nw]);
        }
        ans[i]=(fl?tot:(ss-tot))%10+'0';
    }
    printf("%s",ans+1);
    return 0;
}