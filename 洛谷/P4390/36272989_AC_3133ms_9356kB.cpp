#include<bits/stdc++.h>
#define ll long long
#define lc(u) (e[u].ch[0])
#define rc(u) (e[u].ch[1])
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=3e5+10;
int F,n,m,rt,nod;
struct node{int x,y;};
inline bool c0(const node &x,const node &y){return x.x==y.x?x.y<y.y:x.x<y.x;}
inline bool c1(const node &x,const node &y){return x.y==y.y?x.x<y.x:x.y<y.y;}
bool (*cmp[2])(const node&,const node&)={c0,c1};
struct info{
	node x;ll w;int id;
	inline bool operator<(const info &other)const{return cmp[F](x,other.x);}
}stk[N];
struct matrix{
	node a,b;
	inline bool is_in(const matrix &other)const{return other.a.x<=a.x&&other.a.y<=a.y&&b.x<=other.b.x&&b.y<=other.b.y;}
	inline bool is_out(const matrix &other)const{return b.x<other.a.x||b.y<other.a.y||a.x>other.b.x||a.y>other.b.y;}
	inline void merge(const matrix &other){a.x=std::min(a.x,other.a.x),a.y=std::min(a.y,other.a.y),b.x=std::max(b.x,other.b.x),b.y=std::max(b.y,other.b.y);}
};
struct tree_node{
	ll sum,val; node x; matrix mat; int siz,ch[2];
}e[N];
inline void maintain(int u){
	e[u].mat={e[u].x,e[u].x};
	e[u].siz=e[lc(u)].siz+e[rc(u)].siz+1;
	e[u].sum=e[lc(u)].sum+e[rc(u)].sum+e[u].val;
	for(int i=0;i<2;i++)if(e[u].ch[i])e[u].mat.merge(e[e[u].ch[i]].mat);
}
void pia(int u,int k){
	if(lc(u))pia(lc(u),k);
	stk[k+e[lc(u)].siz]=(info){e[u].x,e[u].val,u};
	if(rc(u))pia(rc(u),k+e[lc(u)].siz+1);
}
int build(int l,int r,int fl){
	if(l>r)return 0;
	int mid=l+rand()%(r-l+1);
	F=fl,std::nth_element(stk+l,stk+mid,stk+r+1);
	int u=stk[mid].id;
	e[u].x=stk[mid].x,e[u].val=stk[mid].w;
	lc(u)=build(l,mid-1,fl^1),rc(u)=build(mid+1,r,fl^1);
	return maintain(u),u;
}
inline void check(int &u,int fl){
	if(e[lc(u)].siz>e[rc(u)].siz*4||e[rc(u)].siz>e[lc(u)].siz*4)pia(u,1),u=build(1,e[u].siz,fl);
}
void insert(int &u,node x,int w,int fl){
	if(!u){u=++nod,e[u].x=x,e[u].val=w,maintain(u);return;}
	insert(e[u].ch[cmp[fl](x,e[u].x)^1],x,w,fl^1);
	maintain(u),check(u,fl);
}
ll query(int u,matrix x,int fl){
	if(!u||e[u].mat.is_out(x))return 0;
	if(e[u].mat.is_in(x))return e[u].sum;
	return ((matrix){e[u].x,e[u].x}.is_in(x)?e[u].val:0)+query(lc(u),x,fl^1)+query(rc(u),x,fl^1);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(int opt,x,y,w,x1,y1,x2,y2;;){
		read(opt);
		if(opt==0){
			read(x);
		}else if(opt==1){
			read(x),read(y),read(w);
			insert(rt,(node){x,y},w,0);
		}else if(opt==2){
			read(x1),read(y1),read(x2),read(y2);
			print(query(rt,{{x1,y1},{x2,y2}},0),'\n');
		}else{
			return 0;
		}
	}
}