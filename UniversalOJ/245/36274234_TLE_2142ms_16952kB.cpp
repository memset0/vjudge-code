#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,a[N],lg[N],ans[N],st[2][20][N];
inline int query(int l,int r){
	if(l==r)return 0;
	int k=lg[r-l];
	return max(st[1][k][l],st[1][k][r-(1<<k)])-min(st[0][k][l],st[0][k][r-(1<<k)]);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	memset(ans,0x3f,sizeof(ans));
	ans[1]=0;
	cin>>n;
	lg[0]=-1;
	for(int i=1;i<N;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<n;i++){
		st[0][0][i]=min(a[i],a[i+1]);
		st[1][0][i]=max(a[i],a[i+1]);
	}
	for(int i=1;i<20;i++)
		for(int j=1;j+(1<<i)<=n;j++){
			st[0][i][j]=min(st[0][i-1][j],st[0][i-1][j+(1<<(i-1))]);
			st[1][i][j]=max(st[1][i-1][j],st[1][i-1][j+(1<<(i-1))]);
//			cerr<<st[0][i-1][j]<<" "<<st[1][i-1][j]<<endl;
		}
	for(int l=1,r,s;l<n;l++){
		ans[2]=min(ans[2],s=query(l,r=l+1));
		double lim=s*1.05;
		while(true){
//			fprintf(stderr,"l=%d r=%d s=%d\n",l,r,s);
			if(r+1>n||query(l,r+1)>lim){
			}else if(r+2>n||query(l,r+2)>lim){
				++r;
			}else if(r+4>n||query(l,r+4)>lim){
				r+=2;
				if(r+1<=n&&query(l,r+1)<=lim)r++;
			}else{
				for(int k=3;;k++)
					if(r+(1<<k)>n||query(l,r+(1<<k))>lim){
						r+=1<<(k-1);
						for(int i=k-2;i>=0;i--)
							if(r+(1<<i)<=n&&query(l,r+(1<<i))<=lim){
								r+=1<<i;
							}
						break;
					}
			}
			ans[r-l+1]=min(ans[r-l+1],s);
			if(r==n)break;
			s=query(l,++r);
			lim=s*1.05;
		}
	}
	for(int i=n-1;i>=2;i--){
		ans[i]=min(ans[i],ans[i+1]);
	}
	for(int i=2;i<=n;i++){
		cout<<ans[i]<<endl;
	}
}