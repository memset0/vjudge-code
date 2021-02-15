#include<bits/stdc++.h>
#define debug(...) fprintf(stderr,__VA_ARGV__)
#define DD fprintf(stderr,"Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__);
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))c^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
const int N=5e2+10;
int T,n,m,q,nod,ans,a[N],b[N],val[N][2],e[N][2],col[N],cho[N],dfn[N],tmp[N],siz[N];
bool vis[N],onc[N],ins[N];
std::vector<int> stk,stkE;
std::vector<std::pair<int,int>> G[N];
struct node{
	int lc,rc,val,tag;
}p[N*10];
struct graph{
	int fl,id,base,sumL,sumR,ans,rt,pos;
	std::vector<int> vet,cir,vetE,cirE;
	void dfs(int u,int src){
		vis[u]=1,col[u]=id;
		vet.push_back(u),stk.push_back(u);
		for(auto eg:G[u]){
			int v=eg.first,w=eg.second; if(w==src)continue;
			if(vis[v]){
				fl=true,cir=stk;
				cirE=stkE,cirE.push_back(w);
			}else{
				vetE.push_back(w),stkE.push_back(w);
				dfs(v,w);
				stkE.pop_back();
			}
		}
		stk.pop_back();
	}
	void dfs2(int u,int src){
		ins[u]=1;
		if(!onc[u]&&!fl)cho[src]=e[src][1]==u;
		for(auto eg:G[u]){
			int v=eg.first,w=eg.second; if(w==src)continue;
			if(!ins[v])dfs2(v,w);
		}
		ins[u]=0;
	}
	void dfs3(int u,int src,int dis){
		dfn[u]=++pos,siz[u]=1,tmp[dfn[u]]=dis;
		for(auto eg:G[u]){
			int v=eg.first,w=eg.second; if(w==src)continue;
			dfs3(v,w,dis+val[w][cho[w]^1]-val[w][cho[w]]);
			siz[u]+=siz[v];
		}
	}
	inline void pushup(int u,int x){
		p[u].val+=x;
		p[u].tag+=x;
	}
	inline void pushdown(int u){
		pushup(p[u].lc,p[u].tag);
		pushup(p[u].rc,p[u].tag);
		p[u].tag=0;
	}
	void build(int &u,int l,int r){ 
		u=++nod;
		if(l==r){p[u].val=tmp[l]; return;}
		int mid=(l+r)>>1;
		build(p[u].lc,l,mid);
		build(p[u].rc,mid+1,r);
		p[u].val=std::max(p[p[u].lc].val,p[p[u].rc].val);
	}
	void modify(int u,int ql,int qr,int x,int l,int r){
		if(l!=r&&p[u].tag)pushdown(u);
		if(ql==l&&qr==r){pushup(u,x); return;}
		int mid=(l+r)>>1;
		if(qr<=mid)modify(p[u].lc,ql,qr,x,l,mid);
		else if(ql>mid)modify(p[u].rc,ql,qr,x,mid+1,r);
		else modify(p[u].lc,ql,mid,x,l,mid),modify(p[u].rc,mid+1,qr,x,mid+1,r);
		p[u].val=std::max(p[p[u].lc].val,p[p[u].rc].val);
	}
	void init(int s,int cur){
DD;
		id=cur,dfs(s,0);
		for(int x:cir)onc[x]=1;
		onc[s]=1,dfs2(s,0);
		if(fl){
			int lst=e[cirE[0]][e[cirE[1]][0]==e[cirE[0]][1]||e[cirE[1]][1]==e[cirE[0]][1]];
			cho[cirE[0]]=(e[cirE[0]][1]==lst)+2;
			for(auto t=std::next(cirE.begin());t!=cirE.end();t++){
				cho[*t]=(e[*t][0]==lst)+2;
				lst=e[*t][cho[*t]-2];
			}
			for(int x:vetE)if(0<=cho[x]&&cho[x]<2){
				base+=val[x][cho[x]];
			}else{
				sumL+=val[x][cho[x]-2];
				sumR+=val[x][(cho[x]-2)^1];
			}
			ans=base+std::max(sumL,sumR);
		}else{
			for(auto x:vetE)base+=val[x][cho[x]];
			dfs3(s,0,0);
			build(rt,1,pos);
			ans=base+p[rt].val;
		}
	}
	void modify(int u,int k,int v){
		::ans-=ans;
		if(fl){
			if(cho[u]<2){
				if(cho[u]==k)base+=v;
			}else{
				(k==(cho[u]&1)?sumL:sumR)+=v;
			}
			ans=base+std::max(sumL,sumR);
		}else{
			int x=e[u][cho[u]];
			if(cho[u]==k)base+=v;
			modify(rt,dfn[x],dfn[x]+siz[x]-1,cho[u]==k?-v:v,1,pos);
			ans=base+p[rt].val;
		}
		::ans+=ans;
	}
}g[N];
int main(){
#ifdef local
	freopen("1.in","r",stdin);
#endif
	read(m),read(n),read(T);
	for(int i=0;i<m;i++)read(a[i]);
	for(int i=0;i<m;i++)read(b[i]);
	for(int i=0;i<m;i++)read(val[i][0]),read(val[i][1]);
	for(int i=0,u,v;i<m;i++){
		u=(a[i]+b[i])%n,v=(a[i]-b[i])%n; if(u>v)std::swap(u,v);
		e[i][0]=u,e[i][1]=v;
		G[u].push_back(std::make_pair(v,i));
		G[v].push_back(std::make_pair(u,i));
	}
	for(int i=0;i<n;i++)if(!vis[i])++nod,g[nod].init(i,nod);
	read(q);
DD;
	for(int i=0,x,v,ans;i<q;i++){
		read(x),read(v),x^=ans*T,v^=ans*T;
		g[col[x]].modify(x>>1,x&1,v-val[x>>1][x&1]);
		val[x>>1][x&1]=v;
	}
	fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
}