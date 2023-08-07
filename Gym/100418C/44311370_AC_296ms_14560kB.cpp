#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int n,M,Q,li,ri,sa[N+10],rk[N+10],ar[N+10],ba[N+10],sz,nw,he[20][N+10],tr;
vector<int>qi[N+10];
long long ss[N+10],prt[N+10],ns;
char S[N+10];
void Getsa(){
    //for(int i=1;i<=n;++i)printf("%d%c",ar[i]," \n"[i==n]);
    for(int i=1;i<=M;++i)ba[i]=0;
    for(int i=1;i<=n;++i)++ba[rk[i]];
    for(int i=2;i<=M;++i)ba[i]+=ba[i-1];
    for(int i=n;i>=1;--i)sa[ba[rk[ar[i]]]--]=ar[i];
}
void SA(){
    //cout<<"SA\n";
    M=27;
    for(int i=1;i<=n;++i)rk[i]=S[i]-'A'+1,ar[i]=i;
    Getsa();
    //for(int j=1;j<=n;++j)printf("%s\n",S+sa[j]);
    //cout<<"----------------------------------\n";
    //cout<<"?\n";
    for(int i=1;i<=n;i<<=1){
        //cout<<"I="<<i<<"\n";
        sz=0;
        for(int j=n-i+1;j<=n;++j)ar[++sz]=j;
        for(int j=1;j<=n;++j)if(sa[j]>i)ar[++sz]=sa[j]-i;
        Getsa();
        for(int j=1;j<=n;++j)ar[j]=rk[j];
        rk[sa[1]]=nw=1;
        for(int j=2;j<=n;++j)rk[sa[j]]=(sa[j]+i<=n&&sa[j-1]+i<=n&&ar[sa[j]]==ar[sa[j-1]]&&ar[sa[j]+i]==ar[sa[j-1]+i]?nw:++nw);
        //for(int j=1;j<=n;++j)printf("%d %s %d\n",sa[j],S+sa[j],rk[sa[j]]);
        //cout<<"----------------------------------\n";
        M=nw;
    }
}
void Getheight(){
    int ls=0;
    for(int i=1;i<=n;++i){
        ls?--ls:0;
        if(rk[i]==1)continue;
        while(i+ls<=n&&sa[rk[i]-1]+ls<=n&&S[i+ls]==S[sa[rk[i]-1]+ls])++ls;
        he[0][rk[i]]=ls;
    }
    return;
}
int main(){
    scanf("%s",S+1),n=strlen(S+1);
    SA(),Getheight();
    //for(int i=1;i<=n;++i)printf("%d %s %d\n",sa[i],S+sa[i],he[0][i]);
    for(int i=1;i<=n;++i)ss[i]=ss[i-1]+n-sa[i]+1/*-he[0][i]*/;
    for(sz=1;(1<<sz)<=n;++sz)for(int j=(1<<sz);j<=n;++j)he[sz][j]=min(he[sz-1][j],he[sz-1][j-(1<<sz-1)]);
    scanf("%d",&Q);
    for(int i=1;i<=Q;++i){
        scanf("%d%d",&li,&ri),ri-=li-1,li=tr=rk[li];
        for(int i=sz;i>=0;--i){
            if(he[i][li]>=ri)li-=(1<<i);
            if(tr+(1<<i)<=n&&he[i][tr+(1<<i)]>=ri)tr+=(1<<i);
        }
        qi[tr+1].push_back(i),prt[i]=ss[li-1]+1ll*(ri-1)*(tr-li+1);
        //cout<<"NW "<<i<<"="<<prt[i]<<"\n";
        //cout<<"LI="<<li<<" TR="<<tr<<"\n";
        //printf("%lld\n",ss[li-1]+ri-1/*-he[0][li]+1*/);
    }
    ar[sz=1]=n+1;
    for(int i=n;i>=1;--i){
        while(he[0][i]<he[0][ar[sz]])ns-=1ll*he[0][ar[sz]]*(ar[sz-1]-ar[sz]),--sz;
        ns+=1ll*he[0][i]*(ar[sz]-i),ar[++sz]=i;
        //cout<<"I="<<i<<" ns="<<ns<<"\n";
        for(int j=0;j<qi[i].size();++j)prt[qi[i][j]]+=ns;
    }
    for(int i=1;i<=Q;++i)printf("%lld\n",prt[i]);
    return 0;
}
/*
AAABBB
7
1 1
2 2
3 3
4 4
5 5
6 6
3 4
*/