#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int T,n,a[N+10],t,cnt[35],ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=32;++i)cnt[i]=0;
		for(int i=1;i<=n;++i){
			scanf("%d",&a[i]);
			t=0;
			while(a[i]>=(1ll<<t))++t;
			++cnt[t];
		}
		ans=0;
		for(int i=1;i<=32;++i)ans=max(ans,cnt[i]);
		printf("%d\n",ans);
	}
	return 0;
}
/*
3
3
1 2 3
3
1 1 1
5
1 2323 534 534 5
*/