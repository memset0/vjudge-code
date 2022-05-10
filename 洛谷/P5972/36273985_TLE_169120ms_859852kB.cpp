#include<bits/stdc++.h>
#define pair std::pair<std::vector<int>,atom>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar('\n');}
const int N=41,M=3200000,mod=19260817;
int n,a[N];
struct atom{
	int min;
	long long cnt;
	friend inline atom operator+(const atom &a,const atom &b){
		if(a.min<b.min)return a;
		if(b.min<a.min)return b;
		return (atom){a.min,a.cnt+b.cnt};
	}
}ans[N];
int cnt;
struct hash_map{
	int tot,hed[mod],nxt[M]; pair set[M];
	void rebuild(){tot=0,memset(hed,-1,sizeof(hed));}
	inline int get_hash(const std::vector<int> &a){
		int hsh=0;
		for(int i=0;i<a.size();i++)hsh=((long long)hsh*131131+a[i])%mod;
		return hsh;
	}
	inline void insert(const pair &it){
		int i=get_hash(it.first);
		for(int j=hed[i];~j;j=nxt[j])if(set[j].first==it.first){
			set[j].second=set[j].second+it.second;
			return;
		}// else ++cnt;
		nxt[tot]=hed[i],set[tot]=it,hed[i]=tot++;
	}
}f[2];
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	f[0].rebuild();
	f[0].insert(std::make_pair(std::vector<int>(n+1),(atom){0,1}));
	for(int k,i=1;i<=n;i++){
		f[i&1].rebuild(),k=0;
		for(int j=i+1;j<=n;j++)if(a[j]<a[i])++k;
		for(int _=0;_<f[i&1^1].tot;_++){
			auto &it=f[i&1^1].set[_];
			auto &key=it.first; const auto &val=it.second; int s=0;
			for(int j=k+1;j<key.size();j++)s+=key[j];
			key[k]+=key[k+1],key.erase(key.begin()+k+1);
			f[i&1].insert(it);
			key[k]++;
			f[i&1].insert(std::make_pair(key,(atom){val.min+s,val.cnt}));
		}
		// printf("%d >> %d\n",i,f[i&1].tot);
	}
	for(int i=0;i<f[n&1].tot;i++)ans[f[n&1].set[i].first[0]]=f[n&1].set[i].second;
	for(int i=1;i<=n;i++)printf("%d %lld\n",ans[i].min,ans[i].cnt);
	std::cerr<<clock()/(double)CLOCKS_PER_SEC<<" "<<cnt<<std::endl;
}