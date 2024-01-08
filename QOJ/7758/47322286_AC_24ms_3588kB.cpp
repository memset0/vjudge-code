#include<bits/stdc++.h>
#define all(x) begin(x),end(x)
using namespace std;
const int N=2000;
int n,op[N+10],xa[N+10],ya[N+10],xb[N+10],yb[N+10];
long long r[N+10];
int xl,xr,yl,yr;
char c[N+10],str[114],prt;
long long Dis(int xx,int yy,int tx,int ty){
	return 1ll*(xx-tx)*(xx-tx)+1ll*(yy-ty)*(yy-ty);
}
int main(){
#ifdef memset0
	//freopen(".in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(int t=1;t<=n;++t){
		cin>>str;
		if(str[0]=='C'){
			op[t]=1;
			cin>>xa[t]>>ya[t]>>r[t]>>str;
			r[t]=1ll*r[t]*r[t];
			c[t]=str[0];
		}else if(str[2]=='c'){
			op[t]=2;
			cin>>xa[t]>>ya[t]>>xb[t]>>yb[t]>>str;
			c[t]=str[0];
		}else{
			cin>>xl>>yl>>xr>>yr;
			for(int j=yr;j>=yl;--j)for(int i=xl;i<=xr;++i){
				//cout<<"i="<<i<<" j="<<j<<"\n";
				prt='.';
				for(int k=t-1;k>=1;--k){
					if(op[k]==1&&Dis(xa[k],ya[k],i,j)<=r[k]){
						prt=c[k];
						break;
					}
					if(op[k]==2&&xa[k]<=i&&i<=xb[k]&&ya[k]<=j&&j<=yb[k]){
						prt=c[k];
						break;
					}
				}
				cout<<prt;
				if(i==xr)cout<<'\n';
			}
		}
	}
}
/*
7
Circle 0 0 5 *
Circle -2 2 1 @
Circle 2 2 1 @
Rectangle 0 -1 0 0 ^
Rectangle -2 -2 2 -2 _
Render -5 -5 5 5
Render -1 0 1 2

*/