#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define debug(x) cerr<<#x<<": "<<x<<endl
using namespace std;
using ll=long long;
using lf=long double;
const int N=5e5;
int T,n,fl,cnt,sz1,sz2;
long long a[N+10],ta[N+10],ans,s1,s2,mx;
int main(){
#ifdef memset0
	freopen("F.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		mx=0;
		for(int i=1;i<=n;++i)cin>>a[i],mx=max(mx,a[i]);
		sort(a+1,a+n+1);
		ans=1ll*n*(n-1)*(n-2)/3;
		//cout<<"----------------------ANS="<<ans<<"\n";
		fl=-1;
		for(long long i=0;i<=mx;(i=(i<<1)+1),fl=-fl){
			//cout<<"-------------------i="<<i<<"\n";
			if(i){
				sz1=sz2=0;
				for(int j=1;j<=n;++j)ta[j]=a[j],sz2+=!(ta[j]&((i>>1)+1));
				for(int j=1;j<=n;++j){
					//cout<<"="<<ta[j]<<"\n";
					if(ta[j]&((i>>1)+1))a[++sz2]=ta[j];
					else a[++sz1]=ta[j];
				}
				//for(int j=1;j<=n;++j)cout<<a[j]<<" \n"[j==n];
			}
			s1=s2=0;
			cnt=0;
			for(int j=1;j<=n;++j){
				ta[j]=(a[j]&i);
				//cout<<"-----j="<<j<<"\n";
				if(a[j]!=a[j-1]){
					//cout<<"DO "<<a[j-1]<<" cnt="<<cnt<<"\n";
					//cout<<"("<<s1<<","<<s2<<"\n";
					ans+=fl*(s1*(1ll*cnt*cnt-(cnt<<1))+s2*cnt);
					s1+=cnt,s2+=1ll*cnt*cnt;
					if(!i)ans-=1ll*cnt*(cnt-1)*(cnt-2)/3;
					cnt=1;
					//cout<<"ANS="<<ans<<"\n";
				}else ++cnt;
				if((a[j]&i)!=(a[j-1]&i)){
					//cout<<a[j]<<" and "<<a[j-1]<<"\n";
					s1=s2=0;
				}
			}
			//cout<<"DO "<<a[n]<<",cnt="<<cnt<<"\n";
			//cout<<"("<<s1<<","<<s2<<"\n";
			ans+=fl*(s1*(1ll*cnt*cnt-(cnt<<1))+s2*cnt);
			if(!i)ans-=1ll*cnt*(cnt-1)*(cnt-2)/3;
			//cout<<"ans="<<ans<<"\n";
		}
		cout<<(ans>>1)<<"\n";
	}
	return 0;
}