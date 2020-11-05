#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int T,n,m,q,rt[N],tmp[N];

struct edge{
	int u,v,w;
	inline bool operator<(const edge &rhs)const{
		return w<rhs.w;
	}
}e[N];

int anc[N];
int find(int x){return anc[x]==x?x:anc[x]=find(anc[x]);}

namespace lct{
	const int N=::N<<1;
	int nod,fa[N],ch[N][2],val[N],sum[N];
	bool rev[N];
	inline bool getson(int x){return ch[fa[x]][1]==x;}
	inline bool isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
	inline void maintain(int x){sum[x]=max({sum[ch[x][0]],val[x],sum[ch[x][1]]});}
	inline void rotate(int x){
		if(!x||!fa[x])return;
		int f=fa[x],ff=fa[f],fs=getson(x),ffs=getson(f),y=ch[x][fs^1];
		if(!isroot(f))ch[ff][ffs]=x;ch[x][fs^1]=f,ch[f][fs]=y;
		fa[y]=f,fa[f]=x,fa[x]=ff,maintain(f),maintain(x);
	}
	inline void pushup(int x){rev[x]^=1,std::swap(ch[x][0],ch[x][1]);}
	inline void clear(int x){
		if(!isroot(x))clear(fa[x]);
		if(rev[x])pushup(ch[x][0]),pushup(ch[x][1]),rev[x]=0;
	}
	inline void splay(int x){
		clear(x);
		for(int f=fa[x];!isroot(x);rotate(x),f=fa[x])
			if(!isroot(f))rotate(getson(x)==getson(f)?f:x);
	}
	inline void access(int x){
		for(int y=0;x;y=x,x=fa[x])splay(x),ch[x][1]=y,maintain(x);
	}
	inline void mroot(int x){access(x),splay(x),pushup(x);}
	inline void split(int x,int y){mroot(x),access(y),splay(y);}
	inline void link(int x,int y){mroot(x),fa[x]=y;}
	inline void cut(int x,int y){
		split(x,y);
		if(fa[x]==y&&ch[y][0]==x&&!ch[x][1])fa[x]=ch[y][0]=0;
	}
	void clear(int n,int m){
		nod=0;
		for(int i=1;i<=n+m;i++)fa[i]=ch[i][0]=ch[i][1]=rev[i]=0;
	}
}

namespace seg{
	int nod;
	struct segment{
		int lc,rc;
		long long sum;
	}p[N];
	void build(int &u,int l,int r){
		u=++nod,p[u].sum=0;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(p[u].lc,l,mid);
		build(p[u].rc,mid+1,r);
	}
	void modify(int &u,int v,int k,int w,int l,int r){
		p[u=++nod]=p[v],p[u].sum+=w;
		if(l==r)return;
		int mid=(l+r)>>1;
		if(k<=mid)modify(p[u].lc,p[v].lc,k,w,l,mid);
		else modify(p[u].rc,p[v].rc,k,w,mid+1,r);
	}
	long long query(int u,int ql,int qr,int l,int r){
		if(ql==l&&qr==r)return p[u].sum;
		int mid=(l+r)>>1;
		if(qr<=mid)return query(p[u].lc,ql,qr,l,mid);
		if(ql>mid)return query(p[u].rc,ql,qr,mid+1,r);
		return query(p[u].lc,ql,mid,l,mid)+query(p[u].rc,mid+1,qr,mid+1,r);
	}
	void clear(int n,int m){
		nod=0;
	}
}

int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=m;i++)cin>>e[i].u>>e[i].v>>e[i].w;
		sort(e+1,e+m+1);
		seg::build(rt[m+1],1,m);
		for(int i=1;i<=n;i++)anc[i]=i,lct::val[i]=INT_MIN;
		for(int i=m;i>=1;i--){
//			printf(">> e[%d] %d %d %d\n",i,e[i].u,e[i].v,e[i].w);
			rt[i]=rt[i+1],tmp[i]=e[i].w,lct::val[i+n]=i;
			seg::modify(rt[i],rt[i],i,e[i].w,1,m);
			if(find(e[i].u)==find(e[i].v)){
				lct::split(e[i].u,e[i].v);
				int j=lct::sum[e[i].v];
//				printf("cut => %d\n",j);
				lct::cut(e[j].u,j+n);
				lct::cut(e[j].v,j+n);
				seg::modify(rt[i],rt[i],j,-e[j].w,1,m);
			}else{
				anc[find(e[i].u)]=find(e[i].v);
			}
//			printf("link => %d\n",i);
			lct::link(e[i].u,i+n);
			lct::link(e[i].v,i+n);
		}
		cin>>q;
		for(int l,r,last=0,i=1;i<=q;i++){
			cin>>l>>r,l-=last,r-=last;
//			fprintf(stderr,">> %d %d\n",l,r);
			l=lower_bound(tmp+1,tmp+m+1,l)-tmp;
			r=upper_bound(tmp+1,tmp+m+1,r)-tmp-1;
//			fprintf(stderr,">> %d %d\n",l,r);
			cout<<(last=(l<=r?seg::query(rt[l],l,r,1,m):0))<<endl;
		}
		lct::clear(n,m);
		seg::clear(n,m); 
	}
}