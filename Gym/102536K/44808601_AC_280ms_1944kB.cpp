#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int n,p[N+10];
long long w[N+10],h[N+10];
bool cmp(int x,int y){
    return h[x]<h[y];
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%lld",&w[i]);
    for(int i=1;i<=n;++i)scanf("%lld",&h[i]);
    for(int i=1;i<=n;++i)p[i]=i;
    sort(p+1,p+n+1,cmp);
    for(int i=1;i<=n;++i)printf("%lld%c",w[p[i]]," \n"[i==n]);
    return 0;
}