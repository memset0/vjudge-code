#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=1e5+5e4+10;
int n,m,t,k,a[N];
struct atom{
	int x,v;
	inline bool operator<(const atom &other)const{
		return v==other.v?x<other.x:v<other.v;
	}
};
inline std::vector<atom> merge(const std::vector<atom> &a,std::vector<atom> b){
	for(int fl,i=0;fl=0,i<a.size();i++){
		for(int j=0;j<b.size();j++)if(a[i].x==b[j].x){fl=1,b[j].v+=a[i].v;break;}
		if(!fl){
			b.push_back(a[i]);
			if(b.size()>k){
				int min=1000000000;std::vector<atom> c;
				for(int i=0;i<b.size();i++)min=std::min(min,b[i].v);
				for(int i=0;i<b.size();i++)if(b[i].v-=min)c.push_back(b[i]);
				b=c;
			}
		}
	}
	return b;
}
struct node{
	int l,r,mid,tag;
	std::vector<atom> res;
}p[N<<2];
void pushup(int u,int x){
	p[u].tag=x;
	p[u].res=std::vector<atom>{(atom){x,p[u].r-p[u].l+1}};
}
void pushdown(int u){
	if(p[u].l==p[u].r||p[u].tag==-1)return;
	pushup(u<<1,p[u].tag),pushup(u<<1|1,p[u].tag),p[u].tag=-1;
}
void build(int u,int l,int r){
	p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1,p[u].tag=-1;
	if(l==r){pushup(u,a[l]);return;}
	build(u<<1,l,p[u].mid),build(u<<1|1,p[u].mid+1,r);
	p[u].res=merge(p[u<<1].res,p[u<<1|1].res);
}
void modify(int u,int l,int r,int x){
	pushdown(u);
	if(p[u].l==l&&p[u].r==r){pushup(u,x);return;}
	if(r<=p[u].mid)modify(u<<1,l,r,x);
	else if(l>p[u].mid)modify(u<<1|1,l,r,x);
	else modify(u<<1,l,p[u].mid,x),modify(u<<1|1,p[u].mid+1,r,x);
	p[u].res=merge(p[u<<1].res,p[u<<1|1].res);
}
std::vector<atom> query(int u,int l,int r){
	pushdown(u);
	if(p[u].l==l&&p[u].r==r)return p[u].res;
	if(r<=p[u].mid)return query(u<<1,l,r);
	if(l>p[u].mid)return query(u<<1|1,l,r);
	return merge(query(u<<1,l,p[u].mid),query(u<<1|1,p[u].mid+1,r));
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),read(m),read(t),k=100/t;
	for(int i=1;i<=n;i++)read(a[i]);
	build(1,1,n);
	for(int op,l,r,x,i=1;i<=m;i++)
		if(read(op),read(l),read(r),op==1){
			read(x),modify(1,l,r,x);
		}else{
			std::vector<atom> res=query(1,l,r);print(res.size(),' ');
			for(int i=0;i<res.size();i++)print(res[i].x," \n"[i==res.size()-1]);
		}
}