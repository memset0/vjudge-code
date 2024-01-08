#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define debug(x) cerr<<#x<<": "<<x<<endl
using namespace std;
using ll=long long;
using lf=long double;
const int N=5e5,INF=1e9;
const int m1=1e9+7,b1=3,m2=998244353,b2=1145;
struct Hash{
	int f,s;
	bool operator==(const Hash&y)const{
		return f==y.f&&s==y.s;
	}
	Hash operator+(const Hash&y)const{
		return(Hash){f+y.f>=m1?f+y.f-m1:f+y.f,s+y.s>=m2?s+y.s-m2:s+y.s};
	}
	Hash operator-(const Hash&y)const{
		return(Hash){f-y.f<0?f-y.f+m1:f-y.f,s-y.s<0?s-y.s+m2:s-y.s};
	}
	Hash operator*(const Hash&y)const{
		return(Hash){1ll*f*y.f%m1,1ll*s*y.s%m2};
	}
}h[N+10],pw[(N<<1)+10],iv[N+10];
int B,n,m,Q,p[N+10],sz,prt[N+10],tmpl,tmpr,pi;
int li[N+10],ri[N+10],mn[(N<<2)+10];
char t[N+10],s[N+10];
vector<int>pos[N+10],dl[N+10];
vector<int>tl[N+10],tr[N+10],ti[N+10];
int POW(int x,int y,int mod){
	int ret=1;
	while(y)y&1?ret=1ll*ret*x%mod:0,x=1ll*x*x%mod,y>>=1;
	return ret;
}
Hash Gethash(int l,int r){
	//cout<<"GET "<<l<<" "<<r<<"="<<h[r].f<<"-"<<1ll*h[l-1].f*pw[r-l+1].f%m1<<"\n";
	return h[r]-h[l-1]*pw[r-l+1];
}
bool Check(int x){
	//cout<<"CHECK "<<x<<"\n";
	Hash hv=Gethash(li[x],li[x]+B-1);
	//cout<<"HV="<<hv.f<<"\n";
	int num=x/B;
	//cout<<"ALL="<<Gethash(li[x],ri[x]).f<<"\n";
	//cout<<"T="<<hv.f<<"*"<<((Hash){pw[num*B].f-1,pw[num*B].s-1}*iv[B]).f<<"*"<<pw[x%B].f<<"+"<<Gethash(li[x],li[x]+x%B-1).f<<"\n";
	return Gethash(li[x],ri[x])==hv*(Hash){pw[num*B].f-1,pw[num*B].s-1}*iv[B]*pw[x%B]+Gethash(li[x],li[x]+x%B-1);
}
void Build(int x,int l,int r){
	if(l==r)return(void)(mn[x]=INF);
	int mid=(l+r>>1);
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	mn[x]=min(mn[x<<1],mn[x<<1|1]);
}
void Del(int x,int l,int r,int id,int v){
	if(l==r)return(void)(mn[x]=v);
	int mid=(l+r>>1);
	id<=mid?Del(x<<1,l,mid,id,v):Del(x<<1|1,mid+1,r,id,v);
	mn[x]=min(mn[x<<1],mn[x<<1|1]);
}
int Que(int x,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return mn[x];
	if(r<ql||qr<l)return INF;
	int mid=(l+r>>1);
	return min(Que(x<<1,l,mid,ql,qr),Que(x<<1|1,mid+1,r,ql,qr));
}
int l,r,mid;
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>t+1;
	for(int i=n;i>=1;--i)if('a'<=t[i]&&t[i]<='z')s[++sz]=t[i];
	if('a'<=t[1]&&t[1]<='z')li[1]=ri[1]=sz;
	else li[1]=ri[1]=sz+1;
	for(int i=1;i<=n;++i)if('A'<=t[i]&&t[i]<='Z')s[++sz]=t[i]+'a'-'A';
	pw[0]=(Hash){1,1};
	pw[1]=(Hash){b1,b2};
	for(int i=2;i<=(n<<1);++i)pw[i]=pw[i-1]*pw[1];
	for(int i=1;i<=n;++i){
		iv[i]=(Hash){POW(pw[i].f-1,m1-2,m1),POW(pw[i].s-1,m2-2,m2)};
	}
	for(int i=1;i<=n;++i)h[i]=h[i-1]*pw[1]+(Hash){s[i]-'a'+1,s[i]-'a'+1};
	for(int i=2;i<=n;++i){
		li[i]=li[i-1],ri[i]=ri[i-1];
		if('a'<=t[i]&&t[i]<='z')--li[i];
		else ++ri[i];
	}
	for(int i=1;i<=n;++i){
		//cout<<"-------------------I="<<i<<"\n";
		B=i;
		l=i,r=n;
		while(l<r){
			mid=(l+r+1>>1);
			if(Check(mid))l=mid;
			else r=mid-1;
		}
		//cout<<"L="<<l<<"\n";
		dl[l+1].push_back(i);
		
	}
	cin>>m;
	for(int i=1;i<=m;++i)cin>>p[i],pos[p[i]].push_back(i);
	Build(1,1,m);
	cin>>Q;
	for(int i=1;i<=Q;++i){
		cin>>pi>>tmpl>>tmpr;
		tl[pi].push_back(tmpl),tr[pi].push_back(tmpr),ti[pi].push_back(i);
	}
	for(int i=1;i<=n;++i){
		for(int k:pos[i])Del(1,1,m,k,i);
		for(int j:dl[i])for(int k:pos[j])Del(1,1,m,k,INF);
		for(int j=0;j<tl[i].size();++j){
			prt[ti[i][j]]=Que(1,1,m,tl[i][j],tr[i][j]);
		}
	}
	for(int i=1;i<=Q;++i)cout<<(prt[i]==INF?-1:prt[i])<<"\n";
	return 0;
}
/*
7
AABAAba
9
4 3 2 1 7 5 3 6 1
6
1 4 4
2 1 4
2 1 3
3 3 5
5 4 7
7 8 9
*/