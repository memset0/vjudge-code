#include<cstdio>
#include<bitset>
#include<iostream>
using namespace std;
const int N=1e7/6,maxn=1e7;
bitset<2>a[N+10];
int p[5761455+5],len;
int x;
bool vis[10000000];
int main(){
    vis[2]=vis[3]=1;
    for(int i=6,j=1;j<=N;i+=6,j++){
        if(!a[j][0])p[++len]=i-1;
        x=i-1;
        for(int j=1,t=p[1]*x;j<=len&&t<=maxn;){
            a[(t+1)/6][t%6==1]=1;
            if(x%p[j]==0)break;
            t=p[++j]*x;
        }
        if(!a[j][1])p[++len]=i+1;
        x=i+1;
        for(int j=1,t=p[1]*x;j<=len&&t<=maxn;){
            a[(t+1)/6][t%6==1]=1;
            if(x%p[j]==0)break;
            t=p[++j]*x;
        }
    }
    for(int i=1;i<=len;i++)vis[p[i]]=1;
    std::cerr<<clock()<<std::endl;
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d",&x);
        puts(vis[x]?"YES":"NO");
    }
    return 0;
}