#include<bits/stdc++.h>
#include <math.h>
using namespace std;
const int N=2e5,mod=998244353,B=17;
int T,n,a[N+10],b[30],p2[N+10],ans,p,tmp,tp,tpp;
int b2[N+10],pp;
int ap[N+10];
int ins(int x){
    for(int i=B;i>=0;--i)if((x>>i)&1){
        if(!b[i])return(b[i]=x,0);
        x^=b[i];
    }
    int ret=p;
    (p<<=1)>=mod?p-=mod:0;
    return ret;
}
int ins2(int x){
    for(int i=B;i>=0;--i)if((x>>i)&1){
        if(!b2[i])return(b2[i]=x,0);
        x^=b2[i];
    }
    int ret=pp;
    (pp<<=1)>=mod?pp-=mod:0;
    return ret;
}
void Ins(int x,int m){
    //cout<<"INS "<<x<<" "<<m<<"\n";
    if(!m)return;
    ins(x);
    p=1ll*p*p2[m-1]%mod;
}
void Ins2(int x,int m){
    if(!m)return;
    ins(x);
    pp=1ll*pp*p2[m-1]%mod;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n),p2[0]=1;
        for(int i=1;i<=n;++i)(p2[i]=(p2[i-1]<<1))>=mod?p2[i]-=mod:0;
        for(int i=1;i<=n;++i)ap[i]=0;
        for(int i=1;i<=n;++i)scanf("%d",&a[i]),++ap[a[i]];
        for(int i=0;i<=B;++i)b[i]=0;
        sort(a+1,a+n+1);
        ans=0;
        pp=1;
        for(int i=0;i<=B;++i)b2[i]=0;
        for(int i=1,t;i<=n;i=t+1){
            t=i;
            //cout<<"A="<<a[i]<<"\n";
            while(a[t+1]==a[i])++t;
            for(int j=0;j<=B;++j)b[j]=0;
            p=1;
            if(a[i]>1)Ins(1,ap[1]);
            for(int j=2;j*j<=a[i];++j)if(a[i]%j==0){
                Ins(j,ap[j]);
                if(a[i]/j!=j)Ins(a[i]/j,ap[a[i]/j]);
            }
            //cout<<"p="<<p<<" pp="<<pp<<"\n";
            tp=p,tpp=pp;
            ans=(ans+1ll*(tpp+ins(a[i]))*(p2[ap[a[i]]-1]-1)+1ll*(tp+ins2(a[i]))*p2[ap[a[i]]-1])%mod;
            Ins2(a[i],ap[a[i]]);
            //cout<<"ANS="<<ans<<"\n";
        }
        printf("%d\n",ans);
    }
    return 0;
}
/*
2
3
1 2 3
5
3 3 5 1 1

*/