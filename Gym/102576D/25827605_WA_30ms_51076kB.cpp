#include<bits/stdc++.h>
const int S=1<<21; char ibuf[S],*iS,*iT,obuf[S],*oS=obuf,*oT=oS+S-1;
#define flush() (fwrite(obuf,1,oS-obuf,stdout),oS=obuf,void())
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,S,stdin),(iS==iT?EOF:*iS++)):*iS++)
#define putchar(x) (*oS++=(x),oS==oT?flush():void())
struct Flusher_{~Flusher_(){flush();}}flusher_;
std::mt19937 rng(20040725^std::chrono::steady_clock::now().time_since_epoch().count());
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
const int N=3e3+10,M=1e6+10;
int T,n,ans,sum;
struct segment{int l,r;};
std::vector<int> all,pa[M],pb[M];
std::vector<segment> p,a,b;
void solve(int x){
	// printf("solve %d\n",x);
	int ans=0;
	std::vector<segment> a,b;
	for(const auto &p:(::a))if(p.l<=x&&p.r>=x)a.push_back(p);
	for(const auto &p:(::b))if(p.l>x&&p.r<x)b.push_back({p.r+1,p.l-1}); else ++ans;
	ans+=a.size()+b.size();
	for(const auto &p:a)pa[p.r].push_back(p.l);
	for(const auto &p:b)pb[p.r].push_back(p.l);
	// printf("[a] >> "); for(const auto &p:a)printf("<%d,%d> ",p.l,p.r); puts("");
	// printf("[b] >> "); for(const auto &p:b)printf("<%d,%d> ",p.l,p.r); puts("");
	std::multiset<int> set;
	// printf("%d\n",ans);
	for(int i:all){
		// printf("%d : %d %d\n",i,pa[i].size(),pb[i].size());
		for(int v:pa[i])set.insert(v);
		for(int v:pb[i]){
			auto it=set.lower_bound(v);
			// printf("%d : %d\n",v,it!=set.end());
			if(it!=set.end()){
				ans--,set.erase(it);
			}
		}
		pa[i].clear(),pb[i].clear();
	}
	::ans=std::max(ans,::ans);
}
int main(){
#ifdef memset0
	freopen("D.in","r",stdin);
#endif
	for(read(T);T--;){
		read(n),ans=0,p.resize(n),a.clear(),b.clear(),all.clear();
		for(int i=0,l,r;i<n;i++)read(p[i].l),read(p[i].r);
		for(int i=0;i<n;i++)(p[i].l<=p[i].r?a:b).push_back(p[i]);
		for(const auto &p:a)all.push_back(p.l),all.push_back(p.r);
		for(const auto &p:b){
			if(p.l-1>=1)all.push_back(p.l-1);
			if(p.r+1<=1000000)all.push_back(p.r+1);
		}
		for(int i=0;i<n;i++)all.push_back(p[i].l),all.push_back(p[i].r);
		std::sort(all.begin(),all.end());
		all.erase(std::unique(all.begin(),all.end()),all.end());
		std::vector<std::pair<int,int>> suf(all.size());
		for(int i=0;i<suf.size();i++){
			suf[i].first=all[i];
			for(const auto &p:a)suf[i].second+=p.l<=all[i]&&all[i]<=p.r;
			for(const auto &p:b)suf[i].second+=p.l<=all[i]||all[i]<=p.r;
		}
		std::sort(suf.begin(),suf.end(),[](const std::pair<int,int> &a,const std::pair<int,int> &b){return a.second<b.second;});
		solve(5);
		// for(const std::pair<int,int> &x:suf)solve(x.first);
		print(ans,'\n');
		// fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
	}
}