#include<bits/stdc++.h>
#define ll long long
template<class T> inline void read(T &x){
	x=0;register char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=1e5+10;
const ll inf=1e18;
int n,L,s,e,l,r,cnt,q[N],p[N],c[N];
ll res,tmp,max,a[N],d[N],maxd[N],AA[N],Rmax0[N],Rmax1[N];
std::pair<int,int> pre[N];
std::pair<ll,int> LL[N],RR[N];
std::vector<std::pair<int,int>> G[N];
int bfs(int s){
	memset(d,-1,(n+1)<<3);
	memset(pre,0,(n+1)<<3);
	l=1,r=1,res=s,q[1]=s,d[s]=0;
	while(l<=r){
		int u=q[l++];
		for(std::pair<int,int> it:G[u]){
			int v=it.first,w=it.second;
			if(!~d[v])d[v]=d[u]+w,pre[v]=std::make_pair(u,w),q[++r]=v;
		}
	}
	for(int i=1;i<=n;i++)if(d[i]>d[res])res=i;
	return res;
}
void init(int s,int e){
	memset(d,-1,(n+1)<<3);
	memset(maxd,0,(n+1)<<3);
	// printf("init %d %d\n",s,e);
	l=1,r=0;
	// for(int i=1;i<=n;i++)printf("[%d %d]%c",pre[i].first,pre[i].second," \n"[i==n]);
	for(int u=e;u;u=pre[u].first){
		// printf("> %d : pre => %d %d\n",u,pre[u].first,pre[u].second);
		q[++r]=u,d[u]=0,a[pre[u].first]=a[u]+pre[u].second,c[u]=u,p[++cnt]=u;
	}
	// printf("The Link is: ");
	// for(int i=1;i<=cnt;i++)print(p[i]," \n"[i==cnt]);
	while(l<=r){
		int u=q[l++];
		for(std::pair<int,int> it:G[u]){
			int v=it.first,w=it.second;
			if(!~d[v])d[v]=d[u]+w,a[v]=a[u],c[v]=c[u],q[++r]=v;
		}
	}
	// printf("a[] = "); for(int i=1;i<=n;i++)print(a[i]," \n"[i==n]);
	// printf("d[] = "); for(int i=1;i<=n;i++)print(d[i]," \n"[i==n]);
	// printf("c[] = "); for(int i=1;i<=n;i++)print(c[i]," \n"[i==n]);
	for(int i=1;i<=n;i++)maxd[c[i]]=std::max(maxd[c[i]],d[i]);
}
bool check(ll cur){
	// printf("check %lld\n",cur);
	ll A=-inf,B=-inf,C=-inf,D=-inf;
	for(int i=1,j=n+1;i<=n;i++){
		while(j>1&&LL[i].first+RR[j-1].first>cur)--j;
		// printf(">> i=%d j=%d : %lld %lld\n",i,j,Rmax0[j],Rmax1[j]);
		A=std::max(A,d[LL[i].second]+a[LL[i].second]+Rmax0[j]);
		B=std::max(B,d[LL[i].second]+a[LL[i].second]+Rmax1[j]);
		C=std::max(C,d[LL[i].second]-a[LL[i].second]+Rmax0[j]);
		D=std::max(D,d[LL[i].second]-a[LL[i].second]+Rmax1[j]);
	}
	// printf("A=%lld B=%lld C=%lld D=%lld\n",A,B,C,D);
	A=A-cur+L,B=B-cur+L,C=cur-L-C,D=cur-L-D;
	// printf("A=%lld B=%lld C=%lld D=%lld\n",A,B,C,D);
	for(int i=1;i<=cnt;i++){
		ll limL=std::max(A-a[p[i]],a[p[i]]-C);
		ll limR=std::min(D-a[p[i]],a[p[i]]-B);
		if(limL<=limR){
			ll* it=std::lower_bound(AA+1,AA+cnt+1,limL);
			if(*it<=limR)return true;
		}
	}
	return false;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	while(read(n),read(L),n||L){
		tmp=-inf,max=-inf,res=-1,cnt=0;
		for(int i=1;i<=n;i++)G[i].clear();
		for(int i=1,u,v,w;i<n;i++){
			read(u),read(v),read(w);
			G[u].push_back(std::make_pair(v,w));
			G[v].push_back(std::make_pair(u,w));
		}
		s=bfs(1),e=bfs(s),init(s,e);
		for(int i=1;i<=n;i++){
			LL[i]=std::make_pair(d[i]+a[i],i);
			RR[i]=std::make_pair(d[i]-a[i],i);
		}
		std::sort(LL+1,LL+n+1);
		std::sort(RR+1,RR+n+1);
		// for(int i=1;i<=n;i++)printf("[%lld %d]%c",LL[i].first,LL[i].second," \n"[i==n]);
		// for(int i=1;i<=n;i++)printf("[%lld %d]%c",RR[i].first,RR[i].second," \n"[i==n]);
		Rmax0[n+1]=Rmax1[n+1]=-inf;
		for(int i=n;i>=1;i--){
			Rmax0[i]=std::max(Rmax0[i+1],d[RR[i].second]+a[RR[i].second]);
			Rmax1[i]=std::max(Rmax1[i+1],d[RR[i].second]-a[RR[i].second]);
		}
		for(int i=1;i<=cnt;i++)AA[i]=a[p[i]];
		std::sort(AA+1,AA+cnt+1);
		for(int i=1;i<=cnt;i++){
			max=std::max(max,tmp+a[p[i]]+maxd[p[i]]);
			tmp=std::max(tmp,-a[p[i]]+maxd[p[i]]);
		}
		for(ll L=1,R=max,mid;L<=R;){
			mid=(L+R)>>1;
			check(mid)?(R=mid-1,res=mid):(L=mid+1);
		}
		print(res,'\n');
	}
}