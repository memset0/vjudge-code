#include<bits/stdc++.h>
using namespace std;
const int N=1e6+7;
const long long inf=1e18;
int t,n,m,p,q,sum,f[N],g[N],ps[N];
long long v[N<<2],w[N];
inline void build(int l,int r,int t){
	if(l==0) v[t]=0;
	else v[t]=inf;
	if(l==r){
		ps[l]=t;
		return;
	}
	int d=(l+r)>>1;
	build(l,d,t<<1);
	build(d+1,r,t<<1|1);
}
inline long long getmin(int l,int r,int ql,int qr,int t){
	if(l==ql&&r==qr) return v[t];
	int d=(l+r)>>1; long long w=inf;
	if(ql<=d) w=min(w,getmin(l,d,ql,min(d,qr),t<<1));
	if(d+1<=qr) w=min(w,getmin(d+1,r,max(d+1,ql),qr,t<<1|1));
	return w;
}
inline void update(int u,long long c){
	u=ps[u];
	while(u>0){
		v[u]=min(v[u],c);
		u=u>>1;
	}
}
int main(){
	cin>>t;
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&f[i]);
		for(int i=1;i<=n;i++) g[i]=0;
		scanf("%d",&m);
		for(int i=1;i<=m;i++){
			int l,r;
			scanf("%d%d",&l,&r);
			g[r]=max(g[r],l);
		}
		for(int i=1;i<=n;i++) g[i]=max(g[i],g[i-1]);
		build(0,n,1);
		for(int i=1;i<=n;i++){
			//cerr<<i<<" "<<g[i]-1<<","<<n<<endl; 
			w[i]=getmin(0,n,max(g[i-1],0),n,1)+f[i];
			//cerr<<i<<","<<w[i]<<endl;
			update(i,w[i]);
		}
		printf("%lld\n",getmin(0,n,g[n],n,1));
	}
	return 0;
}