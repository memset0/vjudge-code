#include<bits/stdc++.h>
using namespace std;
const int N=1e6;
int T,n,p[N+10],cnt[N+10],lk[N+10],sz;
int main(){
#ifdef memset0
	freopen("K.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		sz=0;
		for(int i=1;i<=n;++i)cnt[i]=0;
		for(int i=2;i<=n;++i)cin>>p[i],++cnt[p[i]];
		for(int i=1;i<=n;++i)if(!cnt[i]){
			if(cnt[p[i]]>1){
				cout<<"Takeru\n";
				goto Skip;
			}
			lk[++sz]=1;
			for(int j=p[i];cnt[p[j]]==1;j=p[j])++lk[sz];
			if(lk[sz]==n-1){
				cout<<((n&1)?"Takeru\n":"Meiya\n");
				goto Skip;
			}
		}
		for(int i=1;i<=sz;++i)if(!(lk[i]&1)){
			cout<<"Takeru\n";
			goto Skip;
		}
		cout<<"Meiya\n";
		Skip:;
	}
	return 0;
}