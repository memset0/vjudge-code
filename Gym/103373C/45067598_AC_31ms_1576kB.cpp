#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int n,a[N],s[N];
long long ans;
inline void add(int k,int x){
	for(;k<N;k+=k&-k)s[k]+=x;
}
inline int ask(int k){
	int r=0;
	for(;k;k-=k&-k)r+=s[k];
	return r;
}
int main(){
#ifdef memset0
	freopen("C.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=n;i>=1;i--){
		ans+=ask(a[i]);
		add(a[i],1);
	}
	cout<<ans<<endl;
}