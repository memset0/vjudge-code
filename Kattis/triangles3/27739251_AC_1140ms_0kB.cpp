#include<bits/stdc++.h>
#define maxn 6005
#define maxm 12005
#define LL long long
using namespace std;
int n,m,U[maxn][maxm],D[maxn][maxm];
char a[maxn*2][maxm*2];
vector<int>G[maxm];
int arr[maxm];
void upd(int i,int v){for(;i;i-=i&-i) arr[i]+=v;}
int qsum(int i){int s=0;for(int lim=(m+1)/2;i<=lim;i+=i&-i) s+=arr[i];return s;}
int main()
{
	scanf("%d%d\n",&n,&m);
	for(int i=1;i<=2*n-1;i++) fgets(a[i]+1,2*m+1,stdin);
	LL ans=0;
	for(int i=1;i<=2*n-1;i+=2){
		int Mx=0;
		for(int j=i/2&1?3:1,L=0,k=1;j<=2*m-1;j+=4,k++){
			U[i][j] = a[i-1][j-1]=='\\' ? U[i-2][j-2]+1 : 0;
			D[i][j] = a[i-1][j+1]=='/' ? D[i-2][j+2]+1 : 0;
			L = a[i][j-1]=='-' ? L+1 : 0;
			ans += qsum(k-min(U[i][j],L));
			upd(k,1),G[k+D[i][j]].push_back(k),Mx=max(Mx,k+D[i][j]);
			while(!G[k].empty()) upd(G[k].back(),-1),G[k].pop_back();
		}
		for(int k=m/2+1;k<=Mx;k++) while(!G[k].empty()) upd(G[k].back(),-1),G[k].pop_back();
	}
	for(int i=2*n-1;i>=1;i-=2){
		int Mx=0;
		for(int j=i/2&1?3:1,L=0,k=1;j<=2*m-1;j+=4,k++){
			U[i][j] = a[i+1][j-1]=='/' ? U[i+2][j-2]+1 : 0;
			D[i][j] = a[i+1][j+1]=='\\' ? D[i+2][j+2]+1 : 0;
			L = a[i][j-1]=='-' ? L+1 : 0;
			ans += qsum(k-min(U[i][j],L));
			upd(k,1),G[k+D[i][j]].push_back(k),Mx=max(Mx,k+D[i][j]);
			while(!G[k].empty()) upd(G[k].back(),-1),G[k].pop_back();
		}
		for(int k=m/2+1;k<=Mx;k++) while(!G[k].empty()) upd(G[k].back(),-1),G[k].pop_back();
	}
	printf("%lld\n",ans);
}