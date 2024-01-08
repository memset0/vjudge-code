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
const int N=2e5+10;
int n,m,a[N],b[N],pre[N],s[N];
struct segment{
	int l,r,mid,val;
	long long sum;
}p[N<<2];
void build(int u,int l,int r){
	p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
	if(l==r){
		p[u].val=s[l];
		p[u].sum=(long long)s[l]*l;
		return;
	}
	build(u<<1,l,p[u].mid);
	build(u<<1|1,p[u].mid+1,r);
	p[u].val=p[u<<1].val+p[u<<1|1].val;
	p[u].sum=p[u<<1].sum+p[u<<1|1].sum;
}
void modify(int u,int k,int x){
	if(p[u].l==p[u].r){
		p[u].val+=x;
		p[u].sum+=x*p[u].l;
		return;
	}
	modify(k<=p[u].mid?u<<1:u<<1|1,k,x);
	p[u].val=p[u<<1].val+p[u<<1|1].val;
	p[u].sum=p[u<<1].sum+p[u<<1|1].sum;
	// printf("[%d %d] => %d %d\n",p[u].l,p[u].r,p[u].val,p[u].sum);
}
long long query(int u,int l,int r,int c){
	// printf("query %d(%d %d) %d %d %d => %d %d\n",u,p[u].l,p[u].r,l,r,c,p[u].val,p[u].sum);
	if(p[u].l==l&&p[u].r==r)return p[u].sum-(long long)p[u].val*c;
	if(r<=p[u].mid)return query(u<<1,l,r,c);
	if(l>p[u].mid)return query(u<<1|1,l,r,c);
	return query(u<<1,l,p[u].mid,c)+query(u<<1|1,p[u].mid+1,r,c);
}
int main(){
#ifdef memset0
	freopen("bubble.in","r",stdin);
#else
	// freopen("bubble.in","r",stdin),freopen("bubble.out","w",stdout);
#endif
	read(n),read(m);
	for(int i=1;i<=n;i++){
		read(a[i]),b[i]=i-1;
		for(int k=a[i];k;k-=k&-k)b[i]-=pre[k];
		for(int k=a[i];k<=n;k+=k&-k)pre[k]++;
	}
	for(int i=1;i<=n;i++)s[b[i]]++;
	build(1,0,n);
	for(int o,k,i=1;i<=m;i++)if(read(o),read(k),o==1){
		std::swap(b[k],b[k+1]);
		if(a[k]<a[k+1]){ // b[k+1]++
			modify(1,b[k+1],-1);
			modify(1,++b[k+1],1);
		}else{ // b[k]--
			modify(1,b[k],-1);
			modify(1,--b[k],1);
		}
		std::swap(a[k],a[k+1]);
		// for(int i=1;i<=n;i++)printf("%d%c",b[i]," \n"[i==n]);
	}else{
		long long res=k>=n?0:query(1,k+1,n,k);
		print(res),putchar('\n');
	}
}