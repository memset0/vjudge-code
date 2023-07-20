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
const int N=1e5+10;
int n,m,p,k;
long long f[N],ans,lst,ned;
std::vector<int> v[N];
std::vector<std::pair<int,int>> G[N];
void dfs(int u,int fa){
	if(u==n)return;
	for(auto e:G[u])if(e.first!=fa){
		v[p].push_back(e.second);
		dfs(e.first,u);
	}
}
inline void pop(int i,long long w){f[i]-=w;}
inline void push(int i,long long w){f[i]-=w,ans+=w*(k-i);}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m);																		
	for(int u,v,w,i=1;i<=m;i++){
		read(u),read(v),read(w);
		G[u].push_back(std::make_pair(v,w));
		G[v].push_back(std::make_pair(u,w));
	}
	for(auto e:G[1]){
		++p,v[p].push_back(0),v[p].push_back(e.second),dfs(e.first,1);
	}
	k=v[1].size()-1;
	// for(int i=1;i<=p;i++){
	// 	for(int j=1;j<=k;j++)print(v[i][j]," \n"[j==k]);
	// }
	for(int i=1;i<=p;i++){
		std::sort(&v[i][1],&v[i][k+1]);
		// std::sort(v[i].begin(),v[i].end());
		for(int j=1;j<=k;j++)f[k-j+1]+=v[i][j]-v[i][j-1];
	}
	// for(int i=1;i<=p;i++){
	// 	for(int j=1;j<=k;j++)print(v[i][j]," \n"[j==k]);
	// }
	push(k,f[k]);
	for(int l=1,r=k-1;l<=r;){
		if(l==r){
			push(l,(lst+f[l]*l)/k);
			break;
		}
		long long ls=f[l]*l+lst;
		long long rs=f[r]*(k-r);
		if(ls>rs){
			ned=(std::max(0ll,f[r]*(k-r)-lst)+l-1)/l;
			lst=lst+ned*l-f[r]*(k-r);
			pop(l,ned),push(r,f[r]);
		}else{
			ned=std::max(0ll,lst+f[l]*l)/(k-r);
			lst=lst+f[l]*l-ned*(k-r);
			pop(l,f[l]),push(r,ned);
		}
		l+=f[l]==0,r-=f[r]==0;
	}
	printf("%lld\n",ans);
}