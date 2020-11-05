#include<bits/stdc++.h>
#define fi first
#define se second
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
const int N=3e5+10;
int n,m,s,f[N],sa[N],rk[N],pt[N],ans[N];
struct node{
	int l,r,w;
}a[N];
std::set<int> set;
std::vector<int> val,G[N],L[N],ins[N<<1],del[N<<1];
std::map<int,int> map[N];
std::pair<int,int> seg[N<<2];
std::multiset<int> g[N];
std::vector<std::pair<int,int>> qry,edg;
std::vector<std::pair<std::pair<int,int>,int>> q;
std::pair<int,int> merge(const std::pair<int,int> &a,const std::pair<int,int> &b){
	if(a.fi>b.fi){
		return {a.fi,std::max(a.se,b.fi)};
	}else{
		return {b.fi,std::max(a.fi,b.se)};
	}
}
void modify(int u,int k,int x,int l,int r){
	if(l==r){seg[u]={x,0};return;}
	int mid=(l+r)>>1;
	if(k<=mid)modify(u<<1,k,x,l,mid);
	else modify(u<<1|1,k,x,mid+1,r);
	seg[u]=merge(seg[u<<1],seg[u<<1|1]);
}
std::pair<int,int> query(int u,int ql,int qr,int l,int r){
	if(ql==l&&qr==r)return seg[u];
	int mid=(l+r)>>1;
	if(qr<=mid)return query(u<<1,ql,qr,l,mid);
	if(ql>mid)return query(u<<1|1,ql,qr,mid+1,r);
	return merge(query(u<<1,ql,mid,l,mid),query(u<<1|1,mid+1,qr,mid+1,r));
}
int query(int x){
	int res=f[x];
	if(pt[x]){
		auto it=query(1,1,pt[x],1,n);
		// printf("query %d -> rk=%d pt=%d : %d %d\n",x,rk[x],pt[x],it.fi,it.se);
		res=std::max(res,f[x]+(rk[x]<=pt[x]&&it.first==f[x]?it.se:it.fi));
	}
	if(g[x].size())res=std::max(res,f[x]+*g[x].rbegin());
	for(int y:L[x])res=std::max(res,f[x]+f[y]+map[x][y]);
	// printf("query(%d) => %d\n",x,res);
	return res;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	val={0,(int)(2e9)};
	read(n),read(s);
	for(int l,r,i=1;i<=n;i++){
		read(a[i].l),read(a[i].r),read(a[i].w);
		val.push_back(a[i].l);
		val.push_back(a[i].r);
	}
	std::sort(val.begin(),val.end());
	val.erase(std::unique(val.begin(),val.end()),val.end());
	for(int i=1;i<=n;i++){
		ins[std::lower_bound(val.begin(),val.end(),a[i].l)-val.begin()].push_back(i);
		del[std::lower_bound(val.begin(),val.end(),a[i].r)-val.begin()].push_back(i);
	}
	read(m);
	for(int x,i=1;i<=m;i++){
		read(x);
		qry.push_back({x,i});
	}
	std::sort(qry.begin(),qry.end());
	for(int i=1;i<=n;i++)sa[i]=i;
	std::sort(sa+1,sa+n+1,[](int i,int j){return a[i].w<a[j].w;});
	for(int i=1;i<=n;i++){
		a[n+1].w=s-a[i].w;
		rk[sa[i]]=i;
		pt[i]=std::upper_bound(sa+1,sa+n+1,n+1,[](int i,int j){return a[i].w<a[j].w;})-sa-1;
	}
	// for(int i=1;i<=n;i++)fprintf(stderr,"%d%c",sa[i]," \n"[i==n]);
	// for(int i=1;i<=n;i++)fprintf(stderr,"%d%c",pt[i]," \n"[i==n]);
	for(int i=0;i<val.size();i++){
		if(i){
			// fprintf(stderr,"> %d %d : %d\n",i,val[i],(int)set.size());
			std::pair<int,int> t;
			if(!set.size()){
				t={0,0};
			}else if(set.size()==1){
				if(a[*set.begin()].w>s)t={-1,-1};
				else t={*set.begin(),-1};
			}else if(set.size()==2){
				if(a[*set.begin()].w+a[*set.rbegin()].w>s)t={-1,-1};
				else t={*set.begin(),*set.rbegin()};
			}else{
				t={-1,-1};
			}
			q.push_back({t,val[i]-val[i-1]});
		}
		for(int x:ins[i])set.insert(x);
		for(int x:del[i])set.erase(x);
	}
	for(const auto &it:q)
		if(it.fi.fi&&~it.fi.fi&&it.fi.se&&~it.fi.se){
			edg.push_back(it.fi);
		}
	std::sort(edg.begin(),edg.end());
	edg.erase(std::unique(edg.begin(),edg.end()),edg.end());
	for(const auto &it:edg){
		G[it.fi].push_back(it.se);
		G[it.se].push_back(it.fi);
	}
	for(const auto &it:edg)
		if(G[it.fi].size()>1&&G[it.se].size()>1){
			L[it.fi].push_back(it.se);
			L[it.se].push_back(it.fi);
		}
	for(int i=1;i<=n;i++){
		if(G[i].size()==1)g[G[i][0]].insert(0);
	}
	int tim=0,fre=0,max=0,k=0;
	for(const auto &it:q){
		int u=it.fi.fi,v=it.fi.se,t=it.se;
		// fprintf(stderr,"u=%d v=%d t=%d\n",u,v,t);
		if(u==0&&v==0){
			fre+=t;
		}else if(u!=-1&&v==-1){
			if(G[u].size()==1)g[G[u][0]].erase(g[G[u][0]].find(f[u]+map[u][G[u][0]]));
			f[u]+=t;
			// printf("modify %d : rk=%d %d\n",u,rk[u],f[u]);
			modify(1,rk[u],f[u],1,n);
			if(G[u].size()==1)g[G[u][0]].insert(f[u]+map[u][G[u][0]]);
			max=std::max(max,query(u));
			if(G[u].size()==1)max=std::max(max,query(G[u][0]));
		}else if(u!=-1&&v!=-1){
			if(G[u].size()==1)g[G[u][0]].erase(g[G[u][0]].find(f[u]+map[u][G[u][0]]));
			if(G[v].size()==1)g[G[v][0]].erase(g[G[v][0]].find(f[v]+map[v][G[v][0]]));
			map[u][v]+=t,map[v][u]+=t;
			if(G[u].size()==1)g[G[u][0]].insert(f[u]+map[u][G[u][0]]);
			if(G[v].size()==1)g[G[v][0]].insert(f[v]+map[v][G[v][0]]);
			max=std::max(max,std::max(query(u),query(v)));
		}
		tim+=t;
		while(k<qry.size()&&qry[k].fi<=max+fre){
			ans[qry[k].se]=tim-(max+fre-qry[k].fi);
			// printf("solve %d %d : %d\n",qry[k].se,qry[k].fi,ans[qry[k].se]);
			k++;
		}
		// fprintf(stderr,">> max=%d fre=%d tim=%d\n",max,fre,tim);
	}
	for(int i=1;i<=m;i++)print(ans[i]),putchar('\n');
}