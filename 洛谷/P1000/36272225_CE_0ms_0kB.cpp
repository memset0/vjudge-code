#include<bits/stdc++.h>
#define ll long long
// #define mod 

// input & output
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
template<class T> inline void print(T a,int l,int r){for(int i=l;i<=r;i++)print(a[i]," \n"[i==r]);}
template<class T1,class T2> inline void update_min(T1 &x,T2 y){if(y<x)x=y;}
template<class T1,class T2> inline void update_max(T1 &a,T2 y){if(y>x)x=y;}
// zint
#ifdef mod
struct z{
	int x;
	inline z(int x=0):x(x){}
};
inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
inline z opetator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
inline void read(z &x){read(x.x);}
inline void print(z x){print(x.x);}
#endif
// segment tree
// #define segment_tree "on"
#ifdef segment_tree
template<class T> struct segment_tree_base{
	struct node{int l,r,mid; T val,tag; bool has;};
};
template<class T> struct segment_tree_info_min:segment_tree_base<T>{
	inline void pushup(int u,T x){
		update_min(p[u].val,x);
		p[u].has?update_min(p[u].tag,x):(p[u].tag=x,p[u].has=true);
	}
	inline void pushdown(int u){
		if(!p[u].has||p[u].l==p[u].r)return;
		pushup(u<<1,p[u].tag),pushup(u<<1|1,p[u].tag),p[u].has=false;
	}
	inline void maintain(int u){
		p[u].val=p[u<<1].val,update_min(p[u].val,p[u<<1|1].val);
	}
};
template<class T> struct segment_tree_info_max:segment_tree_base<T>{
	inline void pushup(int u,T x){
		update_max(p[u].val,x);
		p[u].has?update_max(p[u].tag,x):(p[u].tag=x,p[u].has=true);
	}
	inline void pushdown(int u){
		if(!p[u].has||p[u].l==p[u].r)return;
		pushup(u<<1,p[u].tag),pushup(u<<1|1,p[u].tag),p[u].has=false;
	}
	inline void maintain(int u){
		p[u].val=p[u<<1].val,update_max(p[u].val,p[u<<1|1].val);
	}
};
template<class T> struct segment_tree_info_sum:segment_tree_base<T>{
	inline void pushup(int u,T x){
		p[u].sum=p[u].sum+x;
		p[u].tag=p[u].tag+x;
	}
	inline void pushdown(int u){
		if(!p[u].tag||p[u].l==p[u].r)return;
		pushup(u<<1,p[u].tag),pushup(u<<1|1,p[u].tag),p[u].tag=false;
	}
	inline void maintain(int u){
		p[u].val=p[u<<1].val+p[u<<1|1].val;
	}
};
template<class info,class T> struct segment_tree:info<T>{
	void build(int u,int l,int r,T x){
		p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1,p[u].val=x;
		if(l==r)return;
		build(u<<1,l,p[u].mid,x);
		build(u<<1|1,p[u].mid+1,r,x);
	}
	void modify(int u,int l,int r,T x){
		pushdown(u);
		if(p[u].l==l&&p[u].r==r)return pushup(u,x);
		if(r<=p[u].mid)modify(u<<1,l,r,x);
		else if(l>p[u].mid)modify(u<<1|1,l,r,x);
		else modify(u<<1,l,p[u].mid,x),modify(u<<1|1,p[u].mid+1,r,x);
		p[u].val=merge(p[u<<1].val,p[u<<1|1])
	}
	v
}
template<class T> struct min_segment_tree:segment_tree<segment_tree_info_min,T>{};
template<class T> struct max_segment_tree:segment_tree<segment_tree_info_max,T>{};
template<class T> struct sum_segment_tree:segment_tree<segment_tree_info_sum,T>{};
#endif
int main(){
	
}