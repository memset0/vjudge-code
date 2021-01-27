#include<bits/stdc++.h>
using namespace std;
const int N=2e3+7;
int t,sum,ans[N]; bool fl[N];
int main(){
	cin>>t;
	while(t--){
		int n,p; cin>>n,p=n+1,sum=0;
		for(int i=2;i<p;i++){
			memset(fl,0,sizeof(fl));
			int u=1; int tg=0;
			for(int x=1;x<p;x++) fl[u]=1,u=u*i%p;
			for(int x=1;x<p;x++) if(!fl[x]) tg=1;
			if(tg==1) continue;
			sum=i; break;
		}
		ans[1]=1;
		for(int i=2;i<=n;i++) ans[i]=ans[i-1]*sum%p;
		for(int i=1;i<=n;i++) printf("%d %d\n",ans[i],i);
	}
}