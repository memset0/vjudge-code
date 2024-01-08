#include<bits/stdc++.h>
using namespace std;
using DP=array<long long,27>;
const int N=1e5+9;
int n,m,p,f[27],a[N];
inline int getc(){
	char c;
	do{cin>>c;}
	while(c!='?'&&!isupper(c));
	return c=='?'?0:(c-'A'+1);
}
inline void updmax(long long &x,long long y){
	if(y>x)x=y;
}
inline void updsum(long long &x,long long y){
	x=(x==-1||y==-1)?-1:(x+y);
}
DP solve(int s,int t){
	DP res;
	fill(res.begin(),res.end(),-1);
	if(t==n){
		if(a[s]){
			res[a[s]]=f[a[s]];
		}else{
			for(int i=1;i<=26;i++)res[i]=f[i];
		}
	}else{
		vector<DP> dp(p);
		for(int i=0;i<p;i++)dp[i]=solve(s+i*t,t*p);
		for(int i=0;i<=26;i++){
			res[i]=0;
			for(int j=0;j<p;j++)updsum(res[i],dp[j][i]);
			if(i&&res[i]!=-1){
				res[i]+=(long long)n/t*f[i];
			}
		}
	}
	for(int i=1;i<=26;i++)updmax(res[0],res[i]);
	// fprintf(stderr,"s=%d t=%d :: ",s,t);
	// for(int i=0;i<=3;i++)cerr<<res[i]<<" \n"[i==3];
	return res;
}
int main(){
#ifdef memset0
	freopen("C.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=0;i<n;i++)a[i]=getc();
	cin>>m;
	memset(f,-1,sizeof(f));
	for(int x,v,i=0;i<m;i++){
		x=getc();
		cin>>v;
		f[x]=max(f[x],v);
	}
	if(n==1){
		if(a[0]){
			cout<<f[a[0]]<<endl;
		}else{
			int ans=0;
			for(int i=1;i<=26;i++)ans=max(ans,f[i]);
			cout<<ans<<endl;
		}
		return 0;
	}
	for(p=2;p<=n;p++)
		if(n%p==0){
			break;
		}
	auto ans=solve(0,1);
	cout<<ans[0]<<endl;
}