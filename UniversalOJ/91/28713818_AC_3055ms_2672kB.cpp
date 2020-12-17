// Author -- xyr2005

#include<bits/stdc++.h>

#define lowbit(x) ((x)&(-(x)))
#define DEBUG fprintf(stderr,"Running on Line %d in Function %s\n",__LINE__,__FUNCTION__)
#define SZ(x) ((int)x.size())
#define mkpr std::make_pair
#define pb push_back

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef std::pair<int,int> pi;
typedef std::pair<ll,ll> pl;
using std::min;
using std::max;

const int inf=0x3f3f3f3f,Inf=0x7fffffff;
const ll INF=0x3f3f3f3f3f3f3f3f;

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
template <typename _Tp>_Tp gcd(const _Tp &a,const _Tp &b){return (!b)?a:gcd(b,a%b);}
template <typename _Tp>inline _Tp abs(const _Tp &a){return a>=0?a:-a;}
template <typename _Tp>inline void chmax(_Tp &a,const _Tp &b){(a<b)&&(a=b);}
template <typename _Tp>inline void chmin(_Tp &a,const _Tp &b){(b<a)&&(a=b);}
template <typename _Tp>inline void read(_Tp &x)
{
	char ch(getchar());bool f(false);while(!isdigit(ch)) f|=ch==45,ch=getchar();
	x=ch&15,ch=getchar();while(isdigit(ch)) x=(((x<<2)+x)<<1)+(ch&15),ch=getchar();
	f&&(x=-x);
}
template <typename _Tp,typename... Args>inline void read(_Tp &t,Args &...args){read(t);read(args...);}
inline int read_str(char *s)
{
	char ch(getchar());while(ch==' '||ch=='\r'||ch=='\n') ch=getchar();
	char *tar=s;*tar=ch,ch=getchar();while(ch!=' '&&ch!='\r'&&ch!='\n'&&ch!=EOF) *(++tar)=ch,ch=getchar();
	return tar-s+1;
}

const int N=2005;
typedef std::bitset<N> B;
int p[N],n,m,q;
B a[N],b[N],c[N],t;
void insert(int id)
{
	for(int i=m-1;i>=0;--i)
	{
		if(a[id].test(i))
		{
			if(p[i]) a[id]^=a[p[i]],b[id]^=b[p[i]];
			else{p[i]=id;return;}
		}
	}
}
void upd(int id,const B &o)
{
	if(o.none()) return;
	int g=0;
	for(int i=1;i<=n;++i) if(a[i].none()&&b[i].test(id)){g=i;break;}
	if(!g) for(int i=0;i<m;++i) if(p[i]&&b[p[i]].test(id)){g=p[i],p[i]=0;break;}
	for(int i=1;i<=n;++i) if(i!=g&&b[i].test(id)) a[i]^=a[g],b[i]^=b[g];
	a[g]^=o;insert(g);
}
void read(B &x)
{
	char ch;x.reset();
	for(int i=m-1;i>=0;--i)
	{
		do{ch=getchar();}while(!isdigit(ch));
		if(ch=='1') x.set(i);
	}
}
int main()
{
	read(n,m,q);
	for(int i=1;i<=n;++i) read(c[i]),a[i]=c[i]^c[i-1],insert(i),b[i].set(i);
	int opt,x,y;
	while(q--)
	{
		read(opt);
		if(opt==1)
		{
			read(x,y),read(t);
			for(int i=x;i<=y;++i) c[i]^=t;
			upd(x,t);
			if(y<n) upd(y+1,t);
		}
		else if(opt==2)
		{
			read(x,y),read(t);
			if(y<n) upd(y+1,c[y]^t);
			for(int i=y;i>x;--i) upd(i,c[i]^c[i-1]),c[i]=t;
			upd(x,t^c[x]),c[x]=t;
		}
		else
		{
			t.reset();
			for(int i=m-1;i>=0;--i) if(p[i]&&!t.test(i)) t^=a[p[i]];
			for(int i=m-1;i>=0;--i) printf("%d",t.test(i));
			printf("\n");
		}
	}
	return 0;
}
