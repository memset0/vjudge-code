// n log^2 n solution
#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; char c=getchar(); bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=1e5+10;
int n,m,nod,ans,a[N],col[N];
namespace SEG{
	const int M=N*40;
	int nod,lc[M],rc[M],max[M],tag[M];
	inline void up(int u,int x){max[u]+=x,tag[u]+=x;}
	inline void down(int u){if(tag[u])up(lc[u],tag[u]),up(rc[u],tag[u]),tag[u]=0;}
	void build(int &u,int l,int r){
		u=++nod;
		if(l==r){max[u]=a[l]; return;}
		int mid=(l+r)>>1;
		build(lc[u],l,mid);
		build(rc[u],mid+1,r);
		max[u]=std::max(max[lc[u]],max[rc[u]]);
	}
	void modify(int u,int ql,int qr,int x,int l,int r){
		down(u);
		if(ql==l&&qr==r){up(u,x); return;}
		int mid=(l+r)>>1;
		if(qr<=mid)modify(lc[u],ql,qr,x,l,mid);
		else if(ql>mid)modify(rc[u],ql,qr,x,mid+1,r);
		else modify(lc[u],ql,mid,x,l,mid),modify(rc[u],mid+1,qr,x,mid+1,r);
		max[u]=std::max(max[lc[u]],max[rc[u]]);
	}
}
struct node{
	int l,r,mid,rt,d,k,tag,lc,rc;
	std::pair<int,int> todo,item;
	std::queue<std::tuple<int,int,int>> q;
	std::vector<std::pair<int,int>> opt;
}p[N<<1];
inline void pushup(int u,int x){
	p[u].d+=x,p[u].tag+=x,p[u].todo.first-=x;
}
inline void pushdown(int u){
	if(p[u].tag&&p[u].l!=p[u].r){
		pushup(p[u].lc,p[u].tag);
		pushup(p[u].rc,p[u].tag);
		p[u].tag=0;
	}
}
inline void maintain(int u){
	p[u].todo=p[u].item;
	if(p[u].l!=p[u].r){
		pushdown(u);
		if(p[p[u].lc].todo.first<p[u].todo.first)p[u].todo=p[p[u].lc].todo;
		if(p[p[u].rc].todo.first<p[u].todo.first)p[u].todo=p[p[u].rc].todo;
	}
}
int build(int l,int r){
	int u=++nod;
	p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
	SEG::build(p[u].rt,l,r);
	p[u].item=p[u].todo={114514,u};
	if(l!=r){
		p[u].lc=build(l,p[u].mid);
		p[u].rc=build(p[u].mid+1,r);
	}
	return u;
}
void update(int u){
	static int c,k,d,l,r;
	// printf("update %d [%d %d]\n",u,p[u].l,p[u].r);
	while(p[u].q.size()){
		std::tie(c,k,d)=p[u].q.front();
		while(p[u].k<k){
			std::tie(l,r)=p[u].opt[p[u].k++];
			SEG::modify(p[u].rt,l,r,1,p[u].l,p[u].r);
		}
		// printf("%d [%d %d] c=%d k=%d d=%d => [%d %d]\n",u,p[u].l,p[u].r,c,k,d,p[u].d-d,SEG::max[p[u].rt]);
		if(p[u].d-d>=SEG::max[p[u].rt]){
			col[c]--,ans-=!col[c];
			p[u].q.pop();
		}else{
			p[u].item={SEG::max[p[u].rt]+d-p[u].d,u};
			maintain(u);
			return;
		}
	}
	p[u].item={114514,u};
	maintain(u);
}
void modify(int u,int l,int r,int c){
	// printf("modify %d %d %d %d\n",u,l,r,c);
	if(p[u].l==l&&p[u].r==r){
		ans+=!col[c],col[c]++;
		pushup(u,1);
		p[u].q.push({c,(int)p[u].opt.size(),p[u].d});
	}else{
		pushdown(u);
		p[u].opt.push_back({l,r});
		SEG::modify(p[u].rt,l,r,-1,p[u].l,p[u].r);
		if(r<=p[u].mid)modify(p[u].lc,l,r,c);
		else if(l>p[u].mid)modify(p[u].rc,l,r,c);
		else modify(p[u].lc,l,p[u].mid,c),modify(p[u].rc,p[u].mid+1,r,c);
		maintain(u);
	}
	update(u);
	// printf("end modify %d todo=[%d %d,%d]\n",u,p[u].todo.first,p[p[u].todo.second].l,p[p[u].todo.second].r);
}
void resolve(int u,int v){
	// printf("resolve %d %d\n",u,v);
	pushdown(u);
	if(u==v){
		update(u);
		return;
	}
	resolve(p[v].r<=p[u].mid?p[u].lc:p[u].rc,v);
	update(u);
	maintain(u);
	// printf("end resolve todo=[%d %d,%d]\n",p[u].todo.first,p[p[u].todo.second].l,p[p[u].todo.second].r);
}
int main(){
#ifdef memset0
	freopen("2.in","r",stdin);
#endif
	read(n),read(m);
	for(int i=1;i<=n;i++)read(a[i]);
	build(1,n);
	for(int i=1,l,r,x;i<=m;i++){
		read(l),read(r),read(x);
		modify(1,l,r,x);
		while(!p[1].todo.first)resolve(1,p[1].todo.second);
		printf("%d\n",ans);
	}
}