#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,i,o,x,y;
struct node{
	int ch[2],fa,v,s;
	bool b;
	inline int dir(int x){return ch[1]==x;}
	inline void rev(){b^=1;swap(ch[0],ch[1]);}
}t[N];
inline void upd(int x){t[x].s=t[t[x].ch[0]].s^t[t[x].ch[1]].s^t[x].v;}
inline void setc(int x,int y,int o){t[x].ch[o]=y;t[y].fa=x;}
inline void pushdown(int x){if(t[x].b)t[t[x].ch[0]].rev(),t[t[x].ch[1]].rev(),t[x].b=0;}
inline bool nrt(int x){return t[t[x].fa].ch[0]==x || t[t[x].fa].ch[1]==x;}
inline void rotate(int x){
	int y=t[x].fa,z=t[y].fa,o;
	if(nrt(y))setc(z,x,t[z].dir(y));t[x].fa=z;
	o=t[y].dir(x);setc(y,t[x].ch[!o],o);setc(x,y,!o);upd(y);
}
bool FL;
inline void splay(int x){
	static int st[N];int w=0,y,z;
	for(y=x;st[++w]=y,nrt(y);y=t[y].fa);
	for(;w;)pushdown(st[w--]);
	for(;nrt(x);rotate(x)){
		y=t[x].fa;z=t[y].fa;
		if(nrt(y))rotate(t[z].dir(y)==t[y].dir(x)?y:x);
			else ++x,--x;
	}
	upd(x);
}
inline void access(int x){
	for(int y=0;x;x=t[x].fa)
		splay(x),t[x].ch[1]=y,upd(x),y=x;
}
inline void makeroot(int x){access(x);splay(x);t[x].rev();}
inline int goleft(int x){for(;t[x].ch[0];x=t[x].ch[0]);return x;}
unordered_set<int>adj[N];
int main(){
//	freopen("1","r",stdin);
	freopen("testdata.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)scanf("%d",&t[i].v),t[i].s=t[i].v;
	for(;m--;){
		scanf("%d%d%d",&o,&x,&y);
		if(o==0){
			makeroot(x);
			access(y);
			splay(x),printf("%d\n",t[x].s);
		}
		if(o==1){
			makeroot(x);
			access(y);
			splay(y);
			int z=goleft(y);
			if(z==x){splay(x);continue;}else t[y].rev(),splay(z),t[z].fa=x,adj[x].insert(y),adj[y].insert(x);
		}
		if(o==2){
			if(!adj[x].count(y))continue;
			adj[x].erase(y);adj[y].erase(x);
			makeroot(x);access(y);splay(y);t[y].ch[0]=t[x].fa=0;upd(y);
		}
		if(o==3)makeroot(x),t[x].v=y,upd(x);
	}
	return 0;
}
