#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<map>
#include<cstdlib>
#include<vector> 
#define gc getchar()
#define ll long long
#define ull unsigned long long
#define file(s) freopen(s".in","r",stdin);freopen(s".out","w",stdout)
#define I inline 
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n)) 
using namespace std;
const int N=4e5+5,M=1<<15;
const double pi=acos(-1);
template<class o>I void qr(o &x)
{
    char c=gc;int f=1;x=0;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=gc;}
    while(c>='0'&&c<='9'){x=x*10+(c^48);c=gc;}
    x*=f;
}
template<class o>I void qw(o x)
{
    if(x<0)x=-x,putchar('-');
    if(x/10)qw(x/10);
    putchar(x%10+48);
}
struct cp
{
	double x,y;
	cp(double x=0.0,double y=0.0):x(x),y(y){}
	I cp operator +(const cp &a)const{return cp(x+a.x,y+a.y);}
	I cp operator -(const cp &a)const{return cp(x-a.x,y-a.y);} 
	I cp operator *(const cp &a)const{return cp(x*a.x-y*a.y,a.x*y+x*a.y);}
	I cp operator +(const double &a)const{return cp(x+a,y+a);}
	I cp operator -(const double &a)const{return cp(x-a,y-a);}
	I cp operator *(const double &a)const{return cp(x*a,y*a);}
	I cp operator /(const double &a)const{return cp(x/a,y/a);}
}w[N<<1];
int tr[N<<1],cnt,mod;
I void rev(int n)
{
	if(cnt==n)return ;cnt=n;
	for(int i=0;i<n;i++)tr[i]=(tr[i>>1]>>1|((i&1)?n>>1:0));
}
I void Init(int n){for(int i=1;i<n;i<<=1){w[i]=cp(1,0);for(int j=1;j<i;j++)w[i+j]=(((j&31)==1)?cp(cos(pi*j/i),sin(pi*j/i)):w[i+j-1]*w[i+1]);}}
void dft(cp *g,bool op,int n)
{
	rev(n);
	static cp f[N<<1],t;
	for(int i=0;i<n;i++)f[i]=g[tr[i]];
	for(int p=2,l=1;p<=n;l=p,p<<=1)
		for(int i=0;i<n;i+=p)for(int j=0;j<l;j++)
			t=w[j|l]*f[i|j|l],f[i|j|l]=f[i|j]-t,f[i|j]=f[i|j]+t;
	if(op)for(int i=0;i<n;i++)g[i]=f[i]/n;
	else for(int i=0;i<n;i++)g[i]=f[i];
}
I void px(cp *f,cp *g,int n){for(int i=0;i<n;i++)f[i]=f[i]*g[i];}
I ll num(double x){return x<0?(ll)(x-0.49)%mod:(ll)(x+0.49)%mod;}
cp p[N<<1],q[N<<1];
void mtt(int *f,int *g,int m)
{
	int n=1;for(;n<(m<<1);n<<=1);
	for(int i=0;i<m;i++)p[i]=cp(f[i],0),q[i]=cp(g[i],0);
	for(int i=m;i<n;i++)p[i]=q[i]=cp(0,0);
	dft(p,0,n);dft(q,0,n);
	px(p,q,n);
	reverse(p+1,p+n);
	dft(p,1,n);
	for(int i=0;i<m;i++)f[i]=(num(p[i].x)+mod)%mod;
}
int f[2][N<<1];//0 odd 1 even
void add(int p,int m)
{
	for(int i=m;i;i--)f[p][i]=(f[p][i]+f[0][i-1]+f[1][i-1])%mod; 
	f[p][1]=(f[p][1]+1)%mod;
}
int g[2][N<<1],n;
void mul(int p,int m)
{
	for(int i=0;i<2;i++)
		for(int j=1;j<m;j++)
			g[i][j]=(f[0][j]+f[1][j])%mod;
	g[0][0]=g[1][0]=1;
	mtt(g[0],f[p],m);
	mtt(g[1],f[p^1],m);
	for(int i=0;i<2;i++)	
		for(int j=1;j<m;j++)
			f[i][j]=(g[i][j]+f[i][j])%mod;
	clr(g[0],n),clr(g[1],n);
}
int main()
{
	int mx,lg=0,j=0;qr(n),qr(mx);qr(mod);
	mx/=2;if(mx)lg=log2(mx);ll ans=0;
	//if(mx==0){puts("0");return 0;}
	int m=n+1;for(n=1;n<(m<<1);n<<=1);
	Init(n);
	for(int i=lg;~i;i--)
	{
		mul(j&1,m);j<<=1;
		if(mx&(1<<i))add((j|1)&1,m),j|=1;
		for(int k=1;k<m;k++)if(k&1)ans+=f[1][k];
		ans%=mod;
	}
	qw(ans);puts("");
	return 0;
}