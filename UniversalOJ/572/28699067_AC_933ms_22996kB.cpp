#include<bits/stdc++.h>
using namespace std;

template<class T> inline void read(T &x){
	x=0; char c=getchar(); bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}

namespace mem{

const int N=1e5+10,M=1e6+1e5+10,mod=998244353;
int n,m,tem,a[N],t[N],v[N],p[N],q[N],id[N],mul[N],ind[N],tag[N],ans[N];

struct graph{
	int tot,hed[N],nxt[M],to[M];
	inline void add_edge(int u,int v){
		nxt[tot]=hed[u],to[tot]=v,hed[u]=tot++;
	}
}G,R;

inline void add(int x,int y){
//	printf("%d -> %d\n",x,y);
	G.add_edge(x,y);
	R.add_edge(y,x);
	++ind[x];
}

void akcsp(){
	memset(G.hed,-1,sizeof(G.hed));
	memset(R.hed,-1,sizeof(R.hed));
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	read(m);
	for(int i=1;i<=m;i++){
		read(t[i]);
		if(t[i]==1)read(p[i]),read(v[i]);
		if(t[i]==2)read(v[i]);
		if(t[i]==3){
			read(p[i]);
			for(int q,j=1;j<=p[i];j++)read(q),add(i,q);
		}
	}
	++m;
	t[m]=3,read(p[m]);
	for(int q,j=1;j<=p[m];j++)read(q),add(m,q);
	int l=1,r=0;
	for(int i=1;i<=m;i++)if(!ind[i])q[++r]=i;
	while(l<=r){
		int u=q[l++]; id[++tem]=u;
//		printf("q:: %d\n",u);
		for(int i=R.hed[u];~i;i=R.nxt[i]){
			int v=R.to[i];
			if(!--ind[v])q[++r]=v;
		}
	}
	for(int i=m;i>=1;i--)if(id[i]==m){
		swap(id[i],id[m]);
		break;
	}
	for(int i=1;i<=m;i++){
		int u=id[i];
		if(t[u]==1)mul[u]=1;
		else if(t[u]==2)mul[u]=v[u];
		else{
			mul[u]=1;
			for(int i=G.hed[u];~i;i=G.nxt[i]){
				mul[u]=(long long)mul[u]*mul[G.to[i]]%mod;
			}
		}
//		printf("%d[%d] > %d\n",u,t[u],mul[u]);
	}
	for(int i=1;i<=n;i++){
		ans[i]=(long long)a[i]*mul[m]%mod;
	}
	tag[m]=1;
	for(int i=m;i>=1;i--){
		int u=id[i];
		if(t[u]==1){
			ans[p[u]]=(ans[p[u]]+(long long)v[u]*tag[u])%mod;
		}else if(t[u]==2){
			continue;
		}else{
			int tem=1;
			for(int i=G.hed[u];~i;i=G.nxt[i]){
				int v=G.to[i];
				tag[v]=(tag[v]+(long long)tag[u]*tem)%mod;
				tem=(long long)tem*mul[v]%mod;
			}
		}
	}
//	for(int i=1;i<=m;i++)printf("%d%c",mul[i]," \n"[i==m]);
//	for(int i=1;i<=m;i++)printf("%d%c",tag[i]," \n"[i==m]);
	for(int i=1;i<=n;i++){
		print(ans[i]);
		putchar(i==n?'\n':' ');
	}
}

}

int main(){
//#ifdef memset0
//	freopen("call3.in","r",stdin);
//	freopen("call3.out","w",stdout);
//#else
//	freopen("call.in","r",stdin);
//	freopen("call.out","w",stdout);
//#endif
	mem::akcsp();
}