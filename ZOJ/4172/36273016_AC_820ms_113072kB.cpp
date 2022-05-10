#include<bits/stdc++.h>
using namespace std;
template<class T> inline void read(T &x){
	x=0; char c=getchar(); bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar('0'+x%10);
}
const int N=1e6+10;
int nod,rt[N],a[N];
long long pre[N];
struct Segment{
	int lc,rc,cnt;
	long long sum;
}p[N<<4];
void build(int &u,int l,int r){
	u=++nod;
	p[u].cnt=0;
	p[u].sum=0;
	if(l==r){
		return;
	}
	int mid=(l+r)>>1;
	build(p[u].lc,l,mid);
	build(p[u].rc,mid+1,r);
}
void modify(int &u,int v,int k,int l,int r){
	u=++nod;
	p[u].cnt=p[v].cnt+1;
	p[u].sum=p[v].sum+k;
	if(l==r){
		return;
	}
	int mid=(l+r)>>1;
	if(k<=mid){
		p[u].rc=p[v].rc;
		modify(p[u].lc,p[v].lc,k,l,mid);
	}else{
		p[u].lc=p[v].lc;
		modify(p[u].rc,p[v].rc,k,mid+1,r);
	}
}
long long query(int u,int v,int k,int l,int r){
//	printf("query %d %d %d %d %d [%d %lld]\n",u,v,k,l,r,p[v].cnt-p[u].cnt,p[v].sum-p[u].sum);
	if(k==p[v].cnt-p[u].cnt){
//		printf("found %lld\n",p[v].sum-p[u].sum);
		return p[v].sum-p[u].sum;
	}
	if(l==r){
		return (long long)k*l;
	}
	int mid=(l+r)>>1;
	int left_part=p[p[v].lc].cnt-p[p[u].lc].cnt;
	if(k<=left_part){
		return query(p[u].lc,p[v].lc,k,l,mid);
	}else{
//		printf("found %lld\n",p[p[v].lc].sum-p[p[u].lc].sum);
		return p[p[v].lc].sum-p[p[u].lc].sum+query(p[u].rc,p[v].rc,k-left_part,mid+1,r);
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
//	freopen("2.out","w",stdout);
//	cerr<<sizeof(p)/1024./1024.<<endl;
#endif
	for(int i=1;i<N;i++){
		pre[i]=pre[i-1]+(long long)i*i;
	}
	int t;
	read(t);
	while(t-->0){
		int n,m;
		nod=0;
		read(n);
//		printf("!! %d\n",n);
		build(rt[0],0,1e6);
		for(int i=1;i<=n;i++){
			read(a[i]);
			modify(rt[i],rt[i-1],1e6-a[i],0,1e6);
		}
		read(m);
//		printf("!! %d %d\n",m,nod);
		for(int l,r,k,i=1;i<=m;i++){
			read(l),read(r),read(k);
			long long ans=pre[r-l+1];
			ans+=1000000ll*k;
			ans-=query(rt[l-1],rt[r],k,0,1e6);
			print(ans),putchar('\n');
		}
//		cerr<<clock()<<endl;
	}
}
