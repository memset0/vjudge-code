#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;char c=getchar();while(!isdigit(c))c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
}
const int N=3e3+10,mod=998244353;
int n,m,u,v,cnt[N];
std::vector<int> vet,G[N];
struct z {
	int x;
	z(int x=0):x(x){}
	friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
	friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
	friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}t,p[N],res[N],f[N][N];
inline z fpow(z a,int b){z s(1);for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n),f[n][n]=1;
	for(int i=1,x;i<=(n<<1);i++)read(x);
	read(m);
	for(int i=1;i<=m;i++)read(u),read(v),G[u].push_back(v),G[v].push_back(u);
	for(int i=1;i<n;i++)f[i][i]=f[i][n+1]=1;
	for(int i=1;i<n;i++)p[i]=0-fpow(G[i].size(),mod-2);
	for(int i=1;i<n;i++)for(int j:G[i])f[i][j]=p[i];
	for(int i=1;i<=n;i++)for(int j=1;j<=n+1;j++)cnt[i]+=(bool)f[i][j].x;
	cnt[0]=20040725;
	for(int k,i=1;i<=n;i++){
		k=0;
		for(int j=i;j<=n;j++)if(f[j][i].x&&cnt[j]<cnt[k])k=j;
		if(!k){puts("0");return 0;}
		if(i!=k)std::swap(f[i],f[k]),std::swap(cnt[i],cnt[k]);
 		t=fpow(f[i][i],mod-2),vet.clear();
		for(int j=i;j<=n+1;j++)if(f[i][j].x)vet.push_back(j);
		for(int j:vet)f[i][j]=f[i][j]*t;
		for(int j=i+1;j<=n;j++){
			t=f[j][i]; 
			for(int k:vet){
				cnt[j]-=(bool)f[j][k].x;
				f[j][k]=f[j][k]-f[i][k]*t;
				cnt[j]+=(bool)f[j][k].x;
			}
		}
		// for(int i=1;i<=n;i++)for(int j=1;j<=n+1;j++)printf("%d%c",f[i][j].x," \n"[j==n+1]);
	}
	for(int i=n;i>=1;i--){
		res[i]=f[i][n+1];
		for(int j=1;j<i;j++)f[j][n+1]=f[j][n+1]-res[i]*f[j][i];
	}
	printf("%d\n",res[1].x);
}