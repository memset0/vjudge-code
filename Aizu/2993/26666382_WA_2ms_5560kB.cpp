#include<bits/stdc++.h>
typedef long long i64;
const int N=3e5+10,mod=998244353;
int n,ans,p[N],cnt[N],vis[N];
int length(int u){vis[u]=1;return vis[p[u]]?1:length(p[u])+1;}
inline int fpow(int a,int b){int s=1;for(;b;b>>=1,a=(i64)a*a)if(b&1)s=(i64)s*a;return s;}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&p[i]);
	for(int i=1;i<=n;i++)if(!vis[i])cnt[length(i)]++;
	if(!cnt[1]&&!cnt[2]){puts("0"); return 0;}
	if(!cnt[1])for(int i=1;i<=n;i+=2)if(cnt[i]){puts("0"); return 0;}
	for(int i=1,j,w;i<=n;i++)if(cnt[i]){
		if(i==1)ans=cnt[i]==1?1:fpow(cnt[i],cnt[i]-2);
		else if(i==2&&!cnt[1])ans=(i64)fpow(cnt[i],cnt[i]-1)*fpow(i,cnt[i]-1)%mod;
		else{
			for(w=0,j=1;j*j<=i;j++)if(i%j==0){
				w=(w+(i64)j*cnt[j])%mod;
				if(j*j!=i&&j!=1)w=(w+(i64)(i/j)*cnt[i/j])%mod;
			}
			ans=(i64)ans*w%mod*fpow((w+(i64)i*cnt[i])%mod,cnt[i]-1)%mod;
		}
	}
	printf("%d\n",ans);
}