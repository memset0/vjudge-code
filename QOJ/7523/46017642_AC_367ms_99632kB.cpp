#include<bits/stdc++.h>
#define pi pair<int,int>
#define a second
#define b first
using namespace std;
const int N=2e5,T=20;
const long long INF=1e18;
struct node{
	int lc,rc,num;
	long long sum;
}t[N*T+10];
struct Val{
	int v,*pos;
	bool operator<(const Val&y)const{
		return v<y.v;
	}
}ar[N+10];
int n,mp[N+10],rt[N+10],cnt,num;
pi p[N+10];
void Build(int lx,int&x,int l,int r,int v){
	x=++cnt;
	t[x].num=t[lx].num+1,t[x].sum=t[lx].sum+mp[v];
	if(l==r)return;
	int mid=(l+r>>1);
	if(v<=mid)t[x].rc=t[lx].rc,Build(t[lx].lc,t[x].lc,l,mid,v);
	else t[x].lc=t[lx].lc,Build(t[lx].rc,t[x].rc,mid+1,r,v);
}
long long Que(int x,int l,int r,int qn){
	if(l==r)return 1ll*qn*mp[l];
	//cout<<"QUE "<<x<<"["<<l<<","<<r<<"] qn="<<qn<<",num="<<t[x].num<<"\n";
	int mid=(l+r>>1);
	//cout<<"LN="<<t[t[x].lc].num<<"\n";
	if(t[t[x].lc].num>=qn)return Que(t[x].lc,l,mid,qn);
	return Que(t[x].rc,mid+1,r,qn-t[t[x].lc].num)+t[t[x].lc].sum;
}
void Solve(int l,int r,int ql,int qr){
	if(l>r)return;
	//cout<<"SOLVE "<<l<<" "<<r<<" "<<ql<<" "<<qr<<"\n";
	int mid=(l+r>>1);
	long long tans=INF,tmp,ti;
	for(int i=max(mid,ql);i<=qr;++i){
		//cout<<"I="<<i<<"\n";
		if((tmp=Que(rt[i],1,num,mid)+p[i].b)<tans){
			//cout<<"I="<<i<<" tmp="<<tmp<<"\n";
			tans=tmp,ti=i;
		}
		//cout<<"TMP="<<tmp<<"\n";
	}
	//cout<<"MID="<<mid<<" ti="<<ti<<"\n";
	Solve(l,mid-1,ql,ti);
	printf("%lld\n",tans);
	Solve(mid+1,r,ti,qr);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d%d",&p[i].a,&p[i].b);
	sort(p+1,p+n+1);
	for(int i=1;i<=n;++i)ar[i]=(Val){p[i].a,&p[i].a};
	sort(ar+1,ar+n+1);
	for(int i=1;i<=n;++i)num+=(ar[i].v!=ar[i-1].v),mp[num]=ar[i].v,(*ar[i].pos)=num;
	rt[0]=cnt=1;
	for(int i=1;i<=n;++i)Build(rt[i-1],rt[i],1,num,p[i].a);
	//cout<<"\n\n";
	//for(int i=1;i<=n;++i)cout<<mp[p[i].a]<<"("<<p[i].a<<")"<<" "<<p[i].b<<"\n";
	Solve(1,n,1,n);
	return 0;
}
/*
5
1145 1 
1145 2
1145 3
1145 4
1 5
*/