#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9,M=N*50,TOT=(M<<1);
int T,n,m,tot,rev[N];
struct interval{
	int l,r,id;
	inline bool operator<(const interval &rhs)const{
		return r==rhs.r?l<rhs.l:r<rhs.r;
	}
}a[N];
vector<int>e[TOT+10];
void link(int u,int x,int v,int y){
	// x/y: 1选/0不选
	// u, u+M
	e[u+(x?M:0)].emplace_back(v+(y?M:0));
	// fprintf(stderr,"link %d[%d] %d[%d]\n",u,x,v,y);
}
struct segment{
	int l,r,mid;
	int nod[2];
}p[N<<2];
void build(int u,int l,int r){
	p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
	if(l==r){
		p[u].nod[0]=l;
		p[u].nod[1]=l;
		return;
	}
	p[u].nod[0]=++tot;
	p[u].nod[1]=++tot;
	build(u<<1,l,p[u].mid);
	build(u<<1|1,p[u].mid+1,r);
	link(p[u].nod[0],0,p[u<<1].nod[0],0);
	link(p[u].nod[0],0,p[u<<1|1].nod[0],0);
	link(p[u<<1].nod[1],1,p[u].nod[1],1);
	link(p[u<<1|1].nod[1],1,p[u].nod[1],1);
}
void cover(int u,int l,int r,int x){
	if(p[u].l==l&&p[u].r==r){
		link(x,1,p[u].nod[0],0);
		link(p[u].nod[1],1,x,0);
		return;
	}
	if(r<=p[u].mid){
		cover(u<<1,l,r,x);
	}else if(l>p[u].mid){
		cover(u<<1|1,l,r,x);
	}else{
		cover(u<<1,l,p[u].mid,x);
		cover(u<<1|1,p[u].mid+1,r,x);
	}
}
int dfn[TOT+10],low[TOT+10],cnt,q[TOT+10],sz,iq[TOT+10];
int fr[TOT+10],B;
void Tarjan(int x){
	dfn[x]=low[x]=++cnt,q[++sz]=x,iq[x]=1;
	for(int i=0;i<e[x].size();++i)if(!dfn[e[x][i]]){
		Tarjan(e[x][i]),low[x]=min(low[x],low[e[x][i]]);
	}else if(iq[e[x][i]])low[x]=min(low[x],dfn[e[x][i]]);
	if(low[x]==dfn[x]){
		++B;
		while(q[sz]!=x)fr[q[sz]]=B,iq[q[sz--]]=0;
		fr[q[sz]]=B,iq[q[sz--]]=0;
	}
}
bool two_SAT(){
	B=cnt=0;
	for(int i=1;i<=tot;i++){
		dfn[i]=dfn[i+M]=0;
	}
	for(int i=1;i<=tot;i++){
		if(!dfn[i])Tarjan(i);
		if(!dfn[i+M])Tarjan(i+M);
	}
	for(int i=1;i<=tot;++i)if(fr[i]==fr[i+M])return 0;
	return true;
}
int main(){
#ifdef memset0
	freopen("C.in","r",stdin);
#endif
	cin>>T;
	while(T--){
		cin>>n>>m;
		tot=n;
		for(int i=1;i<=n;i++){
			cin>>a[i].l>>a[i].r;
			a[i].id=i;
		}
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++){
			rev[a[i].id]=i;
		}
		for(int u,v,i=1;i<=m;i++){
			cin>>u>>v;
			link(rev[u],0,rev[v],1);
			link(rev[v],0,rev[u],1);
		}
		build(1,1,n);
		for(int i=1;i<=n;i++){
			int l=1,r=i-1,res=-1;
			while(l<=r){
				int mid=(l+r)>>1;
				if(a[mid].r>=a[i].l){
					res=mid;
					r=mid-1;
				}else{
					l=mid+1;
				}
			}
			if(res!=-1){
				cover(1,res,i-1,i);
			}
		}
		cout<<(two_SAT()?"YES\n":"NO\n");
		for(int i=1;i<=tot;i++){
			e[i].clear();
			e[i+M].clear();
		}
	}
}