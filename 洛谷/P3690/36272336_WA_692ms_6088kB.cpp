#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=1e5+10;
int n,m,val[N],sum[N],fa[N],ch[N][2],rev[N];
inline bool getson(int x){return ch[fa[x]][1]==x;}
inline bool isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
inline void maintain(int x){sum[x]=sum[ch[x][0]]^val[x]^sum[ch[x][1]];}
inline void rotate(int x){
	if(!x||!fa[x])return;int f=fa[x],ff=fa[f],fs=getson(x),ffs=getson(f),y=ch[x][fs^1];
	if(!isroot(f))ch[ff][ffs]=x;ch[x][fs^1]=f,ch[f][fs]=y;
	fa[y]=f,fa[f]=x,fa[x]=ff,maintain(f),maintain(x);
}
inline void pushup(int x){rev[x]^=1,std::swap(ch[x][0],ch[x][1]);}
inline void clear(int x){if(!isroot(x))clear(fa[x]);if(rev[x])pushup(ch[x][0]),pushup(ch[x][1]),rev[x]=0;}
inline void splay(int x){
	clear(x);
	for(int f=fa[x];!isroot(x);rotate(x),f=fa[x])if(!isroot(f))rotate(getson(x)==getson(f)?f:x);
}
inline void access(int x){
	for(int y=0;x;y=x,x=fa[x])splay(x),ch[x][1]=y,maintain(x);
}
inline void mroot(int x){access(x),splay(x),pushup(x);}
inline void split(int x,int y){mroot(x),access(y),splay(y);}
inline int getroot(int x){
	access(x),splay(x);
	while(ch[x][0])x=ch[x][0];return x;
}
int main(){
	read(n),read(m);
	for(int i=1;i<=n;i++)read(val[i]),sum[i]=val[i];
	for(int i=1,x,y,op;i<=m;i++){
		read(op),read(x),read(y);
		if(op==0)split(x,y),printf("%d\n",sum[y]);
		else if(op==1){
			if(getroot(x)!=getroot(y))access(x),splay(x),fa[x]=y;
		}else if(op==2){
			if(getroot(x)==getroot(y)){
				split(x,y);
				if(fa[x]==y&&ch[y][0]==x&&!ch[x][1])fa[x]=ch[y][0]=0;
			}
		}else mroot(x),val[x]=y,maintain(x);
	}
}