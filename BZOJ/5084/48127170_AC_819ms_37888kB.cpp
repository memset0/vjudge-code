#include<set>
#include<cstdio>
#include<cstring>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
typedef long long ll;
const int N=200005; 
int n,ind,cnt=1,lst=1,tf[N],tr[N][26],fa[N][20],ch[N][26],dep[N],pos[N],len[N],tin[N],dfn[N];char s[N];std::set<int>S;std::set<int>::iterator it;ll ans;
struct ed{ed*nxt;int to;}pool[N<<1],*p=pool,*lnk[N];
void ae(int u,int v){*++p=(ed){lnk[u],v},lnk[u]=p;}
int extend(int p,int c){
		int np=++cnt;len[np]=len[p]+1;
		for(;p&&!ch[p][c];p=fa[p][0])ch[p][c]=np;
		if(!p)fa[np][0]=1;
		else{
			int q=ch[p][c];
			if(len[p]+1==len[q])fa[np][0]=q;
			else{
				int nq=++cnt;len[nq]=len[p]+1;
				memcpy(ch[nq],ch[q],sizeof(ch[nq]));
				fa[nq][0]=fa[q][0],fa[q][0]=fa[np][0]=nq;
				for(;ch[p][c]==q;p=fa[p][0])ch[p][c]=nq;
			}
		}
		return np;
}
void build(int u){
	for(int i=0;i<26;++i)if(tr[u][i]){
		pos[tr[u][i]]=extend(pos[u],i);
		build(tr[u][i]);
	}
}
void dfs(int u){
	dfn[tin[u]=++ind]=u;
	rep(i,1,19)fa[u][i]=fa[fa[u][i-1]][i-1];
	for(ed*i=lnk[u];i;i=i->nxt){
		dep[i->to]=dep[u]+1;
		dfs(i->to);
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v])u^=v^=u^=v;int ret=dep[u]-dep[v];
	per(i,19,0)if(ret>>i&1)u=fa[u][i];if(u==v)return u;
	per(i,19,0)if(fa[u][i]!=fa[v][i])u=fa[u][i],v=fa[v][i];return fa[u][0];
}
int main(){
	scanf("%s",s+1);n=strlen(s+1);
	int now=1,tot=1;
	rep(i,1,n){
		if(s[i]=='-')now=tf[now];
		else{
			if(!tr[now][s[i]-'a'])tf[tr[now][s[i]-'a']=++tot]=now;
			now=tr[now][s[i]-'a'];
		}
	}
	pos[1]=dep[1]=1,build(1);
	rep(i,2,cnt)ae(fa[i][0],i);
	dfs(1);
	now=1;
	rep(i,1,n){
		if(s[i]=='-'){
			ans-=len[pos[now]],S.erase(tin[pos[now]]);
			int x=0,y=0;it=S.upper_bound(tin[pos[now]]);
			if(it!=S.end())x=dfn[*it];
			if(it!=S.begin())y=dfn[*--it];
			if(x)ans+=len[lca(x,pos[now])];
			if(y)ans+=len[lca(y,pos[now])];
			if(x&&y)ans-=len[lca(x,y)];
			now=tf[now];
		}
		else{
			now=tr[now][s[i]-'a'];
			ans+=len[pos[now]];int x=0,y=0;
			it=S.upper_bound(tin[pos[now]]);
			if(it!=S.end())x=dfn[*it];
			if(it!=S.begin())y=dfn[*--it];
			if(x)ans-=len[lca(x,pos[now])];
			if(y)ans-=len[lca(y,pos[now])];
			if(x&&y)ans+=len[lca(x,y)]; 
			S.insert(tin[pos[now]]);
		}
		printf("%lld\n",ans);
	}
	return 0;
} 