#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int n,m;
long long ans;
struct node{
	int x,y;
}a[N],b[N],ta[N],tb[N];
inline long long cross(int i,int j){
	return (long long)(b[j].x-a[i].x)*(b[j].y-a[i].y);
}
void solve(int al,int ar,int bl,int br){
	if(al>ar||bl>br)return;
	if(al==ar){
		for(int i=bl;i<=br;i++)ans=max(ans,cross(al,i));
		return;
	}
	int am=(al+ar)>>1,bm=-1;
	long long mx=-LLONG_MAX;
	for(int i=bl;i<=br;i++){
		long long cur=cross(am,i);
		if(cur>mx)mx=cur,bm=i;
	}
	ans=max(ans,mx);
	solve(al,am-1,bl,bm);
	solve(am+1,ar,bm,br);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int tn,tm;cin>>tn>>tm;
	for(int i=1;i<=tn;i++)cin>>ta[i].x>>ta[i].y;
	for(int i=1;i<=tm;i++)cin>>tb[i].x>>tb[i].y;
	sort(ta+1,ta+tn+1,[](const node &a,const node &b){
		return a.x==b.x?a.y<b.y:a.x<b.x;
	});
	sort(tb+1,tb+tm+1,[](const node &a,const node &b){
		return a.x==b.x?a.y>b.y:a.x>b.x;
	});
	for(int i=1;i<=tn;i++)if(i==1||ta[i].y<a[n].y)a[++n]=ta[i];
	for(int i=1;i<=tm;i++)if(i==1||tb[i].y>b[m].y)b[++m]=tb[i];
	reverse(b+1,b+m+1);
	solve(1,n,1,m);
	cout<<ans<<endl;
}