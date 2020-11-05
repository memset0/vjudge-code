#include<bits/stdc++.h>
#define ll long long
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=1e5+10,mod=998244353;
struct z {
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}ans(1);
inline z fpow(z a,int b){z s(1);for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
ll c[N];
int n,s,fa[N];
std::vector<ll> vet;
std::vector<z> f,g,sum;
std::vector<std::pair<int,int>> E,G[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
bool dfs(int u,int fa){
	if(u==s)return true;
	for(auto &it:G[u]){
		int v=it.first,k=it.second;
		if(v!=fa&&dfs(v,u)){
			vet.push_back(c[k]),c[k]=-1;
			return true;
		}
	}
	return false;
}
z solve(){
	// printf("--- solve ---\n"); for(int i=0;i<vet.size();i++)printf("%lld%c",vet[i]," \n"[i==vet.size()-1]);
	z ans,mul,dp[2],fr[2];
	for(int h=59;h>=0;h--){
		f.clear(),g.clear(),sum.clear();
		for(int i=0;i<vet.size();i++)if((vet[i]>>h)&1){
			f.push_back((vet[i]&((1ll<<h)-1))%mod);
			sum.push_back(h?(vet[i]&((1ll<<h)-1))%mod+1:1);
		}else{
			g.push_back((vet[i]&((1ll<<h)-1))%mod);
		}
		mul=1,dp[0]=1,dp[1]=0;
		for(int i=0;i<g.size();i++)mul=mul*(g[i]+1);
		// for(int i=0;i<sum.size();i++)printf("%d%c",sum[i]," \n"[i==sum.size()-1]);
		for(int i=(int)sum.size()-2;i>=0;i--)sum[i]=sum[i+1]*sum[i];
		for(int i=0;i<f.size();i++){
			// printf("> %d : %d %d %d : %d %d\n",i,(i+1==f.size()?z(1):sum[i+1]),dp[((int)f.size()-i-1)&1],mul,dp[0],dp[1]);
			ans=ans+(i+1==f.size()?z(1):sum[i+1])*dp[((int)f.size()-i-1)&1]*mul;
			fr[0]=dp[0],fr[1]=dp[1];
			dp[0]=(1ll<<h)%mod*fr[0]+(f[i]+1)*fr[1];
			dp[1]=(1ll<<h)%mod*fr[1]+(f[i]+1)*fr[0];
		}
		// if(ans.x)printf("h=%d ans=%d\n",h,ans.x);
		if(f.size()&1)break;
	}
	ll sum=0;
	for(int i=0;i<vet.size();i++)sum^=vet[i];
	if(sum==0)ans=ans+1;
	// printf(">> %d\n",ans);
	// int cnt=0;
	// for(int i=0;i<=2;i++)for(int j=0;j<=3;j++)for(int k=0;k<=3;k++)for(int l=0;l<=3;l++){
	// 	if((i^j^k^l)==0)printf("%d %d %d %d\n",i,j,k,l),++cnt;
	// }
	// printf(">> %d\n",cnt);
	return (1ll<<60)%mod*ans;
}
signed main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n);
	for(int x,i=1;i<=n;i++)read(x),E.push_back(std::make_pair(x,i));
	for(int i=1;i<=n;i++)read(c[i]),fa[i]=i;
	for(auto it:E){
		int u=it.first,v=it.second;
		if(find(u)==find(v)){
			s=u,vet.clear(),dfs(v,0),vet.push_back(c[v]);
			ans=ans*solve(),c[v]=-1;
		}else{
			fa[find(u)]=find(v);
			G[u].push_back(std::make_pair(v,v));
			G[v].push_back(std::make_pair(u,v));
		}
	}
	for(int i=1;i<=n;i++)if(~c[i])ans=ans*(c[i]%mod+1);
	printf("%d\n",ans.x);
}
// 799667024