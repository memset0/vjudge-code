#include<bits/stdc++.h>
#define e(i) a[i].n
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
const int N=1010,mod=31607;
const double pi=acos(-1);
int T,n,ans,f[N][N],g[N][N],p[N][N];
struct node{int x,y;};
struct atom{node n; double atan; int p;}a[N];
inline double deg(int i,int j){return atan2(e(j).y-e(i).y,e(j).x-e(i).x);}
inline node vec(const node &a,const node &b){return {b.x-a.x,b.y-a.y};}
inline int cross(node a,node b){return a.x*b.y-b.x*a.y;}
inline int triangle(int x,int y){return cross(vec(a[0].n,a[x].n),vec(a[x].n,a[y].n))%mod;}
inline int fpow(int a,int b){int s=1;for(;b;b>>=1,a=a*a%mod)if(b&1)s=s*a%mod;return s;}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(read(T);T--;){
		ans=0;
		read(n);
		int minx=INT_MAX,miny=INT_MAX;
		for(int i=1,p,q;i<=n;i++){
			read(a[i].n.x),read(a[i].n.y),read(p),read(q);
			a[i].p=p*fpow(q,mod-2)%mod;
			a[i].atan=atan2(a[i].n.y,a[i].n.x);
			minx=std::min(minx,a[i].n.x-10);
			miny=std::min(miny,a[i].n.y-10);
		}
		for(int i=1;i<=n;i++){
			a[i].n.x-=minx;
			a[i].n.y-=miny;
		}
		std::sort(a+1,a+n+1,[](const atom &a,const atom &b){
			return a.atan==b.atan?a.n.x<b.n.x:a.atan==b.atan;
		});
		for(int i=1;i<=n;i++){
			std::vector<std::pair<double,int>> q;
			for(int j=1;j<=n;j++)if(j!=i)q.push_back({deg(i,j),j});
			std::sort(q.begin(),q.end(),[](const std::pair<double,int> &x,const std::pair<double,int> &y){
				return x.first==y.first?a[x.second].n.x<a[y.second].n.x:x.first<y.first;
			});
			for(int i=0,l=q.size();i<l;i++)q.push_back({q[i].first+pi,q[i].second});
			for(int j=1;j<=n;j++)if(i!=j){
				int l=std::lower_bound(q.begin(),q.end(),std::make_pair(deg(i,j)+pi/2,j))-q.begin();
				int r=std::lower_bound(q.begin(),q.end(),std::make_pair(deg(i,j)+pi,j))-q.begin();
				p[i][j]=a[i].p*a[j].p%mod*;
			}
		}
		for(int l=1;l<=n;l++)
			for(int r=l;r<=n;r++){
				f[l][r]=triangle(l,r)*p[l][r];
				g[l][r]=p[l][r];
			}
		for(int i=1;i<=n;i++){
			std::vector<std::pair<double,int>> q;
			for(int j=1;j<i;j++)q.push_back({deg(j,i),f[j][i]});
			std::sort(q.begin(),q.end());
			for(int j=1;j<q.size();j++)(q[i].second+=q[i-1].second)%=mod;
			for(int j=i+1;j<=n;j++){
				auto it=--std::upper_bound(q.begin(),q.end(),std::make_pair(deg(i,j),1000000));
				f[i][j]=(f[i][j]+p[i][j]*(*it).second%mod*triangle(i,j))%mod;
				g[i][j]=(g[i][j]+p[i][j]*(*it).second)%mod;
			}
		}
		ans=(ans+mod)%mod;
		ans=ans&1?(ans+mod)>>1:ans>>1;
		printf("%d\n",ans);
	}
}