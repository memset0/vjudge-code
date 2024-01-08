#include<bits/stdc++.h>

// #define log(...) (void(0))
#define log(...) fprintf(stderr,__VA_ARGS__)
#define debug log("\33[2mPassing [%s] in LINE %d\33[0m\n",__FUNCTION__,__LINE__);

const int S=1<<21; char ibuf[S],*iS,*iT,obuf[S],*oS=obuf,*oT=oS+S-1;
#define flush() (fwrite(obuf,1,oS-obuf,stdout),oS=obuf,void())
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,S,stdin),(iS==iT?EOF:*iS++)):*iS++)
#define putchar(x) (*oS++=(x),oS==oT?flush():void())
struct Flusher_{~Flusher_(){flush();}}flusher_;

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

const int N=1e6+10,mod=1e9+7;
int n,tn,sum,ans,a[N],ta[N],pre[N],lst[N];

inline int inc(int a,int b){return (a+=b)>=mod?a-mod:a;}

struct node{
	int l,r,mid,tag;
	long long cnt,sum;
}p[N<<3];

inline void pushup(int u,long long x){
	p[u].sum+=(x<<1)*p[u].cnt+x*x*(p[u].r-p[u].l+1);
	p[u].cnt+=x*(p[u].r-p[u].l+1);
	p[u].tag+=x;
}

void build(int u,int l,int r){
	p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
	if(l==r)return;
	build(u<<1,l,p[u].mid);
	build(u<<1|1,p[u].mid+1,r);
}

void modify(int u,int l,int r,int x){
	if(p[u].tag)pushup(u<<1,p[u].tag),pushup(u<<1|1,p[u].tag),p[u].tag=0;
	if(p[u].l==l&&p[u].r==r){pushup(u,x);return;}
	if(r<=p[u].mid)modify(u<<1,l,r,x);
	else if(l>p[u].mid)modify(u<<1|1,l,r,x);
	else modify(u<<1,l,p[u].mid,x),modify(u<<1|1,p[u].mid+1,r,x);
	p[u].cnt=p[u<<1].cnt+p[u<<1|1].cnt;
	p[u].sum=p[u<<1].sum+p[u<<1|1].sum;
}

int main(){
	read(n);
	for(int i=1;i<=n;i++)read(a[i]),ta[i]=a[i];
	std::sort(ta+1,ta+n+1),tn=std::unique(ta+1,ta+n+1)-ta-1;
	for(int i=1;i<=n;i++)a[i]=std::lower_bound(ta+1,ta+n+1,a[i])-ta;
	for(int i=1;i<=n;i++)pre[i]=lst[a[i]],lst[a[i]]=i;
	// fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
	build(1,1,n);
	for(int i=1;i<=n;i++){
		// printf("%d [%d %d]\n",i,pre[i]+1,i);
		modify(1,pre[i]+1,i,1);
		// printf("> %d\n",p[1].sum);
		ans=(ans+p[1].sum)%mod;
	}
	print(ans,'\n');
	fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
}