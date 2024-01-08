#include "bits/stdc++.h"

using ll=long long;
const int MAXN = 600011;
const int base=131131,p1=998244353,p2=1e9+7,mod=p1;
struct Hash{
    int x,y;
    friend inline bool operator<(const Hash &a,const Hash &b){
        return a.x==b.x?a.y<b.y:a.x<b.x;
    }
    bool operator== (const Hash& b){return x==b.x&&y==b.y;}
    friend inline Hash operator+(Hash a,const Hash &b) {
        a.x+=b.x; if(a.x>=p1)a.x-=p1;
        a.y+=b.y; if(a.y>=p2)a.y-=p2;
        return a;
    }
    friend inline Hash operator-(Hash a,const Hash &b){
        a.x-=b.x; if(a.x<0)a.x+=p1;
        a.y-=b.y; if(a.y<0)a.y+=p2;
        return a;
    }
    friend inline Hash operator*(const Hash &a,const Hash &b){
        return {
            (int)((long long)a.x*b.x%p1),
            (int)((long long)a.y*b.y%p2),
        };
    }
}pw[MAXN];
struct HashArray{
    int cnt=0;
    Hash h[MAXN];
    void clear(){
        cnt=0;
    }
    void pushc(int c){
        h[cnt+1].x=((long long)h[cnt].x*base+c)%p1;
        h[cnt+1].y=((long long)h[cnt].y*base+c)%p2;
        ++cnt;
    }
    Hash query(int l,int r){
        if(l==1)return h[r];
        return h[r]-h[l-1]*pw[r-l+1];
    }
}f;

char a[MAXN];
Hash seq1[MAXN],seq2[MAXN];
int cnt[MAXN],used[MAXN];
int fac[MAXN],Ifac[MAXN],inv[MAXN];

Hash pre[MAXN],suf[MAXN];
void init(int n)
{
    fac[0]=1;
    for(int i=1;i<=n;++i)fac[i]=ll(fac[i-1])*i%mod;
    inv[1]=1;
    for(int i=2;i<=n;++i)inv[i]=ll(mod-mod/i)*inv[mod%i]%mod;
    Ifac[0]=1;
    for(int i=1;i<=n;++i)Ifac[i]=ll(Ifac[i-1])*inv[i]%mod;
}
int place(Hash* q,int len,Hash val)
{
    return std::lower_bound(q+1,q+len+1,val)-q;
}
int main()
{
    pw[0]={1,1};
    for(int i=1;i<MAXN;i++){
        pw[i]=pw[i-1]*(Hash){base,base};
    }
    int task;
    scanf("%d",&task);
    init(3e5+5);
    for(int T=1;T<=task;++T)
    {
        scanf("%s",a+1);
        int n=strlen(a+1);
        f.clear();
        for(int i=1;i<=n;++i)f.pushc(a[i]);
        int ans=0;
        for(int d=1;d<=n;++d)
        {
            int m=n/d;
            if(n%d==0)
            {
                int d1=0;
                for(int i=1;i<=n;i+=d)
                    seq1[++d1]=f.query(i,i+d-1);
                std::sort(seq1+1,seq1+d1+1);
                d1=std::unique(seq1+1,seq1+d1+1)-seq1-1;
                for(int x=1;x<=d1;++x)cnt[x]=0;
                for(int i=1;i<=n;i+=d)
                    ++cnt[place(seq1,d1,f.query(i,i+d-1))];
                int prod=fac[m];
                for(int x=1;x<=d1;++x)prod=ll(prod)*Ifac[cnt[x]]%mod;
                ans=(ans+prod)%mod;
                continue;
            }
            int r=n%d,d1=0,d2=0,c=0;
            pre[0]=Hash{1,1};
            for(int i=1;i<=n;i+=d)seq1[++d1]=f.query(i,i+d-1),pre[c+1]=pre[c]*seq1[d1],++c;
            suf[0]=Hash{1,1};
            c=0;
            for(int i=n-d+1;i>0;i-=d)seq1[++d1]=f.query(i,i+d-1),suf[c+1]=suf[c]*seq1[d1],++c;
            for(int w=0;w<=m;++w)seq2[++d2]=pre[w]*suf[m-w];
            std::sort(seq1+1,seq1+d1+1),d1=std::unique(seq1+1,seq1+d1+1)-seq1-1;
            std::sort(seq2+1,seq2+d2+1),d2=std::unique(seq2+1,seq2+d2+1)-seq2-1;

            for(int x=1;x<=d1;++x)cnt[x]=0;
            for(int x=1;x<=d2;++x)used[x]=0;
            for(int i=r+1;i<=n;i+=d)++cnt[place(seq1,d1,f.query(i,i+d-1))];
            int prod=fac[m],sum=0;
            for(int x=1;x<=d1;++x)prod=ll(prod)*Ifac[cnt[x]]%mod;
            int s=r+1;
            for(int w=0;w<=m;++w)
            {
                int pos=place(seq2,d2,pre[w]*suf[m-w]);
                if(!used[pos])
                {
                    ans=(ans+prod)%mod;
                    used[pos]=1;
                }
                if(w==m)break;
                int pl=place(seq1,d1,f.query(s-r,s-r+d-1));
                int pr=place(seq1,d1,f.query(s,s+d-1));
                if(pl!=pr)
                {

                    prod=ll(prod)*fac[cnt[pl]]%mod*Ifac[cnt[pl]+1]%mod;
                    prod=ll(prod)*fac[cnt[pr]]%mod*Ifac[cnt[pr]-1]%mod;
                    ++cnt[pl],--cnt[pr];
                }
                s+=d;
            }
            ans=(ans+sum)%mod;
        }
        printf("Case #%d: %d\n",T,ans);
    }
    return 0;
}