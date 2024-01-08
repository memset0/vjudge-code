#include<bits/stdc++.h>
using namespace std;
const int N=400,mod=167772161;
int n,K,F[N+5][N+5],tt,a[N+10],ans;
void Ins(int x){
	++tt;
	for(int i=tt;i>0;--i)for(int j=x;j<=K;++j){
		(F[i][j]+=F[i-1][j-x])>=mod?F[i][j]-=mod:0;
	}
}
void Del(int x){
	for(int i=1;i<=tt;++i)for(int j=x;j<=K;++j){
		(F[i][j]-=F[i-1][j-x])<0?F[i][j]+=mod:0;
	}
	--tt;
}
int main(){
	scanf("%d%d",&n,&K);
	F[0][0]=1;
	for(int i=1;i<=n;++i)scanf("%d",&a[i]),Ins(a[i]);
	for(int i=1;i<=n;++i){
		Del(a[i]);
		for(int j=1;j<n;++j){
			ans=0;
			for(int k=K-a[i]+1;k<=K;++k)(ans+=F[j][k])>=mod?ans-=mod:0;
			printf("%d%c",ans," \n"[j==n-1]);
		}
		Ins(a[i]);
	}
	return 0;
}