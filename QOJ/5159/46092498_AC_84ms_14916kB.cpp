#include<bits/stdc++.h>
using namespace std;
const int N=2e5;
struct inte{
	int l,r,id;
	bool operator<(const inte&y)const{
		return l==y.l?(r>y.r):(l<y.l);
	}
}ar[N+10];
struct val{
	int v,*pos;
	bool operator<(const val&y)const{
		return v<y.v;
	}
}v[(N<<1)+10];
int n,a,t,sz,num,mx[(N<<1)+10];
int prt[N+10];
void Ins(int x,int v){
	while(x<=num)mx[x]=max(mx[x],v),x+=(x&-x);
}
int Que(int x){
	int ret=0;
	while(x)ret=max(ret,mx[x]),x-=(x&-x);
	return ret;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d%d",&a,&t);
		v[++sz]=(val){a,&ar[i].l},v[++sz]=(val){a+t,&ar[i].r};
		ar[i].id=i;
	}
	sort(v+1,v+sz+1);
	for(int i=1;i<=sz;++i)num+=(v[i].v!=v[i-1].v),(*v[i].pos)=num;
	sort(ar+1,ar+n+1);
	for(int i=1;i<=n;++i){
		prt[ar[i].id]=Que(num-ar[i].r+1);
		Ins(num-ar[i].r+1,prt[ar[i].id]+1);
	}
	for(int i=1;i<=n;++i)printf("%d%c",prt[i]," \n"[i==n]);
	return 0;
}
/*
4
2 8
1 7
4 5
5 2

5
2 4
3 3
2 2
4 2
4 1
*/