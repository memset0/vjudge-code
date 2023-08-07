#include<bits/stdc++.h>
using namespace std;
const int INF=1e9+10;
int n,B,C,p[100010],c[100010],lg[100010],mn[20][100010],nw,nl,tmp;
int Min(int l,int r){
	if(l>r)return INF;
	int k=lg[r-l+1];
	return min(mn[k][l],mn[k][r-(1<<k)+1]);
}
int main(){
	scanf("%d%d%d",&n,&B,&C);
	for(int i=2;i<=n;++i)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;++i)scanf("%d%d",&p[i],&c[i]),mn[0][i]=c[i];
	for(int i=1;i<=lg[n];++i)for(int j=1;j+(1<<i)-1<=n;++j)mn[i][j]=min(mn[i-1][j],mn[i-1][j+(1<<i-1)]);
	nw=0,nl=1;
	for(int i=1;i<=nl;++i){
		//cout<<"I="<<i<<"\n";
		if(Min(i+1,nl)<=c[i])continue;
		while(nl+1<=n&&B>=1ll*(p[nl+1]-nw)*c[i]&&p[nl+1]-p[i]<=C){
			++nl,B-=(p[nl]-nw)*c[i],nw=p[nl];
			if(c[nl]<=c[i])break;
		}
		//cout<<"B="<<B<<" nw="<<nw<<"\n";
		if(Min(i+1,nl)>c[i]){
			tmp=min(nw+B/c[i],p[i]+C);
			B-=c[i]*(tmp-nw),nw=tmp;
		}
	}
	printf("%d",nw);
	return 0;
}