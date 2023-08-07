#include<bits/stdc++.h>
using namespace std;
int n,tx,ty,mxx,mnx,mxy,mny;
int main(){
	scanf("%d",&n);
	mxx=mxy=-1e6,mnx=mny=1e6;
	for(int i=1;i<=n;++i)scanf("%d%d",&tx,&ty),mxx=max(mxx,tx),mnx=min(mnx,tx),mxy=max(mxy,ty),mny=min(mny,ty);
	printf("%d %d",(mxx-mnx+1)>>1,(mxy-mny+1)>>1);
	return 0;
}