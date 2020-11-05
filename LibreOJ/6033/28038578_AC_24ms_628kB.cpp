#include<bits/stdc++.h>
template<class T> inline void read(T &x){
    x=0;register char c=getchar();register bool f=0;
    while(!isdigit(c))f^=c=='-',c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=110,M=10010;
int n,m,pos,cnt,col[M],id[N][N],bln[M];
char s[N][N];
bool use[M];
std::vector<int> ans,G[M];
inline void add(int u,int v){G[u].push_back(v),G[v].push_back(u);}
bool match(int u){
	for(auto v:G[u])if(col[v]!=cnt){
		col[v]=cnt;
		if(!bln[v]||match(bln[v])){bln[v]=u,bln[u]=v;return true;}
	}
	return false;
}
void solve(int u){
	use[u]=1,ans.push_back(u);
	for(auto v:G[u])if(!use[bln[v]])solve(bln[v]);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m);
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)id[i][j]=++pos;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		if(s[i][j]=='#')continue;
		if(s[i][j+1]=='.')add(id[i][j],id[i][j+1]);
		if(s[i+1][j]=='.')add(id[i][j],id[i+1][j]);
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(s[i][j]=='.'&&((i+j)&1))++cnt,match(id[i][j]);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(s[i][j]=='.'&&!bln[id[i][j]])solve(id[i][j]);
	printf("%lu\n",ans.size()),std::sort(ans.begin(),ans.end());
	for(auto x:ans)printf("%d %d\n",(x-1)/m+1,(x-1)%m+1);
}
