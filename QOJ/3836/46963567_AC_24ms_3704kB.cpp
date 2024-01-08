#include "bits/stdc++.h"
using namespace std;
const int N=64;
int T,n,a[N+10][N+10],tt[2],ar[N*N+10],sz;
int main()
{
    cin.sync_with_stdio(0),cin.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)cin>>a[i][j];
        tt[0]=tt[1]=0;
        sz=0;
        for(int i=1;i<=n;++i){
            if(i&1){
                for(int j=1;j<n;++j)++tt[a[i][j]<a[i][j+1]],ar[++sz]=a[i][j];
                if(i<n)++tt[a[i][n]<a[i+1][n]];
                ar[++sz]=a[i][n];
            }else{
                for(int j=n;j>1;--j)++tt[a[i][j]<a[i][j-1]],ar[++sz]=a[i][j];
                if(i<n)++tt[a[i][1]<a[i+1][1]];
                ar[++sz]=a[i][1];
            }
        }
        if(tt[0]>=tt[1])for(int i=1;i<=sz;++i)cout<<ar[i]<<" \n"[i==sz];
        else for(int i=sz;i>=1;--i)cout<<ar[i]<<" \n"[i==1];
    }
    return 0;
}
/*
2
2
4 3
2 1
2
4 3
2 1
*//////