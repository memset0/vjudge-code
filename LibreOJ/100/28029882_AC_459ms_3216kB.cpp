#include<bits/stdc++.h>
template<class T> inline void read(T &x){
    x=0;register char c=getchar();register bool f=0;
    while(!isdigit(c))f^=c=='-',c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=510,mod=1e9+7;
int n,m,l,a[N][N],b[N][N],c[N][N];
int main(){
    read(n),read(m),read(l);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)read(a[i][j]),a[i][j]=(a[i][j]+mod)%mod;
    for(int i=1;i<=m;i++)for(int j=1;j<=l;j++)read(b[i][j]),b[i][j]=(b[i][j]+mod)%mod;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)for(int k=1;k<=l;k++)
        c[i][k]=(c[i][k]+(long long)a[i][j]*b[j][k])%mod;
    for(int i=1;i<=n;i++)for(int j=1;j<=l;j++)printf("%d%c",c[i][j]," \n"[j==l]);
}