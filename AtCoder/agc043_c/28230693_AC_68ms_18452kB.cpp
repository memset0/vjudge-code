#include<bits/stdc++.h>
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

const int N=1e5+10,M=400,mod=998244353;
int n,lim,max,m[3],sg[N];
std::vector<int> G[3][N];

struct z {
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}ans,pw[N],f[3][N],g[N];
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}

void SG(int m,std::vector<int> G[N],int sg[N]){
	static bool vis[N];
	for(int i=n;i>=1;i--){
		for(int j:G[i])vis[sg[j]]=1;
		sg[i]=0;
		while(vis[sg[i]])sg[i]++;
		for(int j:G[i])vis[sg[j]]=0;
	}
}

void fwt(z *a){
	for(int len=1;len<lim;len<<=1)
		for(int i=0;i<lim;i+=(len<<1))
			for(int j=0;j<len;j++){
				z x=a[i+j],y=a[i+j+len];
				a[i+j]=x+y,a[i+j+len]=x-y;
			}
}

int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),lim=sqrt(n);
	for(int i=0;i<3;i++){
		read(m[i]);
		for(int u,v,j=1;j<=m[i];j++){
			read(u),read(v);
			// G[i][u].push_back(v);
			G[i][std::min(u,v)].push_back(std::max(u,v));
			// G[i][std::max(u,v)].push_back(std::min(u,v));
		}
	}
	pw[0]=1,pw[1]=fpow(10,18);
	for(int i=2;i<=n;i++)pw[i]=pw[i-1]*pw[1];
	for(int i=0;i<3;i++){
		SG(m[i],G[i],sg);
		for(int j=1;j<=n;j++){
			max=std::max(max,sg[j]);
			f[i][sg[j]]=f[i][sg[j]]+pw[j];
		}
		// for(int j=1;j<=n;j++){
		// 	printf("%d%c",sg[j]," \n"[j==n]);
		// }
	}
	lim=1; while(lim<=max)lim<<=1;
	// for(int i=0;i<lim;i++)
	// 	for(int j=0;j<lim;j++)
	// 		for(int k=0;k<lim;k++){
	// 			g[i^j^k]=g[i^j^k]+f[0][i]*f[1][j]*f[2][k];
	// 			// if(f[0][i].x&&f[1][j].x&&f[2][k].x){
	// 			// 	printf("%d %d %d : %d\n",i,j,k,f[0][i]*f[1][j]*f[2][k]);
	// 			// }
	// 		}
	for(int i=0;i<3;i++)fwt(f[i]);
	for(int i=0;i<lim;i++)g[i]=f[0][i]*f[1][i]*f[2][i];
	fwt(g);
	z invlim=fpow(lim,mod-2);
	for(int i=0;i<lim;i++)g[i]=g[i]*invlim;
	// for(int i=0;i<lim;i++){
	// 	printf("%d : %d\n",i,g[i]);
	// }
	printf("%d\n",g[0]);
}