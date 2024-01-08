#include<bits/stdc++.h>
using namespace std;
const int N=2e3;
struct frac{
	int x,y;
	bool operator<(const frac&t)const{
		return x==t.x?y<t.y:x<t.x;
	}
	bool operator==(const frac&t)const{
		return x==t.x&&y==t.y;
	}
	frac operator~()const{
		int t=__gcd(abs(x),abs(y));
		if(y<0||(y==0&&x<0))return(frac){-x/t,-y/t};
		return(frac){x/t,y/t};
	}
	frac operator-()const{
		return x<=0?(frac){y,-x}:(frac){-y,x};
	}
	long long out(){
		return 2000000000ll*x+y;
	}
}tmp;
int n,q,xi[N+10],yi[N+10],qx,qy,ans;
unordered_map<long long,int>cnt[N+10];
frac Calc(int x,int y,int tx,int ty){
	//cout<<"CALC "<<x<<" "<<y<<" "<<tx<<" "<<ty<<"\n";
	return(frac){x-tx,y-ty};
}
int main(){
#ifdef memset0
	freopen("A.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;++i){
		cin>>xi[i]>>yi[i];
	}
	for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)if(i!=j){
		++cnt[i][(~Calc(xi[i],yi[i],xi[j],yi[j])).out()];
		//cout<<"i="<<i<<" j="<<j<<"\n";
		//tmp=~Calc(xi[i],yi[i],xi[j],yi[j]);
		//cout<<"("<<tmp.x<<","<<tmp.y<<")\n";
	}
	//cout<<"----------------\n";
	while(q--){
		ans=0;
		cin>>qx>>qy;
		cnt[n+1].clear();
		for(int i=1;i<=n;++i){
			++cnt[n+1][(~Calc(qx,qy,xi[i],yi[i])).out()];
			//tmp=~Calc(qx,qy,xi[i],yi[i]);
			//cout<<"("<<tmp.x<<","<<tmp.y<<")\n";
		}
		for(int i=1;i<=n;++i){
			tmp=~Calc(qx,qy,xi[i],yi[i]);
			//cout<<"i="<<i<<" tmp=("<<tmp.x<<","<<tmp.y<<")\n";
			ans+=cnt[n+1][(-tmp).out()]+(cnt[i][(-tmp).out()]<<1);
			//cout<<"ANS="<<ans<<"\n";
		}
		//cout<<"ANS="<<ans<<"\n";
		cout<<(ans>>1)<<"\n";
	}
}