#include<bits/stdc++.h>
using namespace std;
struct que{
	int k,id;
	bool operator<(const que&y)const{
		return k<y.k;
	}
}ar[100010];
int n,Q,a[100010],nw,prt[100010];
int main(){
	scanf("%d%d",&n,&Q);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=Q;++i)scanf("%d",&ar[i].k),ar[i].id=i;
	sort(ar+1,ar+Q+1);
	a[0]=-1,nw=1;
	for(int i=1;i<=n;++i){
		while(nw<=Q&&a[i]-i+1>=ar[nw].k)prt[ar[nw].id]=ar[nw].k+i-2,++nw;
	}
	for(int i=nw;i<=Q;++i)prt[ar[i].id]=ar[i].k+n-1;
	for(int i=1;i<=Q;++i)printf("%d%c",prt[i]," \n"[i==Q]);
	return 0;
}