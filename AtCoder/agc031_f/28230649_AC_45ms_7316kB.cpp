#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=5e4+10,M=1e6+10;
bool pre[2][M];
struct edge{int u,v,c;}e[N];
int n,m,q,g,z,mod,fa[N*6],tr[6][3];
inline int gcd(int n,int m){return m?gcd(m,n%m):n;}
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
signed main(){
	read(n),read(m),read(q),read(mod);
	for(int i=1;i<=m;i++){
		read(e[i].u),read(e[i].v),read(e[i].c);
		g=gcd(g,std::abs(e[i].c-e[1].c));
	}
	g=g?g:mod,mod=gcd(3*g,mod),z=e[1].c%g;
	for(int i=1;i<=6*n;i++)fa[i]=i;
	tr[0][0]=3,tr[0][1]=4,tr[0][2]=5,tr[1][0]=5,tr[1][1]=3,tr[1][2]=4,tr[2][0]=4,tr[2][1]=5,tr[2][2]=3;
	tr[3][0]=0,tr[3][1]=1,tr[3][2]=2,tr[4][0]=2,tr[4][1]=0,tr[4][2]=1,tr[5][0]=1,tr[5][1]=2,tr[5][2]=0;
	for(int i=1;i<=m;i++){
		int t=(e[i].c-z)/g%3;
		for(int j=0;j<6;j++){
			fa[find(j*n+e[i].u)]=find(tr[j][t]*n+e[i].v);
			fa[find(j*n+e[i].v)]=find(tr[j][t]*n+e[i].u);
		}
	}
	for(int u=z*1%mod;!pre[0][u];u=u*4%mod)pre[0][u]=1;
	for(int u=z*2%mod;!pre[1][u];u=u*4%mod)pre[1][u]=1;
	// for(int i=1;i<=n;i++){
	// 	printf(">>> ");
	// 	for(int j=0;j<6;j++)printf("%d%c",find(j*n+i)," \n"[j==5]);
	// }
	for(int s,t,r,fl,i=1;i<=q;i++){
		read(s),read(t),read(r),fl=0;
		for(int p=0;p<2;p++)for(int q=0;q<3;q++)if(find((p*3+q)*n+s)==find(t)){
			// printf("-> %d %d | %d %d\n",p,q,r+z-q*g,pre[p][pure(r+z-q*g)]);
			if(pre[p][(r+z+(3-q)*g)%mod]){fl=1;break;}
		}
		puts(fl?"YES":"NO");
	}
}