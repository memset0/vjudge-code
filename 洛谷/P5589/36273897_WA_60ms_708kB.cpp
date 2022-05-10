#include<bits/stdc++.h>
using namespace std;
const int N=64+7;
int t; long long n,w[N],cnt[N];
int main(){
	for(int i=1;i<=64;i++) for(int x=1;x<=i;x++) if(!(i%x)) cnt[i]++; cin>>t;
	while(t--){
      scanf("%lld",&n); double ans=1.0; w[0]=n;
		for(int i=1;i<=64;i++){
			long long l=1,r=2e18,d,pos=0;
			while(l<=r){
				d=(l+r)>>1; long long q=1; bool fl=0;
				for(int z=1;z<=i;z++) {if(q>n/d){fl=1; break;} q=q*d;}
				if(q>n) fl=1; if(fl) r=d-1; else pos=d,l=d+1;
			} w[i]=pos-1;
		}
		for(int i=64;i>0;i--) for(int x=i+1;x<=64;x++) w[i]=w[i]-(x/i)*w[x];
		for(int i=64;i>0;i--) w[i]+=w[i+1]; for(int i=1;i<=64;i++) ans=ans+1.0*w[i]/cnt[i];
		printf("%.6lf\n",ans);
	}
    return 0;
}