// luogu-judger-enable-o2
// test

#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7,p=998244353;
int n,tp,f[N],e[N],t[N],q[N],dep[N]; char s[N]; long long ans,len[N],opt[N];
vector<int>v[N];
inline int read(){
    int num=0; char g=getchar(); while(g<48||57<g) g=getchar();
    while(47<g&&g<58) num=(num<<1)+(num<<3)+g-48,g=getchar(); return num;
}
inline int find(int u){
    if(f[u]==u) return u; return f[u]=find(f[u]);
}
inline void search(int u){
    int lent=v[u].size(); t[dep[u]]=u,len[dep[u]]=(len[dep[u]-1]+e[u])%p; long long sum=0;
    if(dep[u]==1){
        sum=e[u]*(e[u]-1)/2;
    }
    else if(dep[u]){
        tp=q[dep[u]-1]; int ret=0; q[dep[u]]=0;
        while(tp>=0){
            if(s[t[tp+1]]==s[u]){
                if(ret<e[t[tp+1]]){
                    int gt=min(e[t[tp+1]],e[u]);
                    sum=(sum+(gt-ret)*len[tp]+1ll*(ret+1+gt)*(gt-ret)/2)%p;
                    if(e[t[tp+1]]==e[u]){
                        q[dep[u]]=tp+1; break;
                    }
                    ret=gt;
                }
                if(!tp){
                        sum=(sum+1ll*(e[u]-ret)*len[1])%p,ret=e[u];
                        if(e[t[1]]<=e[u])q[dep[u]]=1; 
                    }
            }
            if(!tp) break;
            tp=q[tp];
        }
    }
    long long tt=ans;
    ans=(ans+sum)%p,opt[u]=ans;
    for(int i=0;i<lent;i++) dep[v[u][i]]=dep[u]+1,search(v[u][i]);
    ans=(ans-sum+p)%p;
}
signed main(){
//	freopen("jojo.in","r",stdin),freopen("jojo.out","w",stdout); 
    n=read(); for(int i=1;i<=n;i++) f[i]=i; int op,u;
    for(int i=1;i<=n;i++){
        op=read();
        if(op==1){
            e[i]=read(),s[i]=getchar(); while(s[i]<'a'||'z'<s[i]) s[i]=getchar(); v[tp].push_back(i),tp=i;
        }
        else{
            u=read(),f[i]=find(u),tp=f[i];
        }
    }
    search(0);
    for(int i=1;i<=n;i++) f[i]=find(f[i]),printf("%lld\n",opt[f[i]]);
    return 0;
} 