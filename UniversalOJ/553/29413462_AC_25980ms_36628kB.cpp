#include<bits/stdc++.h>
const int Buf=1<<21; char ibuf[Buf],*iS,*iT,obuf[Buf],*oS=obuf,*oT=oS+Buf-1;
#define flush() (fwrite(obuf,1,oS-obuf,stdout),oS=obuf,void())
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,Buf,stdin),(iS==iT?EOF:*iS++)):*iS++)
#define putchar(x) (*oS++=(x),oS==oT?flush():void())
struct Flusher_{~Flusher_(){flush();}}flusher_;
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
const int N=12010,Q=1e6+10,D=1e9+10;
int n,q,m,S,M,L[N],R[N],bln[N],loc[N],at[N],ans[Q];
std::vector<int> all,vec[N];
struct node{
	long long x,y;
}a[N];
std::pair<node,int> b[Q];
struct frac{
	long long x,y;
	inline frac(long long x=0,long long y=1):x(x),y(y){}
	friend inline bool operator<(const frac &a,const frac &b){return (__int128)a.x*b.y<(__int128)b.x*a.y;}
	friend inline bool operator==(const frac &a,const frac &b){return (__int128)a.x*b.y==(__int128)b.x*a.y;}
	friend inline bool operator<=(const frac &a,const frac &b){return (__int128)a.x*b.y<=(__int128)b.x*a.y;}
};
struct event{
	frac k;
	int i,j;
};
inline bool check(const node &a,const node &b){
	return a.y<=a.x*b.x+b.y;
}
int query(const node &x){
	int res=0,l=1,r=m,mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(a[at[mid]],x)){
			res=mid,l=mid+1;
		}else{
			r=mid-1;
		}
	}
	return res;
}
void modify(int i,int j){
	j=at[loc[i]+1];
	std::swap(at[loc[i]],at[loc[j]]);
	std::swap(loc[i],loc[j]);
}
int main(){
#ifdef memset0
	freopen("ex_circle3.in","r",stdin);
	freopen("ex_circle3.out","w",stdout);
#endif
	read(n),read(q),S=std::max(1,(int)(sqrt(q)*0.4));
	for(int x,y,i=1;i<=n;i++){
		read(x),read(y);
		a[i]={y,1ll*x*x+1ll*y*y+2ll*D*y};
	}
	for(int z,r,i=1;i<=q;i++){
		read(z),read(r);
		b[i]={{2ll*(z+D),1ll*r*r-1ll*z*z},i};
	}
	for(int i=1;i<=n;i++)bln[i]=(i-1)/S+1; M=bln[n];
	for(int i=1;i<=n;i++)if(!L[bln[i]])L[bln[i]]=i;
	for(int i=n;i>=1;i--)if(!R[bln[i]])R[bln[i]]=i;
	std::sort(b+1,b+q+1,[](const std::pair<node,int> &a,const std::pair<node,int> &b){
		return a.first.x<b.first.x;
	});
	for(int c=1;c<=M;c++){
		std::vector<event> op;
		std::sort(a+L[c],a+R[c]+1,[](const node &a,const node &b){
			return a.y==b.y?a.x<b.x:a.y<b.y;
		});
		for(int i=L[c];i<=R[c];i++)
			for(int j=i+1;j<=R[c];j++)
				if(a[i].x!=a[j].x){
					op.push_back({{a[j].y-a[i].y,a[j].x-a[i].x},i,j});
				}
		m=R[c]-L[c]+1;
		for(int i=L[c];i<=R[c];i++)loc[i]=i-L[c]+1,at[i-L[c]+1]=i;
		std::sort(op.begin(),op.end(),[](const event &a,const event &b){
			return a.k<b.k;
		});
		int k=1;
		frac lst={0,1};
		for(int i=0,j;i<op.size();i=j+1){
			for(j=i;j+1<op.size()&&op[j+1].k==op[i].k;j++);
			while(k<=q&&lst<b[k].first.x&&b[k].first.x<=op[i].k){
				ans[b[k].second]+=query(b[k].first),k++;
			}
			all.clear();
			for(int u=i;u<=j;u++){
				if(!vec[op[u].i].size())all.push_back(op[u].i);
				vec[op[u].i].push_back(op[u].j);
			}
			std::sort(all.begin(),all.end(),[&](int x,int y){
				return loc[x]>loc[y];
			});
			for(int x:all){
				std::sort(vec[x].begin(),vec[x].end(),[&](int x,int y){
					return loc[x]<loc[y];
				});
				for(int y:vec[x])modify(x,y);
				vec[x].clear();
			}
			lst=op[i].k;
		}
		while(k<=q)ans[b[k].second]+=query(b[k].first),k++;
	}
	for(int i=1;i<=q;i++)print(ans[i],'\n');
}