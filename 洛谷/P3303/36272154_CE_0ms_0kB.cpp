// luogu-judger-enable-o2
// luogu-judger-enable-o2
#define int long long
#define lli long long
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
#define nxt m%10,m/=10
const int mod=1e9+7;
const int maxn=15e3+5;
map<lli,lli> m; 
lli w[maxn],dp[maxn][12+5],Ans,rnt;
lli n,k,v[12+5],tot,vnt,cnt,etp[maxn];
struct node{
    lli id;
    lli pos;
    bool operator<(const node &a)const{
        return w[id]*w[pos]<w[a.id]*w[a.pos];
    }
};
priority_queue<node> que;
inline lli swdp(lli top,bool sx,bool qdl,lli mtp){
    if(!top) 
        return mtp==etp[vnt];
    int ___=etp[vnt]/mtp;
    if(!sx && !qdl && ~dp[m[___]][top])
        return dp[m[___]][top];
    lli up=(sx?v[top]:9),ans=0;
    for(int i=(!qdl || top==1);i<=up;i++)
        if((!i && qdl) || (i && ___%i==0))
            ans+=swdp(top-1,sx && i==up,qdl && !i,mtp*i+!i);
    if(!sx && !qdl)
        dp[m[___]][top]=ans;
    return ans;
}
inline lli __Init(lli l){
    for(lli i=2;i<=9;i++)
        if(l*i<=n && !m[l*i]){
            etp[++cnt]=l*i;
            m[__Init(l*i)]=++tot;
        }
    return l;
}
inline void solve(int m){
    do{ 
        v[++rnt]=nxt;
    }while(m);
    sort(etp+1,etp+cnt+1);
    memset(dp,-1,sizeof(dp));
    for(vnt=0;vnt<=cnt;vnt++)
        w[vnt]=swdp(rnt,true,true,1);
}
signed main(){
    scanf("%lld %lld",&n,&k);
    __Init(1);
    etp[0]=1;
    solve(n);
    sort(w,w+vnt+1);
    k=min(k,vnt*vnt);
    for(int i=0;i<=vnt;i++)
        que.push((node){ i,vnt });
    for(int i=1;i<=k;i++){
        node u=que.top();
        que.pop();
        Ans=(Ans+w[u.id]*w[u.pos])%mod;
        if(u.pos==1)
            continue;
        que.push((node){ u.id,u.pos-1 });
    }
    printf("%lld\n",Ans);
    return 0;
}