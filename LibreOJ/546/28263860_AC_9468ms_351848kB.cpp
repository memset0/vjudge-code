#include<bits/stdc++.h>
#define debug(...) (void(0))
// #define debug(...) fprintf(stderr,__VA_ARGS__)
#define allof(v) v.begin(),v.end()
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
const int N=1e6+10;
int n,m,k,q;
struct node{
	int x,y;
	inline int c(bool fl)const{return fl?y:x;}
	inline int& c_refer(bool fl){return fl?y:x;}
	inline bool operator<(const node &other)const{
		return x==other.x?y<other.y:x<other.x;
	}
}s,a[N],t[N];
std::vector<node*> ptr;
struct atom{
	int i,l,r;
};
namespace discrete{
	struct discrete{
		int limit,length;
		std::vector<int> b;
		inline void push(int a){
			if(a>1)b.push_back(a-1);
			b.push_back(a);
			if(a<limit)b.push_back(a+1);
		}
		inline void build(){
			std::sort(allof(b));
			b.erase(std::unique(allof(b)),b.end());
			length=b.size();
		}
		inline int locate(int x){
			return std::lower_bound(allof(b),x)-b.begin()+1;
		}
	}d[2];
	void solve(const std::vector<node*> &ptr){
		d[0].limit=n,d[0].b.push_back(1),d[0].b.push_back(n);
		d[1].limit=m,d[1].b.push_back(1),d[1].b.push_back(m);
		for(auto x:ptr)for(int fl=0;fl<2;fl++)d[fl].push((*x).c(fl));
		d[0].build(),d[1].build();
		for(auto x:ptr)for(int fl=0;fl<2;fl++)(*x).c_refer(fl)=d[fl].locate((*x).c(fl));
	}
} using discrete::d;
struct graph{
	int nod,fl,rt[N],res[N];
	bool inq[N];
	std::vector<int> q;
	std::vector<node> v[N];
	std::vector<atom> list;
	std::vector<std::pair<int,int>> event[N];
	struct seg_node{
		int lc,rc,val;
		bool vis;
	}p[N<<4];
	void build(int &u,int l,int r){
		u=++nod;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(p[u].lc,l,mid);
		build(p[u].rc,mid+1,r);
	}
	void modify(int &u,int t,int k,int x,int l,int r){
		p[u=++nod]=p[t];
		if(l==r){p[u].val=x;return;}
		int mid=(l+r)>>1;
		if(k<=mid)modify(p[u].lc,p[t].lc,k,x,l,mid);
		else modify(p[u].rc,p[t].rc,k,x,mid+1,r);
	}
	void dfs(int u,int x,int l,int r){
		if(p[u].vis)return; p[u].vis=1;
		if(p[u].val&&!inq[p[u].val]){
			q.push_back(p[u].val),inq[p[u].val]=1;
			res[p[u].val]=std::min(res[p[u].val],x);
		}
		if(l==r)return;
		int mid=(l+r)>>1;
		dfs(p[u].lc,x,l,mid);
		dfs(p[u].rc,x,mid+1,r);
	}
	void update(int u,int ql,int qr,int x,int l,int r){
		if(ql==l&&qr==r){dfs(u,x,l,r);return;}
		int mid=(l+r)>>1;
		if(qr<=mid)update(p[u].lc,ql,qr,x,l,mid);
		else if(ql>mid)update(p[u].rc,ql,qr,x,mid+1,r);
		else{
			update(p[u].lc,ql,mid,x,l,mid);
			update(p[u].rc,mid+1,qr,x,mid+1,r);
		}
	}
	inline int locate(const node &x){
		int l=1,r=list.size()-1;
		while(l<=r){
			int mid=(l+r)>>1;
			if(list[mid].i<x.c(fl^1)||list[mid].i==x.c(fl^1)&&list[mid].r<x.c(fl))l=mid+1;
			if(list[mid].i>x.c(fl^1)||list[mid].i==x.c(fl^1)&&list[mid].l>x.c(fl))r=mid-1;
			if(list[mid].i==x.c(fl^1)&&list[mid].l<=x.c(fl)&&list[mid].r>=x.c(fl))return mid;
		}
		return -1;
	}
	inline int ans(const node &x){return res[locate(x)];}
	void build(){
		debug("BUILD %d\n",fl);
		for(int i=1;i<=k;i++)v[a[i].c(fl^1)].push_back(a[i]);
		list.push_back({0,0,0});
		for(int i=1,lst;lst=0,i<=d[fl^1].length;i++){
			const auto push_back=[&](const atom &x){
				if(x.l>x.r)return;
				event[x.l].push_back(std::make_pair(x.i,list.size()));
				event[x.r+1].push_back(std::make_pair(x.i,0));
				debug("LIST[%2d] | %d %d %d\n",list.size(),x.i,x.l,x.r);
				list.push_back(x);
			};
			std::sort(v[i].begin(),v[i].end());
			for(auto x:v[i])push_back({i,lst+1,x.c(fl)-1}),lst=x.c(fl);
			push_back({i,lst+1,d[fl].length});
		}
		for(int i=1;i<=d[fl].length;i++){
			rt[i]=rt[i-1];
			for(auto x:event[i])modify(rt[i],rt[i],x.first,x.second,1,d[fl^1].length);
		}
		debug("BUILD %d -end -size%d\n",fl,list.size());
	}
	void clear(){
		q.clear();
		memset(inq,0,sizeof(inq));
		for(int i=1;i<=nod;i++)p[i].vis=0;
	}
	graph(){
		memset(res,63,sizeof(res));
	}
}f[2];
void solve(int sf){
	debug("SOLVE %d\n",sf);
	int fl=sf,ss=f[fl].locate(s);
	f[fl].q.push_back(ss),f[fl].res[ss]=0;
	for(int dis=0;f[fl].q.size();dis++,fl^=1){
		debug(">> dis = %d | side %c\n",dis,fl?'Y':'X');
		f[fl^1].q.clear();
		for(int i:f[fl].q){
			const auto &x=f[fl].list[i];
			debug("%3d | %d %d %d\n",i,x.i,x.l,x.r);
			f[fl^1].update(f[fl^1].rt[x.i],x.l,x.r,dis+1,1,d[fl].length);
		}
	}
	debug("SOLVE %d -end\n",sf);
}
int main(){
#ifdef local
	freopen("1.in","r",stdin);
#endif
	read(n),read(m),read(k),read(q),f[1].fl=1;
	for(int i=1;i<=k;i++)read(a[i].x),read(a[i].y),ptr.push_back(&a[i]);
	read(s.x),read(s.y),ptr.push_back(&s);
	for(int i=1;i<=q;i++)read(t[i].x),read(t[i].y),ptr.push_back(&t[i]);
	discrete::solve(ptr);
	for(int i=1;i<=k;i++)debug("%4d A | %d %d\n",i,a[i].x,a[i].y);
	debug("     S | %d %d\n",s.x,s.y);
	for(int i=1;i<=q;i++)debug("%4d T | %d %d\n",i,t[i].x,t[i].y);
	f[0].build(),f[1].build();
	solve(0),f[0].clear(),f[1].clear(),solve(1);
	for(int i=1;i<=q;i++){
		int out=std::min(f[0].ans(t[i]),f[1].ans(t[i]));
		print(out==1061109567?-1:out),putchar('\n');
	}
	debug("clocks: ",clock()/(double)CLOCKS_PER_SEC);
}