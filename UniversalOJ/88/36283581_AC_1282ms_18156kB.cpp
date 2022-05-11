#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; char c=getchar(); bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void readAlpha(T &x){
	x=getchar();
	while(!isalpha(x))x=getchar();
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=1e5+10;
int n,m,a[N];
struct line{
	long long s;
	int k;
	inline void travel(int x){s+=(long long)k*x;}
};
inline int beat_min(const line &x,const line &y){
	if(x.k>=y.k)return 1<<30;
	return std::min(1ll<<30,(x.s-y.s)/(y.k-x.k)+1);
}
inline int beat_max(const line &x,const line &y){
	if(x.k<=y.k)return 1<<30;
	return std::min(1ll<<30,(y.s-x.s)/(x.k-y.k)+1);
}
struct segment{
	int l,r,mid,rem,tag;
	line min,max;
}p[N<<2];
void debug(){
	for(int u=1;u<=(n<<2);u++)if(p[u].mid)
		printf("> %d %d %d %d [%lld %d] [%lld %d]\n",p[u].l,p[u].r,p[u].rem,p[u].tag,p[u].min.s,p[u].min.k,p[u].max.s,p[u].max.k);
}
void pushup(int u,int x){
	p[u].min.travel(x);
	p[u].max.travel(x);
	p[u].tag+=x;
	p[u].rem-=x;
}
void pushdown(int u){
	if(!p[u].tag||p[u].l==p[u].r)return;
	pushup(u<<1,p[u].tag);
	pushup(u<<1|1,p[u].tag);
	p[u].tag=0;
}
void maintain(int u){
	p[u].rem=std::min(p[u<<1].rem,p[u<<1|1].rem);
	if(p[u<<1].min.s<p[u<<1|1].min.s){
		p[u].min=p[u<<1].min;
		p[u].rem=std::min(p[u].rem,beat_min(p[u<<1|1].min,p[u<<1].min));
	}else{
		p[u].min=p[u<<1|1].min;
		p[u].rem=std::min(p[u].rem,beat_min(p[u<<1].min,p[u<<1|1].min));
	}
	if(p[u<<1].max.s>p[u<<1|1].max.s){
		p[u].max=p[u<<1].max;
		p[u].rem=std::min(p[u].rem,beat_max(p[u<<1|1].max,p[u<<1].max));
	}else{
		p[u].max=p[u<<1|1].max;
		p[u].rem=std::min(p[u].rem,beat_max(p[u<<1].max,p[u<<1|1].max));
	}
}
void update(int u){
	if(p[u].rem>0)return;
	// if(p[u].l==p[u].r)return;
	pushdown(u);
	update(u<<1);
	update(u<<1|1);
	maintain(u);
}
void build(int u,int l,int r){
	p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
	if(l==r){
		p[u].min=p[u].max=(line){(long long)a[l],0};
		p[u].rem=1<<30;
		return;
	}
	build(u<<1,l,p[u].mid);
	build(u<<1|1,p[u].mid+1,r);
	maintain(u);
}
void modify(int u,int k,int x){
	pushdown(u);
	if(p[u].l==p[u].r){
		p[u].min.k=p[u].max.k=x;
		p[u].rem=1<<30;
		return;
	}
	modify(k<=p[u].mid?u<<1:u<<1|1,k,x);
	maintain(u);
}
int main(){
#ifdef Ciel
	freopen("1.in","r",stdin);
#endif
	read(n),read(m);
	for(int i=1;i<=n;i++)read(a[i]);
	build(1,1,n);
	for(int t,c,k,x,lst=0,i=1;i<=m;i++){
		read(t),readAlpha(c);
		pushup(1,t-lst),lst=t;
		update(1);
		// printf("%d %c\n",t,c);
		if(c=='c'){
			read(k),read(x);
			modify(1,k,x);
		}else{
			print(std::max(p[1].max.s,-p[1].min.s),'\n');
		}
		// debug();
	}
}