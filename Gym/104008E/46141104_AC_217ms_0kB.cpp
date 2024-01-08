#include<bits/stdc++.h>
using namespace std;
int T,sx,sy,tx,ty,vx,vy,s;
long long ax,ay;
int gcd(int x,int y){
    return y?gcd(y,x%y):x;
}
void exgcd(int x,int y,long long&u,long long&v){
    if(!y)return(void)(u=1,v=0);
    long long tu,tv;
    exgcd(y,x%y,tu,tv);
    u=tv,v=tu-(x/y)*u;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d%d",&sx,&sy,&tx,&ty);
        vx=tx-sx,vy=ty-sy;
        s=gcd(abs(vx),abs(vy));
        exgcd(vy/s,-vx/s,ax,ay);
        printf("%lld %lld\n",sx+ax,sy+ay);
    }
    return 0;
}