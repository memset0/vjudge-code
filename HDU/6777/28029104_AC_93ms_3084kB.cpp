#include<bits/stdc++.h>
template<class T> inline void read(T &x){
    x=0; register char c=getchar(); register bool f=0;
    while(!isdigit(c))f^=c=='-',c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=2e4+10;
int T,n,a[N],mrk[N];
std::vector<int> vet[105][15];
int main(){
#ifdef memset0
    freopen("1.in","r",stdin);
#endif
    read(T);
    while(T--){
        read(n);
        for(int i=1;i<=100;i++)
            for(int j=1;j<=10;j++)
                vet[i][j].clear();
        for(int m,i=1;i<=n;i++){
            read(m);
            for(int t,p,j=1;j<=m;j++){
                read(t),read(p);
                vet[t][p].push_back(i);
            }
        }
        for(int i=1;i<=n;i++)mrk[i]=0;
        mrk[1]=1;
        for(int i=1;i<=100;i++){
            for(int j=1;j<=10;j++){
                bool fl=false;
                for(int x:vet[i][j])fl|=mrk[x];
                for(int x:vet[i][j])mrk[x]|=fl;
            }
        }
        std::vector<int> ans;
        for(int i=1;i<=n;i++)if(mrk[i])ans.push_back(i);
        for(int i=0;i<ans.size();i++)print(ans[i]," \n"[i+1==ans.size()]);
    }
}