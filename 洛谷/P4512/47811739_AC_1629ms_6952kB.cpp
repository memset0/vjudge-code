// luogu-judger-enable-o2
// luogu-judger-enable-o2
// test
#include<bits/stdc++.h>
using namespace std;
const int N=4e6+7,p=998244353;
vector<int>h,s,q;
int k,lim,rev[N];
inline int read()
{
    int num=0; char g=getchar();
    while(g<48||57<g) g=getchar();
    while(47<g&&g<58) num=(num<<1)+(num<<3)+g-48,g=getchar();
    return num;
}
inline int pows(long long u,int v) {long long ans=1; while(v>0) {if(v&1) ans=ans*u%p; v=v>>1,u=u*u%p;} return ans;}
inline void NTT(vector<int>&s,int t)
{
    for(int i=0;i<lim;i++) if(rev[i]<i) swap(s[i],s[rev[i]]);
    for(int mid=1;mid<lim;mid=mid<<1)
    {
        long long w=pows(t,(p-1)/(mid<<1));
        for(int i=0,r=mid<<1;i<lim;i+=r)
        {
            long long wn=1;
            for(int j=0;j<mid;j++,wn=wn*w%p)
            {
                long long a=s[i+j],b=s[i+j+mid]*wn%p; s[i+j]=a+b,s[i+j+mid]=a-b+p;
                if(s[i+j]>=p) s[i+j]-=p; if(s[i+j+mid]>=p) s[i+j+mid]-=p;
            }
        }
    }
    if(p+1==t+t+t) {long long inv=pows(lim,p-2); for(int i=0;i<lim;i++) s[i]=s[i]*inv%p;}
}
inline void getinv(int u,vector<int>&e,vector<int>&g,vector<int>&f)
{
    if(u==1) {e.resize(1),e[0]=pows(f[0],p-2); return;} getinv((u+1)/2,g,e,f);
    lim=1,k=0; while(lim<u+u) lim=lim<<1,k++; h.resize(lim),g.resize(lim),e.resize(lim);
    for(int i=0;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
    for(int i=0;i<(u+1)/2;i++) e[i]=(g[i]<<1); for(int i=(u+1)/2;i<lim;i++) e[i]=0,g[i]=0;
    for(int i=0;i<u;i++) h[i]=f[i]; for(int i=u;i<lim;i++) h[i]=0;
    NTT(g,3),NTT(h,3); for(int i=0;i<lim;i++) h[i]=1ll*h[i]*g[i]%p*g[i]%p; NTT(h,(p+1)/3);
    for(int i=0;i<u;i++) {e[i]=e[i]-h[i]+p; if(e[i]>=p) e[i]-=p;} e.resize(u);
}
inline void getdiv(vector<int>e,vector<int>g,vector<int>&f)
{
    int lena=e.size(),lenb=g.size(),lenc=lena-lenb+1;
    for(int i=0;i<lena/2;i++) swap(e[i],e[lena-i-1]);
    for(int i=0;i<lenb/2;i++) swap(g[i],g[lenb-i-1]);
    f.resize(lenc);
    g.resize(lenc); getinv(lenc,s,q,g);
//	cout<<s[0]<<' '<<s[1]<<' '<<s[2]<<' '<<s[3]<<"sasassa"<<' '<<lenc<<' '<<g[0]<<' '<<g[2]<<' '<<g.size()<<endl;
    lim=1,k=0; while(lim<lena+lena) lim=lim<<1,k++; s.resize(lim),q.resize(lim);
    
    for(int i=0;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
    for(int i=0;i<lenc;i++) q[i]=e[i]; for(int i=lenc;i<lim;i++) s[i]=q[i]=0;
    NTT(s,3),NTT(q,3); for(int i=0;i<lim;i++) s[i]=1ll*s[i]*q[i]%p; NTT(s,(p+1)/3);
    for(int i=0;i<lena/2;i++) swap(e[i],e[lena-i-1]);
    for(int i=0;i<lenb/2;i++) swap(g[i],g[lenb-i-1]);
    for(int i=0;i<lenc/2;i++) swap(s[i],s[lenc-i-1]);
    for(int i=0;i<lenc;i++) printf("%d ",s[i]); puts("");
    for(int i=lenc;i<lim;i++) s[i]=0; for(int i=0;i<lenb;i++) q[i]=g[i]; for(int i=lenb;i<lim;i++) q[i]=0;
    NTT(s,3),NTT(q,3); for(int i=0;i<lim;i++) s[i]=1ll*s[i]*q[i]%p; NTT(s,(p+1)/3);
    f.resize(lenb-1); for(int i=0;i<lenb;i++) {f[i]=e[i]-s[i]+p; if(f[i]>=p) f[i]-=p;}

}
int main()
{
//	freopen("testdata.in","r",stdin);
    vector<int>a,b,c;
    int n=read()+1,m=read()+1,x;
    for(int i=1;i<=n;i++) x=read(),a.push_back(x);
    for(int i=1;i<=m;i++) x=read(),b.push_back(x);
    getdiv(a,b,c); int lent=c.size();
    for(int i=0;i<lent;i++) printf("%d ",c[i]); puts("");
    return 0;
}