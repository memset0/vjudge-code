#include<bits/stdc++.h>
using namespace std;
const int N=6e5+10,K=20;
const double eps=1e-10;
int n,m,x,a[N],lg[N],st[20][N];
double sum,ans;
mt19937 rng(20040725);
inline int better(int i,int j){return a[i]<a[j]?j:i;}
inline int query(int l,int r){
	if(l==r)return l;
	int k=lg[r-l];
	return better(st[k][l],st[k][r-(1<<k)]);
}
struct segment{
	int l,r,mid;
	double s[K];
}p[N<<2];
void build(int u,int l,int r){
	p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
	if(l==r){
		p[u].s[0]=a[l];
		for(int i=1;i<K;i++)p[u].s[i]=p[u].s[i-1]*a[l];
		return;
	}
	build(u<<1,l,p[u].mid);
	build(u<<1|1,p[u].mid+1,r);
	for(int i=0;i<K;i++){
		p[u].s[i]=p[u<<1].s[i]+p[u<<1|1].s[i];
	}
}
double query(int u,int l,int r){
	if(p[u].l==l&&p[u].r==r){
		double sum=0;
		for(int i=K-1;i>=0;i--){
			sum=(sum+p[u].s[i]/(i+1))/x;
		}
		return sum;
	}
	if(r<=p[u].mid)return query(u<<1,l,r);
	if(l>p[u].mid)return query(u<<1|1,l,r);
	return query(u<<1,l,p[u].mid)+query(u<<1|1,p[u].mid+1,r);
}
void solve(int l,int r){
	if(l>r||ans<eps){
		return;
	}
	int pos=query(l,r);
	if(a[pos]<(x>>1)){
		ans*=exp(-query(1,l,r));
		return;
	}
	ans*=1-a[pos]/(double)x;
	if(rng()&1){
		solve(l,pos-1);
		solve(pos+1,r);
	}else{
		solve(pos+1,r);
		solve(l,pos-1);
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
//	freopen("ex_gjx3.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cout<<fixed<<setprecision(12);
	lg[0]=-1;
	for(int i=1;i<N;i++)lg[i]=lg[i>>1]+1;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++){
		st[0][i]=better(i,i+1);
	}
	for(int i=1;i<20;i++)
		for(int j=1;j+(1<<i)<=n;j++){
			st[i][j]=better(st[i-1][j],st[i-1][j+(1<<(i-1))]);
		}
	build(1,1,n);
	for(int l,r,i=1;i<=m;i++){
		cin>>l>>r>>x;
		ans=1;
		solve(l,r);
		cout<<1-ans<<endl;
	}
}