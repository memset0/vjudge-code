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

const ll INF=1e12;

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

const int N=505;
struct node{
	int x,y;
}a[N];
struct seg{
	node a,b;
}b[N];
struct info{
	double l,r;
	inline bool operator < (const info &o)const
	{
		return r==o.r?l<o.l:r<o.r;
	}
}st[N*N];
inline node operator - (const node &a,const node &b)
{
	return (node){a.x-b.x,a.y-b.y};
}
inline ll cross(const node &a,const node &b)
{
	return 1ll*a.x*b.y-1ll*a.y*b.x;
}
inline bool check(const node &a,const seg &b)
{
	int l1=min(b.a.x,b.b.x),r1=max(b.a.x,b.b.x);
	int l2=min(b.a.y,b.b.y),r2=max(b.a.y,b.b.y);
	return cross(b.a-a,b.b-a)==0&&(a.x>=l1&&a.x<=r1)&&(a.y>=l2&&a.y<=r2);
}
inline double getpoint(const node &a,const node &b)
{
	return (double)b.x+(double)(b.x-a.x)/(double)(a.y-b.y)*(double)b.y;
}
inline info calc(const node &a,const seg &b)
{
	if(check(a,b)) return (info){-INF,INF};
	if(a.y<=b.a.y&&a.y<=b.b.y) return (info){INF,-INF};
	if(a.y<=b.a.y)
	{
		if(cross(a-b.b,b.a-b.b)>0) return (info){-INF,getpoint(a,b.b)};
		else return (info){getpoint(a,b.b),INF};
	}
	if(a.y<=b.b.y)
	{
		if(cross(a-b.a,b.b-b.a)>0) return (info){-INF,getpoint(a,b.a)};
		else return (info){getpoint(a,b.a),INF};
	}
	double L=getpoint(a,b.a),R=getpoint(a,b.b);
	if(L>R) std::swap(L,R);
	return (info){L,R};
}
std::vector<info> solve(std::vector<info> v)
{
	std::sort(v.begin(),v.end());
	int top=0;
	for(auto it:v)
	{
		info cur=it;
		while(top&&it.l<=st[top].r) chmin(cur.l,st[top--].l);
		st[++top]=cur;
	}
	std::vector<info> o;
	double last=-INF;
	for(int j=1;j<=top;++j)
	{
		if(last<st[j].l) o.pb({last,st[j].l});
		chmax(last,st[j].r);
	}
	if(last<INF) o.pb({last,INF});
	return o;
}
void MAIN()
{
	int n,m;read(n,m);
	for(int i=1;i<=n;++i) read(a[i].x,a[i].y);
	for(int i=1;i<=m;++i)
	{
		read(b[i].a.x,b[i].a.y,b[i].b.x,b[i].b.y);
		if(b[i].a.x>=b[i].b.x) std::swap(b[i].a,b[i].b);
	}
	std::vector<info> white;
	for(int i=1;i<=n;++i)
	{
		std::vector<info> shadow;
		for(int j=1;j<=m;++j)
		{
			info tmp=calc(a[i],b[j]);
			if(tmp.l<=tmp.r) shadow.pb(tmp);
		}
		std::sort(shadow.begin(),shadow.end());
		std::vector<info> res(solve(shadow));
		for(auto it:res) white.pb(it);
	}
	std::vector<info> ans=solve(white);
	double sum=0;
	for(auto it:ans) sum+=it.r-it.l;
	if(sum>1e9) printf("-1.000\n");
	else printf("%.8lf\n",sum);
}
int main()
{
	int _;read(_);
	while(_--) MAIN();
	return 0;
}
