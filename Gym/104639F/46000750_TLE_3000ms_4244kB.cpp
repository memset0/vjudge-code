#include<bits/stdc++.h>
using namespace std;
const int N=5e5+9;
int T,n;
long long a[N];
map<pair<long long,long long>,bool> mp;
bool check(long long x,long long y,long long z,int t=0){
	// fprintf(stderr,"![%d] %lld %lld %lld\n",t,x,y,z);
	if(x>y)swap(x,y);
	if(x>z)swap(x,z);
	if(y>z)swap(y,z);
	y-=x,z-=x,x=0;
	auto it=mp.find(make_pair(y,z));
	if(it!=mp.end()){
		return it->second;
	}
	bool win=false;
	for(int i=1;i<=z&&!win;i++){
		// fprintf(stderr,"![%d] %lld %lld %lld >> %d\n",t,x,y,z,i);
		if(x+i<=y-i&&!check(x+i,y-i,z,t+1))win=true;
		if(x+i<=z-i&&!check(x+i,y,z-i,t+1))win=true;
		if(y+i<=z-i&&!check(x,y+i,z-i,t+1))win=true;
	}
	return mp[make_pair(y,z)]=win;
}
int main(){
#ifdef memset0
	freopen("F.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	// for(int x=0;x<=30;x++){
	// 	for(int y=0;y<=30;y++){
	// 		cerr<<check(0,x,y)<<" ";
	// 	}
	// 	cerr<<endl;
	// }
	// for(int x=0;x<=100;x++)
	// 	if(!check(0,0,x)){
	// 		assert(!check(0,x,x));
	// 		if(x%2==0)cerr<<"! "<<x<<endl;
	// 	}
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		int ans=0;
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				for(int k=j+1;k<=n;k++){
					ans+=check(a[i],a[j],a[k]);
				}
		cout<<ans<<endl;
	}
}