#include<bits/stdc++.h>
#ifndef memset0
	#define endl '\n'
#endif
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
using namespace std;
const int N=1e5+9,M=7e5+9;
int T,n,a[N],cnt[M];//
struct matrix{
	unsigned int r[9];
	inline bool get(int i,int j){return (r[i]>>j)&1;}
	inline void set(int i,int j){r[i]|=1<<j;}
	void pushup(const matrix &a,const matrix &b){
		#define solve(i,j) if(unlikely((a.r[i]>>j)&1))r[i]|=b.r[j];
		#define solvex(i) if(unlikely(a.r[i])){solve(i,0)solve(i,1)solve(i,2)solve(i,3)solve(i,4)solve(i,5)solve(i,6)solve(i,7)solve(i,8)}
		solvex(0)
		solvex(1)
		solvex(2)
		solvex(3)
		solvex(4)
		solvex(5)
		solvex(6)
		solvex(7)
		solvex(8)
		#undef solve
		#undef solvex
	}
}X[10],p[1<<20],q[1<<20];
const matrix O={{0,0,0,0,0,0,0,0,0}};
int norm(int x){
	if(x>8)return x-(x-6)/3*3;
	return x;
}
void maintain(int u){
	memset(p[u].r,0,sizeof(p[u].r));
	memset(q[u].r,0,sizeof(q[u].r));
	p[u].pushup(p[u<<1|1],p[u<<1]);
	q[u].pushup(q[u<<1|1],p[u<<1]);
	q[u].pushup(p[u<<1|1],q[u<<1]);
}
void update(int u,int k,int l,int r){
	// cerr<<"update "<<u<<" "<<k<<" "<<x<<endl;
	if(l==r){
		p[u]=X[cnt[k]];
		if(cnt[k]>=2){
			q[u]=X[cnt[k]-2];
		}
		return;
	}
	int mid=(l+r)>>1;
	if(k<=mid)update(u<<1,k,l,mid);
	else update(u<<1|1,k,mid+1,r);
	maintain(u);
}
int main(){
#ifdef memset0
	freopen("K.in","r",stdin);
	// freopen("K.out","w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	for(int x=0;x<=9;x++){
		for(int i=0;i<=2;i++)
			for(int j=0;j<=2;j++){
				int k=x;
				k-=i;
				k-=j;
				if(k<0)continue;
				while(k-3>=0)k-=3;
				X[x].set(i*3+j,j*3+k);
			}
	}
	cin>>T;
	vector<int> val;
	while(T--){
		cin>>n;
		val.clear();
		for(int i=1;i<=n;i++){
			cin>>a[i];
			val.push_back(a[i]);
		}
		sort(val.begin(),val.end());
		val.erase(unique(val.begin(),val.end()),val.end());
		vector<int> id(val.size());
		id[0]=1;
		for(int i=1;i<val.size();i++){
			id[i]=id[i-1]+min(3,val[i]-val[i-1]);
		}
		int m=id.back();
		memset(cnt+1,0,m<<2);//
		int len=1;
		while(len<=m)len<<=1;
		len<<=1;
		memset(p,0,len*sizeof(matrix));
		memset(q,0,len*sizeof(matrix));
		for(int i=0;i<len;i++)p[i].r[0]=1;
		for(int i=1;i<=n;i++){
			int x=*(lower_bound(val.begin(),val.end(),a[i])-val.begin()+id.begin());
			++cnt[x];
			if(cnt[x]>8)cnt[x]-=3;
			update(1,x,1,m);
			cout<<(q[1].r[0]&1);
		}
		cout<<'\n';
	}
}