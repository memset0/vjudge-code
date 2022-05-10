#include<bits/stdc++.h>
#define ll long long
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
int n,m,rt,nod;
struct node{
	int x,y;
	inline int& operator[](int i){return i?y:x;}
};
inline bool comp0(const node &x,const node &y){return x.x==y.x?x.y<y.y:x.x<y.x;}
inline bool comp1(const node &x,const node &y){return x.y==y.y?x.x<y.x:x.y<y.y;}
bool (*comp[2])(const node&,const node&)={comp0,comp1};
struct matrix{
	node a,b;
	inline matrix(){}
	inline matrix(const node &x){a=b=x;}
	inline matrix(int x1,int y1,int x2,int y2){
		a.x=std::min(x1,x2),b.x=std::max(x1,x2);
		a.y=std::min(y1,y2),b.y=std::max(y1,y2);
	}
	inline void merge(const matrix &other){
		a.x=std::min(a.x,other.a.x),a.y=std::min(a.y,other.a.y);
		b.x=std::max(b.x,other.b.x),b.y=std::max(b.y,other.b.y);
	}
	inline bool is_in(const matrix &other)const{
		return other.a.x<=a.x&&other.a.y<=a.y&&b.x<=other.b.x&&b.y<=other.b.y;
	}
	inline bool is_out(const matrix &other)const{
		return b.x<other.a.x||b.y<other.a.y||a.x>other.b.x||a.y>other.b.y;
	}
};
struct tree_node{
	ll sum,val; node x; matrix mat; int siz,ch[2];
}e[N];
inline void maintain(int u){
	e[u].siz=1,e[u].sum=e[u].val,e[u].mat=matrix(e[u].x);
	for(int i=0;i<2;i++)if(e[u].ch[i]){
		e[u].siz+=e[e[u].ch[i]].siz;
		e[u].sum+=e[e[u].ch[i]].sum;
		e[u].mat.merge(e[e[u].ch[i]].mat);
	}
}
void insert(int &u,node x,int w,int fl){
	if(!u){u=++nod,e[u].x=x,e[u].val=w,maintain(u);return;}
	insert(e[u].ch[comp[fl](x,e[u].x)^1],x,w,fl^1);
	maintain(u);
}
ll query(int u,matrix x,int fl){
	if(!u||e[u].mat.is_out(x))return 0;
	if(e[u].mat.is_in(x))return e[u].sum;
	ll res=matrix(e[u].x).is_in(x)?e[u].val:0;
	if(comp[fl](x.a,e[u].x)&&comp[fl](x.b,e[u].x))res+=query(e[u].ch[0],x,fl^1);
	if(!comp[fl](x.a,e[u].x)&&!comp[fl](x.b,e[u].x))res+=query(e[u].ch[1],x,fl^1);
	return res;
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
			print(query(rt,matrix(x1,y1,x2,y2),0),'\n');
		}else{
			return 0;
		}
	}
}