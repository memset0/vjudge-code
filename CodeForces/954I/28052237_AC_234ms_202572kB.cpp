#include<bits/stdc++.h>
#define ll long long
#define REP(i,l,r) for(int i=l,i##ed=r;i<=i##ed;i++)
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
const int N=2e5+10,p1=998244353,p2=1e9+7,pm=131131;
char s[N],t[N];
bool p[N],tag[1<<6];
int n,m,ans,fa[6],w1[N],w2[N];
inline int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
struct hash_lib{
	int f[N],g[N];
	std::pair<int,int> all;
	void build(bool *a,int n){
		for(int i=1;i<=n;i++)f[i]=((ll)pm*f[i-1]+a[i])%p1,g[i]=((ll)pm*g[i-1]+a[i])%p2;
		all=std::make_pair(f[n],g[n]);
	}
	std::pair<int,int> query(int l,int r){
		std::pair<int,int> res;
		res.first=(f[r]-(ll)w1[r-l+1]*f[l-1])%p1;if(res.first<0)res.first+=p1;
		res.second=(g[r]-(ll)w2[r-l+1]*g[l-1])%p2;if(res.second<0)res.second+=p2;
		return res;
	}
}S[1<<6],T[1<<6];
int main(){
	scanf("%s%s",s+1,t+1),n=strlen(s+1),m=strlen(t+1);
	for(int i=1;i<=n;i++)s[i]-='a';
	for(int i=1;i<=m;i++)t[i]-='a';
	w1[0]=w2[0]=1;
	for(int i=1;i<=n;i++)w1[i]=(ll)pm*w1[i-1]%p1,w2[i]=(ll)pm*w2[i-1]%p2;
	for(int x=0;x<(1<<6);x++){
		for(int i=1;i<=n;i++)p[i]=(x>>s[i])&1;
		S[x].build(p,n);
		for(int i=1;i<=n;i++)p[i]=(x>>t[i])&1;
		T[x].build(p,m);
	}
	for(int i=1;i+m-1<=n;i++){
		for(int x=1;x<(1<<6);x++){
			tag[x]=S[x].query(i,i+m-1)==T[x].all;
		}
		for(int x=1;x<(1<<6);x++)if(tag[x])
			for(int y=1;y<(1<<6);y++)if((x|y)==y&&x!=y){
				tag[y]=false;
			}
		ans=6;
		for(int x=1;x<(1<<6);x++)if(tag[x])ans--;
		print(ans," \n"[i==n-m+1]);
	}
}