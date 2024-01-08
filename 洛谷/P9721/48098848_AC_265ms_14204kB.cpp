#include<bits/stdc++.h>
#define all(x) begin(x),end(x)
using namespace std;
const int N=2e3+9;
int n,p[N+10],pos[N+10],q[N+10][N+10];
int cnt=0;
int Que(int l,int r){
	if(l>=r)return 0;
	assert((++cnt)<=40000);
	cout<<"? "<<l<<" "<<r<<"\n";
	cout<<flush;
	int ret;
	cin>>ret;
	return ret;
}
bool Check(int x,int y){
	int a=Que(x,y),b=Que(x+1,y);
	return a^b^q[x][y-1]^q[x+1][y-1];
}
int l,r,mid,fl;
int main(){
#ifndef ONLINE_JUDGE
	//freopen(".in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	p[1]=1,pos[1]=1,q[1][1]=0;
	for(int i=2;i<=n;++i){
		l=0,r=i-1;
		while(l<r){
			mid=(l+r+1>>1);
			if(Check(pos[mid],i))r=mid-1;
			else l=mid;
		}
		//cout<<"l="<<l<<"\n";
		for(int j=i-1;j>l;--j)++p[pos[j]],pos[j+1]=pos[j];
		p[pos[l+1]=i]=l+1;
		fl=0;
		for(int j=i-1;j>=1;--j)fl^=(p[j]>p[i]),q[j][i]=q[j][i-1]^fl;
		//for(int j=1;j<=i;++j)cout<<p[j]<<" \n"[j==i];cout<<flush;
	}
	cout<<"! ";
	for(int i=1;i<=n;++i)cout<<p[i]<<" ";
	cout<<flush;
}