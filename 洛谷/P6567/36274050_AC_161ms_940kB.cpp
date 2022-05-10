#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
const int N=210,M=5e5+10;
int n,m;
std::bitset<M> ans;
void play(int x){
	// printf("play %d\n",x);
	if(x>=M)return;
	ans|=ans<<x;
}
int main(){
#ifdef memset0
	freopen("C.in","r",stdin);
#else
// 	freopen("watch.in","r",stdin),freopen("watch.out","w",stdout);
#endif
	scanf("%d%d",&n,&m),ans.set(0);
	for(int i=1,k,a,h;i<=n;i++){
		scanf("%d%d",&k,&a),h=0;
		for(int i=1;i<=a;i<<=1)if(a&i)h=i;
		for(int i=1;i<h;i<<=1)play(k*i);
		play(k*(a-h+1));
	}
	for(int i=1,x;i<=m;i++)scanf("%d",&x),puts(ans[x]?"Yes":"No");
}