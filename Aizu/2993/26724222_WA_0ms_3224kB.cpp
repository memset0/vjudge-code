#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353;
inline int add(int a,int b){a+=b;return a>mod?a-mod:a;}
inline int sub(int a,int b){a-=b;return a<0?a+mod:a;}
inline int mul(int a,int b){return 1ll*a*b%mod;}
inline int qpow(int a,int b){int ret=1;for(;b;b>>=1,a=mul(a,a))if(b&1)ret=mul(ret,a);return ret;}
/* math */

const int N = 3e5+5;
int p[N],n,cnt[N];
int g[N];
int vis[N];

int main()
{
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	cin >> n;
	for(int i=1;i<=n;i++)scanf("%d",&p[i]);
	for(int i=1;i<=n;i++)if(!vis[i]){
		int j=i,sz=1;vis[i]=1;while(p[j]!=i){
			vis[p[j]]=1;j=p[j],sz++;
		}
		cnt[sz]++;
	}
	for(int i=1;i<=n;i++){
		for(int j=i*2;j<=n;j++){
			g[j] = add(g[j], mul(cnt[i],i));
		}
	}
	int tot=0;
	int ans=1;
	for(int i=1;i<=n;i++)if(cnt[i]>0){
		++tot;
		int w=g[i];
		if(tot==1){
			if(i>2)ans=0;
			else if(i==2){
				ans=mul(ans,qpow(2,cnt[i]-1));
				if(cnt[i]>1)ans=mul(ans, mul(cnt[i], qpow(cnt[i],cnt[i]-2)));
			}else if(i==1){
				if(cnt[i]>1)ans=mul(ans, qpow(cnt[i], cnt[i]-2));
			}
		}else{
			int s=0;
			s=add(g[i], mul(cnt[i], i));
			int w=mul(g[i],qpow(s,cnt[i]+1-2));
			ans=mul(ans,w);
		}
	}
	cout << ans << endl;
}