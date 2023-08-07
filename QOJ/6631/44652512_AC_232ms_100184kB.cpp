#include<bits/stdc++.h>
#define at(x,i) (((x)>>i)&1)
#define FIND {cout<<y<<" 1\n";continue;}
using namespace std;
const int N=1e5+9,K=30;
int T,n,m,a[N],f[K];
struct segment{
	int l,r,mid;
	int x;
	int only[K];
	bitset<K> dp[K];
}p[262144+10];
constexpr int find(int x,int i){
	int j=i-1;
	while(j>=0&&!at(x,j))--j;
	++j;
	return j;
}
inline void update(int *a,const int *b){
	for(int i=0;i<K;i++){
		if(a[i]){
			if(b[i])a[i]=-1;
		}else{
			a[i]=b[i];
		}
	}
}
void build(int u,int l,int r){
	p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
	fill(p[u].only,p[u].only+K,0);
	for(int i=0;i<K;i++)p[u].dp[i].reset();
	if(l==r){
		p[u].x=a[l];
		for(int i=0;i<K;i++)
			if(at(a[l],i)){
				p[u].only[i]=l;
				int j=find(a[l],i);
				for(int l=j;l<=i;l++)
					for(int r=l;r<=i;r++){
						p[u].dp[l][r]=1;
					}
			}
		return;
	}
	build(u<<1,l,p[u].mid);
	build(u<<1|1,p[u].mid+1,r);
	update(p[u].only,p[u<<1].only);
	update(p[u].only,p[u<<1|1].only);
	for(int i=0;i<K;i++)
		for(int j=i;j<K;j++){
			p[u].dp[i][j]=p[u<<1].dp[i][j]||p[u<<1|1].dp[i][j];
		}
}
void query(int u,int l,int r){
	if(p[u].l==l&&p[u].r==r){
		update(f,p[u].only);
		return;
	}
	if(r<=p[u].mid)return query(u<<1,l,r);
	if(l>p[u].mid)return query(u<<1|1,l,r);
	query(u<<1,l,p[u].mid);
	query(u<<1|1,p[u].mid+1,r);
}
bool contain(int u,int l,int r,int bl,int br){
	// fprintf(stderr,"contain %d %d %d %d %d\n",u,l,r,bl,br);
	if(p[u].l==l&&p[u].r==r){
		return p[u].dp[bl][br];
	}
	if(r<=p[u].mid)return contain(u<<1,l,r,bl,br);
	if(l>p[u].mid)return contain(u<<1|1,l,r,bl,br);
	return contain(u<<1,l,p[u].mid,bl,br)||contain(u<<1|1,p[u].mid+1,r,bl,br);
}
int main(){
#ifdef memset0
	freopen("A.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++)cin>>a[i];
		build(1,1,n);
		for(int l,r,i=1;i<=m;i++){
			cin>>l>>r;
			int x=0,y=1;
			fill(f,f+K,0);
			query(1,l,r);
			for(int i=0;i<K;i++)
				if(f[i]){
					x|=1<<i;
				}
			while(y<=x)y<<=1;
			--y;
			if(x==y){
				cout<<y<<" 0\n";
				continue;
			}
			int z=x^y,bl=-1,br;
			for(int i=0;i<K;i++)
				if(at(z,i)){
					if(bl==-1)bl=i;
					br=i;
				}
			// cerr<<"! "<<l<<" "<<r<<" "<<bl<<" "<<br<<endl;
			bool fl=false;
			vector<int> p={l-1,r+1};
			for(int i=0;i<K;i++)
				if(f[i]&&f[i]!=-1){
					p.push_back(f[i]);
					bool use=true;
					for(int j=0;j<K;j++)
						if(i!=j&&f[i]==f[j]){
							use=false;
						}
					if(use){
						int j=find(a[f[i]],i);
						if(j<=bl&&br<=i){
							fl=true;
							break;
						}
					}
				}
			if(fl)FIND;
			sort(p.begin(),p.end());
			for(int i=0;i+1<p.size();i++){
				int l=p[i]+1,r=p[i+1]-1;
				if(l<=r){
					if(contain(1,l,r,bl,br)){
						fl=true;
						break;
					}
				}
			}
			if(fl)FIND;
			cout<<y<<" 2\n";
		}
	}
}