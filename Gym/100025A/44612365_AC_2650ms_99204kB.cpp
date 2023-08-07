#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using uint=unsigned int;
const int N=1e4+9,V=1e8+9;
int p,m,q[N][2],pri[N];
bool used[V];
map<int,int> mp;
struct barrett {
  uint _m;
  ull im;
	void init(uint m){
		_m=m;
		im=(ull)(-1)/m+1;
	}
  uint umod()const{return _m;}
  uint mul(uint a, uint b)const{
    ull z=a;
    z*=b;
    ull x=(ull)(((unsigned __int128)(z)*im)>>64);
    ull y=x*_m;
    return (uint)(z-y+(z<y?_m:0));
  }
}bar;
inline int power(int a,int b){
	int s=1;
	for(;b;b>>=1,a=bar.mul(a,a))
		if(b&1)s=bar.mul(s,a);
	return s;
}
inline ll exgcd(ll a,ll b,ll &x,ll &y){
	if(a==0&&b==0)return -1;
	if(b==0){x=1,y=0; return a;}
	ll d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}
ll get_inverse(ll a,ll n){
	ll x,y;
	ll d=exgcd(a,n,x,y);
	if(d==1)return (x%n+n)%n;
	return -1;
}
vector<pair<int,int>> get_factor(int x){
	vector<pair<int,int>> fac;
	for(int i=2;i*i<=x;i++)
		if(x%i==0){
			int cnt=0;
			while(x%i==0){
				x/=i;
				++cnt;
			}
			fac.emplace_back(i,cnt);
		}
	if(x>1){
		fac.emplace_back(x,1);
	}
	sort(fac.begin(),fac.end());
	return fac;
}
int get_g(int p){
	if(p==2)return 1;
	auto fac=get_factor(p-1);
	for(int g=2;g<p;g++){
		bool fl=true;
		for(const auto &it:fac){
			int t=(p-1)/it.first;
			if(power(g,t)==1){
				fl=false;
				break;
			}
		}
		if(fl){
			return g;
		}
	}
	return -1;
}
inline void add_number(int x){
	if(x&&!used[x]){
		used[x]=true;
		mp[x]=-1;
	}
}
inline int query(int x,int y){
	if(x==0&&y==1)return 0;
	if(x==0&&y==0)return 1;
	if(x==0)return -1;
	if(y==0)return -1;
	if(y==1)return 0;
	if(x==y)return 1;
	x=mp[x],y=mp[y];
	int z=p-1;
	// cerr<<x<<" "<<y<<" "<<z<<endl;
	int gcd=__gcd(x,z);
	if(y%gcd!=0){
		return -1;
	}
	x/=gcd,y/=gcd,z/=gcd;
	// cerr<<x<<" "<<y<<" "<<z<<endl;
	auto inv_x=get_inverse(x,z);
	// cerr<<"inv_x="<<inv_x<<endl;
	return (ll)y*inv_x%z;
}
int main(){
#ifdef memset0
	freopen("A.in","r",stdin);
#else
	freopen("alot.in","r",stdin);
	freopen("alot.out","w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>p>>m;
	bar.init(p);
	int g=get_g(p);
	for(int i=1;i<=m;i++){
		cin>>q[i][0]>>q[i][1];
		add_number(q[i][0]);
		add_number(q[i][1]);
	}
	// cerr<<"g of "<<p<<" is "<<g<<endl;
	cerr<<"clock: "<<clock()/(double)CLOCKS_PER_SEC<<endl;
	for(int x=1,i=0;i<p-1;x=bar.mul(x,g),i++){
		// cerr<<"> "<<x<<" "<<i<<endl;
		if(used[x]){
			mp[x]=i;
		}
	}
	cerr<<"clock: "<<clock()/(double)CLOCKS_PER_SEC<<endl;
	for(int i=1;i<=m;i++){
		cout<<query(q[i][0],q[i][1])<<'\n';
	}
}