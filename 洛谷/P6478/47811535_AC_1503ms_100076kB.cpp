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

const int N=5e3+10,mod=998244353;
int n,a[N],fa[N],cnt[N],siz[N];
char s[N];
std::vector<int> G[N];

struct z {
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}f[N][N],tmp[N],fac[N],ifac[N],ans[N];

void dfs(int u){
	siz[u]=1;
	f[u][0]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v!=fa[u]){
			fa[v]=u,dfs(v),siz[u]+=siz[v];
			for(int i=0;i<=cnt[u]+cnt[v];i++)tmp[i]=0;
			for(int i=0;i<=cnt[v];i++)
				for(int j=0;j<=cnt[u];j++)
					tmp[i+j]=tmp[i+j]+f[v][i]*f[u][j];
			for(int i=0;i<=cnt[u]+cnt[v];i++)f[u][i]=tmp[i];
			cnt[u]+=cnt[v];
		}
	}
	cnt[u]+=a[u];
	for(int i=0;i<=cnt[u];i++)tmp[i]=0;
	for(int i=0;i<cnt[u];i++)tmp[i+1]=f[u][i]*((a[u]?siz[u]-cnt[u]:cnt[u])-i);
	for(int i=0;i<=cnt[u];i++)f[u][i]=f[u][i]+tmp[i];
	// printf("f[%d] => ",u);
	// for(int i=0;i<=cnt[u];i++)printf("%d%c",f[u][i].x," \n"[i==cnt[u]]);
}

int main(){
	read(n),scanf("%s",s+1);
	for(int i=1;i<=n;i++)a[i]=s[i]=='1';
	for(int u,v,i=1;i<n;i++)read(u),read(v),G[u].push_back(v),G[v].push_back(u);
	dfs(1);
	fac[0]=fac[1]=ifac[0]=ifac[1]=1;
	for(int i=2;i<=n;i++)fac[i]=fac[i-1]*i;
	for(int i=2;i<=n;i++)ifac[i]=(mod-mod/i)*ifac[mod%i];
	for(int i=2;i<=n;i++)ifac[i]=ifac[i-1]*ifac[i];
	for(int i=0;i<=cnt[1];i++)f[1][i]=f[1][i]*fac[cnt[1]-i];
	for(int i=0;i<=cnt[1];i++)
		for(int j=0;j<=i;j++)
			ans[j]=ans[j]+f[1][i]*fac[i]*ifac[j]*ifac[i-j]*((i+j)&1?mod-1:1);
	for(int i=0;i<=cnt[1];i++)printf("%d\n",ans[i].x);
}