#include<bits/stdc++.h>
#define debug(x) cerr<<#x<<": "<<(x)<<endl
#ifndef memset0
	#define endl '\n'
#endif
using namespace std;
const int N=2e5+9;
int n,m,tot,siz[N],son[N],p[N],fa[N],ch[N][2],dfn[N],idfn[N],tag[N];
long long cur,ans[N],anspre[N];
struct TriArray{
	int s[N];
	inline void add(int k,int x){for(;k<=n+3;k+=k&-k)s[k]+=x;}
	inline int ask(int k,int r=0){for(;k;k-=k&-k)r+=s[k];return r;}
}tri;
namespace lct{
	int fa[N],son[N][2];
	int top[N];
	bool not_root(int x){return son[fa[x]][0]==x||son[fa[x]][1]==x;}
	void pushup(int x){
		top[x]=x;
		if(son[x][0])top[x]=top[son[x][0]];
	}
	void rotate(int x){
		int y=fa[x],z=fa[y],k=(son[y][1]==x);
		if(not_root(y))son[z][son[z][1]==y]=x;
		fa[x]=z;
		fa[son[x][!k]]=y;
		son[y][k]=son[x][!k];
		son[x][!k]=y;
		fa[y]=x;
		pushup(y),pushup(x);
	}
	void splay(int x){
		while(not_root(x)){
			int y=fa[x];
			if(not_root(y))rotate((son[y][1]==x)==(son[fa[y]][1]==y)?y:x);
			rotate(x);
		}
	}
	void access(int x){
		for(int y=0;x;y=x,x=fa[x])
			splay(x),son[x][1]=y,pushup(x);
	}
	int get_top(int x){
		access(x),splay(x);
		return top[x];
	}
	void link(int x){//set fa[x]=y
		access(x),splay(x),fa[x]=::fa[x];
	}
	void cut(int x){//cut(x,fa[x])
		access(x),splay(x);
		fa[son[x][0]]=0,son[x][0]=0;
	}
	void init(int n){
		for(int i=0;i<=n+3;i++){
			fa[i]=top[i]=0;
			son[i][0]=son[i][1]=0;
		}
	}
}
inline int getsize(int u){
	if(!u)return 0;
	// fprintf(stderr,"get size %d : dfn=%d siz=%d : %d %d\n",u,dfn[u],siz[u], tri.ask(idfn[u]+siz[u]-1),tri.ask(idfn[u]-1));
	return tri.ask(dfn[u]+siz[u]-1)-tri.ask(dfn[u]-1);
}
inline void pushans(int l,int r,int x){
	// fprintf(stderr,">> pushans l=%d r=%d x=%d\n",l,r,x);
	anspre[l]+=x;
	anspre[r+1]-=x;
}
void dfs(int u){
	dfn[u]=++tot;
	idfn[tot]=u;
	siz[u]=1;
	for(int i=0;i<2;i++)
		if(ch[u][i]){
			dfs(ch[u][i]);
			siz[u]+=siz[ch[u][i]];
		}
}
int main(){
#ifdef memset0
	freopen("H.in","r",stdin);
#else
	freopen("heavylight.in","r",stdin);
	freopen("heavylight.out","w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	while(cin>>n,n){
		for(int i=1;i<=n;i++){
			fa[i]=son[i]=tag[i]=siz[i]=0;
			ans[i]=anspre[i]=0;
		}
		lct::init(n);
		fill(tri.s,tri.s+n+5,0);
		for(int i=1;i<=n;i++){
			cin>>ch[i][0]>>ch[i][1];
			for(int j=0;j<2;j++)
				if(ch[i][j]){
					fa[ch[i][j]]=i;
				}
		}
		tot=0,dfs(1);
		cin>>m;
		set<int> st;
		for(int i=1;i<=m;i++){
			cin>>p[i];
			st.insert(p[i]);
		}
		tot=m;
		for(int i=n;i>=1;i--)
			if(!st.count(idfn[i])){
				p[++tot]=idfn[i];
			}
		reverse(p+1,p+n+1);
		cur=0;
		for(int i=1;i<=n;i++){
			int u=p[i];
			// fprintf(stderr,"======= %d %d =======\n",i,u);
			tri.add(dfn[u],1);
			if(u==1){
				continue;
			}
			auto link=[&](int f,int c){
				// fprintf(stderr,"link f=%d c=%d %d %d\n",f,c,ch[f][0],ch[f][1]);
				assert(son[f]!=ch[f][c]);
				cur+=ch[f][c];
				lct::link(ch[f][c]);
				son[f]=ch[f][c];
			};
			auto cut=[&](int f,int c){
				// fprintf(stderr,"cut f=%d c=%d %d %d\n",f,c,ch[f][0],ch[f][1]);
				assert(son[f]==ch[f][c]);
				cur-=ch[f][c];
				lct::cut(ch[f][c]);
				son[f]=0;
			};
			while(true){
				// fprintf(stderr,"get top %d => %d\n",u,lct::get_top(u));
				u=lct::get_top(u);
				int f=fa[u];
				if(!f)break;
				int c=u==ch[f][1];
				int siz_u=getsize(ch[f][c]);
				int siz_v=getsize(ch[f][c^1]);
				// debug(f);
				// debug(c);
				// debug(c^1);
				// debug(ch[f][c]);
				// debug(ch[f][c^1]);
				// debug(getsize(ch[f][c]));
				// debug(getsize(ch[f][c^1]));
				// debug(son[f]);
				if(!ch[f][c^1]||siz_u>siz_v){
					if(son[f]){
						cut(f,c^1);
					}
					if(tag[f]){
						pushans(tag[f],i-1,ch[f][c]);
						tag[f]=0;
					}
					link(f,c);
				}else if(siz_u==siz_v){
					if(son[f]){
						cut(f,c^1);
					}
					tag[f]=i;
				}
				u=f;
			}
			ans[i]=cur;
			// fprintf(stderr,">> ans[%d]=%lld\n",i,cur);
		}
		for(int f=1;f<=n;f++){
			if(tag[f]){
				assert(ch[f][0]&&ch[f][1]&&siz[ch[f][0]]==siz[ch[f][1]]);
				pushans(tag[f],n,ch[f][0]);
				tag[f]=0;
			}
		}
		for(int i=1;i<=n;i++)anspre[i]+=anspre[i-1];
		for(int i=1;i<=n;i++)ans[i]+=anspre[i];
		reverse(ans+1,ans+n+1);
		ans[n+1]=0;
		for(int i=1;i<=m+1;i++){
			cout<<ans[i]<<endl;
		}
	}
}