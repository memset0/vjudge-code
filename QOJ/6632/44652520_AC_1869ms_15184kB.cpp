#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=l,i##end=r;i<=i##end;i++)
#define per(i,l,r) for(int i=l,i##end=r;i>=i##end;i--)
using namespace std;
const int N=1e6+9;
int T,n,m,k,a[N],c[N],d[N];
bool check(int x){
	long long sum=0;
	for(int i=1;i<=((n+1)>>1);i++)
		if(a[i]>x){
			int y=a[i]/(x+1)+1;
			sum+=d[y];
			// fprintf(stderr,"%d : %d %d %d %d\n",i,a[i],x,y,c[y]);
			if(sum>k)return false;
		}
	// cerr<<"check "<<x<<" : "<<sum<<endl;
	return true;
}
int main(){
#ifdef memset0
	freopen("B.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>k;
		rep(i,1,n)cin>>a[i];
		sort(a+1,a+n+1);
		rep(i,1,m)cin>>c[i];
		c[1]=0;
		for(int i=2;i<=m;i++){
			for(int j=2;j<=i&&i*j<=m;j++)c[i*j]=min(c[i*j],c[i]+c[j]);
		}
		d[m]=c[m];
		for(int i=m-1;i>=1;i--)d[i]=min(c[i],d[i+1]);
		d[m+1]=INT_MAX;
		for(int i=2;i<=m;i++)
			for(int j=i;j<=m;j++)
				if(i*j>m){
					d[m+1]=min(d[m+1],c[i]+d[j]);
					break;
				}
		for(int i=1;i<=m;i++)d[i]=min(d[i],d[m+1]);
		// for(int i=1;i<=m;i++)cerr<<d[i]<<" \n"[i==m];
		int l=0,r=m,mid,ans=-1;
		while(l<=r){
			mid=(l+r)>>1;
			if(check(mid)){
				ans=mid;
				r=mid-1;
			}else{
				l=mid+1;
			}
		}
		assert(ans!=-1);
		cout<<ans<<'\n';
	}
}