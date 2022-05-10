#include<bits/stdc++.h>
#define log(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
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
namespace mem{
	const int N=1e5+9;
	int n,nod,rt,val[N],siz[N],ch[N][2],rnd[N];
	mt19937 rng(20040214);
	inline int newnode(int v){return ++nod,val[nod]=v,siz[nod]=1,rnd[nod]=rng(),nod;}
	inline void maintain(int u){siz[u]=siz[ch[u][0]]+siz[ch[u][1]]+1;}
	int merge(int x,int y){
		if(!x||!y)return x|y;
		if(rnd[x]<rnd[y]){
			return ch[x][1]=merge(ch[x][1],y),maintain(x),x;
		}else{
			return ch[y][0]=merge(x,ch[y][0]),maintain(y),y;
		}
	}
	void split(int u,int k,int &x,int &y){
		if(!u)return x=y=0,void();
		if(val[u]>k){
			y=u,split(ch[y][0],k,x,ch[y][0]);
		}else{
			x=u,split(ch[x][1],k,ch[x][1],y);
		}
		maintain(u);
	}
	int kth(int u,int k){
		if(k<=siz[ch[u][0]])return kth(ch[u][0],k);
		if(k==siz[ch[u][0]]+1)return val[u];
		return kth(ch[u][1],k-siz[ch[u][0]]-1);
	}
	void aknoip(){
	int Q,o,v,x,y,z;
	for(srand(20030417),scanf("%d",&Q);Q--;)switch(scanf("%d%d",&o,&v),o){
		case 1:rnd[++n]=rand(),val[n]=v,siz[n]=1,split(rt,v,x,y),rt=merge(x,merge(n,y));break;
		case 2:split(rt,v-1,x,y),split(y,v,y,z),y=merge(ch[y][0],ch[y][1]),rt=merge(x,merge(y,z));break;
		case 3:split(rt,v-1,x,y),printf("%d\n",siz[x]+1),rt=merge(x,y);break;
		case 4:printf("%d\n",kth(rt,v));break;
		case 5:split(rt,v-1,x,y),printf("%d\n",kth(x,siz[x])),rt=merge(x,y);break;
		case 6:split(rt,v,x,y),printf("%d\n",kth(y,1)),rt=merge(x,y);break;
	}
	}
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	return mem::aknoip(),0;
}