#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=1e5+10,M=N<<5;
int n,l,r,y,rt,nod,x[N],v[N],h[N],sum[M],lc[M],rc[M],ans[N];
void modify(int &u,int ql,int qr,int l,int r){
	if(!u)u=++nod;
	if(ql==l&&qr==r)return void(sum[u]++);
	// printf("modify %d[%d] %d %d %d %d\n",u,sum[u],ql,qr,l,r);
	int mid=(l+r)>>1;
	if(qr<=mid)return modify(lc[u],ql,qr,l,mid);
	if(ql>mid)return modify(rc[u],ql,qr,mid+1,r);
	modify(lc[u],ql,mid,l,mid),modify(rc[u],mid+1,qr,mid+1,r);
}
void dfs(int u,int c,int l,int r){
	if(!u)return;
	ans[c]-=r-l+1;
	ans[c+=sum[u]]+=r-l+1;
	int mid=(l+r)>>1;
	dfs(lc[u],c,l,mid);
	dfs(rc[u],c,mid+1,r);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(l),read(r),read(y);
	for(int i=1;i<=n;i++){
		read(x[i]),read(v[i]),read(h[i]);
		long long d=((long long)y*h[i]+v[i]-1)/v[i]-1;
		// printf("%d : %lld : %lld %lld\n",x[i],d,x[i]-d,x[i]+d);
		modify(rt,std::max(x[i]-d,(long long)l),std::min((long long)r,x[i]+d),l,r);
	}
	ans[0]=r-l+1,dfs(rt,0,l,r);
	for(int i=1;i<=n;i++)ans[i]+=ans[i-1];
	for(int i=0;i<=n;i++)print(ans[i],'\n');
}