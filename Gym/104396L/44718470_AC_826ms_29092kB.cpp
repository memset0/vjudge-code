#include<bits/stdc++.h>
#define log(...) fprintf(stderr,__VA_ARGS__)
#define all(x) (x).begin(),(x).end()
using namespace std;
const int N=1e5+9;
int T,n,w,h,l,a[N][6];
__int128 vol;
vector<int> val[3];
template<class T> struct todo:map<int,vector<T>>{
	void push(int k,const T &b){
		auto it=this->find(k);
		if(it==this->end()){
			this->operator[](k)={b};
		}else{
			it->second.push_back(b);
		}
	}
};
todo<tuple<int,int,int>> scan;
todo<tuple<int,int,int,int,int>> scanz;
struct segment{
	int l,r,mid;
	int min,max,tag;
}p[N<<2];
inline void pushup(int u,int x){
	p[u].min+=x;
	p[u].max+=x;
	p[u].tag+=x;
}
inline void pushdown(int u){
	if(p[u].tag){
		pushup(u<<1,p[u].tag);
		pushup(u<<1|1,p[u].tag);
		p[u].tag=0;
	}
}
void build(int u,int l,int r){
	p[u].l=l,p[u].r=r,p[u].mid=(l+r)>>1;
	p[u].min=p[u].max=p[u].tag=0;
	if(l==r){
		return;
	}
	build(u<<1,l,p[u].mid);
	build(u<<1|1,p[u].mid+1,r);
}
void modify(int u,int l,int r,int x){
	if(p[u].l==l&&p[u].r==r){
		pushup(u,x);
		return;
	}
	pushdown(u);
	if(r<=p[u].mid){
		modify(u<<1,l,r,x);
	}else if(l>p[u].mid){
		modify(u<<1|1,l,r,x);
	}else{
		modify(u<<1,l,p[u].mid,x);
		modify(u<<1|1,p[u].mid+1,r,x);
	}
	p[u].min=min(p[u<<1].min,p[u<<1|1].min);
	p[u].max=max(p[u<<1].max,p[u<<1|1].max);
}
bool solve(){
	vol=(__int128)w*h*l;
	val[0]={0,w};
	val[1]={0,h};
	val[2]={0,l};
	for(int i=0;i<n;i++){
		vol-=(__int128)(a[i][3]-a[i][0])*(a[i][4]-a[i][1])*(a[i][5]-a[i][2]);
		for(int j=0;j<6;j++){
			val[j%3].push_back(a[i][j]);
		}
	}
	// cerr<<"volume: "<<(long long)vol<<endl;
	if(vol!=0){
		return false;
	}
	for(int i=0;i<3;i++){
		sort(all(val[i]));
		val[i].erase(unique(all(val[i])),val[i].end());
		for(int j=0;j<n;j++)
			for(int k=i;k<6;k+=3){
				a[j][k]=lower_bound(all(val[i]),a[j][k])-val[i].begin();
			}
	}
	// for(int i=0;i<n;i++)for(int j=0;j<6;j++)cerr<<a[i][j]<<" \n"[j==5];
	w=(int)val[0].size()-1;
	h=(int)val[1].size()-1;
	l=(int)val[2].size()-1;
	scanz.clear();
	for(int i=0;i<n;i++){
		scanz.push(a[i][2],{a[i][0],a[i][1],a[i][3],a[i][4],1});	
		scanz.push(a[i][5],{a[i][0],a[i][1],a[i][3],a[i][4],-1});	
	}
	scanz.push(0,{0,0,w,h,-1});
	scanz.push(l,{0,0,w,h,1});
	for(auto &[z,vec]:scanz){
		// log("z=%d\n",z);
		vector<int> vx;
		for(auto &[x0,y0,x1,y1,w]:vec){
			vx.push_back(x0);
			vx.push_back(x1);
		}
		sort(all(vx));
		vx.erase(unique(all(vx)),vx.end());
		scan.clear();
		for(auto &[x0,y0,x1,y1,w]:vec){
			x0=lower_bound(all(vx),x0)-vx.begin();
			x1=lower_bound(all(vx),x1)-vx.begin();
			// log("> %d %d %d %d %d\n",x0,y0,x1,y1,w);	
			scan.push(y0,{x0,x1,w});
			scan.push(y1,{x0,x1,w*-1});
		}
		build(1,0,(int)vx.size()-1);
		for(const auto &[y,vec]:scan){
			// log("  y=%d\n",y);
			for(auto &[l,r,w]:vec){
				// log("  > %d %d %d\n",l,r,w);
				modify(1,l,r-1,w);
				// log("  >seg: %d %d\n",p[1].min,p[1].max);
			}
			if(p[1].min||p[1].max)return false;
		}
	}
	return true;
}
int main(){
#ifdef memset0
	freopen("L.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--){
		cin>>w>>h>>l>>n;
		for(int i=0;i<n;i++)
			for(int j=0;j<6;j++){
				cin>>a[i][j];
			}
		cout<<(solve()?"Yes":"No")<<endl;
	}
}