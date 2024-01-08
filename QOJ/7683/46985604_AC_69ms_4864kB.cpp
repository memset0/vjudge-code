#include<bits/stdc++.h>
using namespace std;
const int N=1e6;
int T,n,nw;
char s[N+10];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%s",s+1),n=strlen(s+1);
        nw=0;
        for(int i=1;i<=n;++i)s[i]=='('?++nw:nw=max(0,nw-1);
        if(nw)puts("impossible");
        else printf("%s\n",s+1);
    }
    return 0;
}