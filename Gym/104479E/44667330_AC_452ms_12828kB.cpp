#include<bits/stdc++.h>
using namespace std;
const int N=3e5+9,V=1e4+9;
int n,m,s,tot,pos,bln[N],a[N],ans[N],cnt[N],bkt[N];
bool vis[V];
vector<int> pri;
struct TRI{
	int s[N];
	inline void add(int k){for(;k<N;k+=k&-k)s[k]++;}
	inline int ask(int k){int r=0;for(;k;k-=k&-k)r+=s[k];return r;}
}one,two;
void ins(int k){
	// cerr<<"ins "<<k<<" "<<a[k]<<endl;
	if(a[k]==-1)return;
	// cerr<<"! "<<pri[a[k]-1]<<endl;
	++tot;
	--bkt[cnt[a[k]]];
	++cnt[a[k]];
	++bkt[cnt[a[k]]];
	if(cnt[a[k]]>pos)pos=cnt[a[k]];
}
void del(int k){
	// cerr<<"del "<<k<<" "<<a[k]<<endl;
	if(a[k]==-1)return;
	// cerr<<"! "<<pri[a[k]-1]<<endl;
	--tot;
	--bkt[cnt[a[k]]];
	--cnt[a[k]];
	++bkt[cnt[a[k]]];
	while(!bkt[pos])--pos;
}
struct query{
	int l,r,id;
	inline bool operator<(const query &rhs)const{
		if(bln[l]==bln[rhs.l]){
			if(bln[l]&1)return r<rhs.r;
			return r>rhs.r;
		}
		return l<rhs.l;
	}
	int solve()const{
		int ones=one.ask(r)-one.ask(l-1);
		// fprintf(stderr,"![%d] (%d,%d) : ones=%d pos=%d tot=%d\n",id,l,r,ones,pos,tot);
		if(ones==r-l+1){
			return -1;
		}
		if(tot==0){
			return ones;
		}
		if(pos==tot&&(two.ask(r)-two.ask(l-1))==0){
			return -1;
		}
		if((pos<<1)<=tot){
			return ((tot+1)>>1)+ones;
		}
		return pos+ones;
	}
}q[N];
void init_prime(){
	for(int i=2;i<V;i++){
		if(!vis[i]){
			pri.push_back(i);
		}
		for(int j=i*2;j<V;j+=i){
			vis[j]=true;
		}
	}
}
int setup(int x){
	int p=0;
	for(int i=0;i<pri.size()&&pri[i]*pri[i]<=x;i++)
		if(x%pri[i]==0){
			while(x%pri[i]==0){
				x/=pri[i];
			}
			if(p){
				return -1;
			}else{
				p=i+1;
			}
		}
	if(x>1){
		int k=lower_bound(pri.begin(),pri.end(),x)-pri.begin();
		assert(k!=pri.size());
		if(p){
			return -1;
		}else{
			p=k+1;
		}
	}
	return p;
}
int main(){
#ifdef memset0
	freopen("E.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	init_prime();
	bkt[0]=1919810;
	cin>>n>>m;
	while(s*s<=n)s++;
	for(int i=1;i<=n;i++)bln[i]=(i-1)/s+1;
	for(int x,i=1;i<=n;i++){
		cin>>a[i];
		x=a[i];
		for(int i=0;i<pri.size()&&pri[i]*pri[i]<=x;i++)
			if(x%pri[i]==0){
				while(x%pri[i]==0){
					x/=pri[i];
				}
			}
		if(x>1){
			pri.push_back(x);
		}
	}
	sort(pri.begin(),pri.end());
	pri.erase(unique(pri.begin(),pri.end()),pri.end());
	for(int i=1;i<=n;i++){
		a[i]=setup(a[i]);
		if(a[i]==0){
			a[i]=-1;
			one.add(i);
		}else if(a[i]==-1){
			two.add(i);
		}
		// cerr<<a[i]<<endl;
	}
	for(int i=1;i<=m;i++){
		cin>>q[i].l>>q[i].r;
		q[i].id=i;
	}
	sort(q+1,q+m+1);
	int ul=q[1].l,ur=q[1].r;
	for(int i=ul;i<=ur;i++){
		ins(i);
	}
	ans[q[1].id]=q[1].solve();
	for(int i=2;i<=m;i++){
		while(ul>q[i].l)ins(--ul);
		while(ur<q[i].r)ins(++ur);
		while(ur>q[i].r)del(ur--);
		while(ul<q[i].l)del(ul++);
		ans[q[i].id]=q[i].solve();
	}
	for(int i=1;i<=m;i++)cout<<ans[i]<<'\n';
}