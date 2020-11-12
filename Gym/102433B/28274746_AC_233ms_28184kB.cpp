#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct seg{
	int L,R,mn;
}a[200010*8];int v[200010],n,m,k;
int Min(int x,int y){
	if(v[x]<=v[y])return x;
	else return y;
}
vector<int>e[200010];
void build(int x,int L,int R){
	a[x].L=L;a[x].R=R;
	if(L==R)return a[x].mn=L,void();
	int mid=L+R>>1;
	build(x<<1,L,mid);build(x<<1|1,mid+1,R);
	a[x].mn=Min(a[x<<1].mn,a[x<<1|1].mn);
}
int query(int x,int L,int R){
	if(a[x].L>R||a[x].R<L)return n+1;
	if(L<=a[x].L&&R>=a[x].R)return a[x].mn;
	return Min(query(x<<1,L,R),query(x<<1|1,L,R));
}
void change(int x,int pl){
	if(a[x].L>pl||a[x].R<pl)return;
	if(a[x].L==pl&&a[x].R==pl)return;
	change(x<<1,pl);change(x<<1|1,pl);
	a[x].mn=Min(a[x<<1].mn,a[x<<1|1].mn);
}
bool vis[200010];
int gg[200010],to[200010];
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)scanf("%d",&v[i]),e[v[i]].push_back(i);v[n+1]=998244353;
	build(1,1,n); 
	for(int i=n;i>=1;i--){
		if(!vis[v[i]])gg[i]=1,to[v[i]]=i;
		vis[v[i]]=1;
	}
	for(int i=1,ret=1,t=0;i<=n&&ret<=k;ret++){
		if(i>t||!gg[t]){
			t++;
			while(!gg[t])t++;
		}
		int d=query(1,i,t);gg[to[v[d]]]=0;i=d+1;cout<<v[d]<<' ';
		for(auto j:e[v[d]]){
			v[j]=n+1;
			change(1,j);
		}
		
		
	}
	return 0;
}
