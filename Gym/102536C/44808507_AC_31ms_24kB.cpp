#include<bits/stdc++.h>
#ifndef memset0
	#define endl '\n'
#endif
using namespace std;
using ll=long long;
using lf=long double;
const int N=1e3+9;
int T,n,g,w[N],k[N],b[N];
int main(){
#ifdef memset0
	freopen("C.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>g;
		int W=0;
		ll S=0;
		for(int i=1;i<=n;i++){
			cin>>w[i];
			if(w[i]<0){
				w[i]=-w[i];
			}
			W+=w[i];
			S+=w[i]*w[i];
		}
		int K=0,B=0;
		for(int i=1;i<=n;i++){
			cin>>k[i]>>b[i];
			K+=k[i];
			B+=b[i];
		}
		if(B<=0){
			cout<<"0.0"<<endl;
			continue;
		}
		lf Q=sqrtl(S);
		lf up=B;
		lf down=g*Q-K;
		cout<<fixed<<setprecision(15)<<(up/down)<<endl;
	}
}//