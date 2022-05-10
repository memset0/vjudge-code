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

const int N=1e5+10;
int n,m,max,a[N],b[N],ans[N],cnt[N];

void solve(int d){
	static int b[N],c[N],map[N];
	if(map[d])return; map[d]=1;
	for(register int i=1;i<=d;i++){
		int lim=(n-i)/d;
		for(register int j=0,k=i;j<=lim;j++,k+=d)c[j]=a[k];
		std::sort(c,c+lim+1);
		for(register int j=0,k=i;j<=lim;j++,k+=d)b[k]=c[j];
	}
	for(int i=1;i<=n;i++)if(b[i]!=ans[i]){
		if(b[i]<ans[i])memcpy(ans+1,b+1,n<<2);
		break;
	}
}

void split(int v){
	for(int x=2;x*x<=v;x++)if(v%x==0){
		solve(x);
		while(v%x==0)v/=x;
	}
	if(v!=1)solve(v);
}

int main(){
#ifdef memset0
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
#else
	// freopen("ak.in","r",stdin);
	// freopen("ak.out","w",stdout);
#endif
	static int tn,ta[N];
	read(n);
	for(int i=1;i<=n;i++)read(a[i]),ta[++tn]=a[i];
	std::sort(ta+1,ta+tn+1);
	tn=std::unique(ta+1,ta+tn+1)-ta-1;
	for(int i=1;i<=n;i++)a[i]=std::lower_bound(ta+1,ta+tn+1,a[i])-ta;
	for(int i=1;i<=n;i++)cnt[a[i]]++,max=std::max(max,cnt[a[i]]);
	memcpy(ans+1,a+1,n<<2);

	std::vector<int> vet;
	std::multiset<int> set;
	for(int i=1;i<=n;i++)set.insert(a[i]);
	for(int i=1;i<n;i++){
		set.erase(set.find(a[i+1]));
		int x=*set.begin();
		// printf("%d : %d\n",i,x);
		if(a[i]!=x){
			for(int j=i+2;j<=n;j++)if(a[j]==x)vet.push_back(j-i);
			break;
		}
		set.erase(set.begin());
		set.insert(a[i+1]);
	}
	for(auto x:vet)split(x);

	for(int i=1;i<=n;i++)print(ta[ans[i]]," \n"[i==n]);
	fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
}