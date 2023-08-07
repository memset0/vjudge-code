#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l),i##end=(r);i<=i##end;i++)
#define per(i,l,r) for(int i=(l),i##end=(r);i>=i##end;i--)
using namespace std;
int n,t,m,x,y;
int main(){
#ifdef memset0
	freopen("A.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>t>>m>>x>>y;
	double s=(double)m/x+(double)(n-m)/y;
	s/=60;
	if(s<=t)s=t;
	// printf("%.12lf\n",s);
	cout<<(int)ceil(s-t)<<endl;
}