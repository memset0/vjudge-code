#include<bits/stdc++.h>
using namespace std;
const int N=1e7;
int a,b,n,nxt[N+10],ls;
long long ans;
string s;
int main(){
#ifdef memset0
	freopen("J.in","r",stdin);
#endif
	cin.sync_with_stdio(0),cin.tie(0);
	cin>>a>>b,getline(cin,s);
	getline(cin,s);
	n=s.size();
	reverse(s.begin(),s.end());
	nxt[0]=-1;
	ans=a-b;
	ls=-1;
	for(int i=1;i<n;++i){
		if(s[i]=='.')break;
		while(ls>=0&&s[i]!=s[ls+1])ls=nxt[ls];
		if(s[ls+1]==s[i])nxt[i]=++ls;
		else nxt[i]=-1;
		//cout<<"NXT="<<nxt[i]<<"\n";
		ans=max(ans,1ll*a*(i+1)-1ll*b*(i-nxt[i]));
		//cout<<"i="<<i<<" ans="<<ans<<"\n";
	}
	cout<<ans;
	return 0;
}