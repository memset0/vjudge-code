#include<bits/stdc++.h>
using namespace std;
using pattern=pair<int,short>;
const int N=5e4+9;
int n,m,tot,a[N],rt[N];
vector<int> val,pos[N];
struct node{
	int lc,rc;
	pattern x;
}p[N*45];
inline string to_string(pattern a){
	string s;
	for(int i=0;i<a.second;i++){
		s+='0'+(a.first&1);
		a.first>>=1;
	}
	reverse(s.begin(),s.end());
	return s;
}
inline vector<int> expand(pattern s){
	vector<int> a(s.second);
	for(int i=0;i<s.second;i++){
		a[i]=s.first&1;
		s.first>>=1;
	}
	reverse(a.begin(),a.end());
	return a;
}
pattern tab[512][512][10][10];
inline pattern merge(const pattern &a,const pattern &b){
	if(a.second==-1)return a;
	if(b.second==-1)return b;
	auto &it=tab[a.first][b.first][a.second][b.second];
	if(it.second!=0)return it;
	pattern t=a;
	for(int c:expand(b)){
		t.first=t.first<<1|c;
		t.second++;
		if(t.second>=4){
			if((t.first&15)==15){
				t.second=-1;
				break;
			}
		}
		if(t.second>=3){
			if((t.first&7)==0)t.first>>=2,t.second-=2;
			else if((t.first&7)==2)t.first>>=2,t.second-=2;
			else if((t.first&7)==5)t.first=(t.first>>3)<<1|1,t.second-=2;
		}
		if(t.second>=6){
			if((t.first&63)==51){
				t.first>>=4;
				t.second-=4;
			}
		}
	}
	it=t;
	// assert(t.second<=9);
	return t;
}
map<pattern,bool> mp;
inline bool check(const pattern &s){
	if(s.second==-1)return true;
	auto it=mp.find(s);
	if(it!=mp.end())return it->second;
	vector<int> a=expand(s);
	for(int i=0;i+2<a.size();i++){
		pattern t={0,s.second-2};
		int c[2]={0,0};
		for(int j=0;j<i;j++)t.first=t.first<<1|a[j];
		for(int j=i;j<=i+2;j++)c[a[j]]++;
		t.first=t.first<<1|(c[0]>c[1]?0:1);
		for(int j=i+3;j<a.size();j++)t.first=t.first<<1|a[j];
		if(check(t)){
			return mp[s]=true;
		}
	}
	return mp[s]=false;
}
void build(int &u,int l,int r){
	u=++tot;
	if(l==r){
		p[u].x={0,1};
		return;
	}
	int mid=(l+r)>>1;
	build(p[u].lc,l,mid);
	build(p[u].rc,mid+1,r);
	p[u].x=merge(p[p[u].lc].x,p[p[u].rc].x);
}
void modify(int &u,int v,int k,int l,int r){
	u=++tot;
	p[u].lc=p[v].lc,p[u].rc=p[v].rc;
	if(l==r){
		p[u].x={1,1};
		return;
	}
	int mid=(l+r)>>1;
	if(k<=mid){
		modify(p[u].lc,p[v].lc,k,l,mid);
	}else{
		modify(p[u].rc,p[v].rc,k,mid+1,r);
	}
	p[u].x=merge(p[p[u].lc].x,p[p[u].rc].x);
}
pattern query(int u,int ql,int qr,int l,int r){
	// fprintf(stderr,"query %d %d %d %d %d\n",u,ql,qr,l,r);
	if(ql==l&&qr==r)return p[u].x;
	int mid=(l+r)>>1;
	if(qr<=mid){
		return query(p[u].lc,ql,qr,l,mid);
	}else if(ql>mid){
		return query(p[u].rc,ql,qr,mid+1,r);
	}else{
		return merge(query(p[u].lc,ql,mid,l,mid),query(p[u].rc,mid+1,qr,mid+1,r));
	}
}
int main(){
#ifdef memset0
	// freopen("F.in","r",stdin);
	freopen("F0.in","r",stdin);
	freopen("F0.out","w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	mp[{0,1}]=false;
	mp[{1,1}]=true;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		val.push_back(a[i]);
	}
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	for(int i=1;i<=n;i++){
		int p=lower_bound(val.begin(),val.end(),a[i])-val.begin();
		pos[p].push_back(i);
	}
	build(rt[val.size()],1,n);
	for(int i=(int)val.size()-1;i>=0;i--){
		int lst=rt[i+1];
		for(int k:pos[i]){
			modify(rt[i],lst,k,1,n);
			lst=rt[i];
		}
	}
	// cerr<<"!!!!"<<endl;
	// cerr<<to_string(p[1].x)<<endl;
	cin>>m;
	for(int ql,qr,i=1;i<=m;i++){
		cin>>ql>>qr;
		int l=0,r=(int)val.size()-1,mid,ans=-1;
		// cerr<<"! "<<ql<<" "<<qr<<endl;
		while(l<=r){
			mid=(l+r)>>1;
			// cerr<<"> "<<val[mid]<<" "<<check(query(rt[mid],ql,qr,1,n))<<endl;
			// cerr<<to_string(query(rt[mid],ql,qr,1,n))<<endl;
			// for(int i=1;i<=n;i++)cerr<<to_string(query(rt[mid],i,i,1,n))<<" \n"[i==n];
			if(check(query(rt[mid],ql,qr,1,n))){
				ans=mid;
				l=mid+1;
			}else{
				r=mid-1;
			}
		}
#ifdef memset0
		assert(ans!=-1);
#endif
		cout<<val[ans]<<endl;
	}
}	