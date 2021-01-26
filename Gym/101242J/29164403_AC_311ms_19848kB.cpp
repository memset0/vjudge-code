#include<bits/stdc++.h>
using namespace std;
const int N = 3e5+5;
typedef long long ll;

struct node{
	int x,y;
	node(int x=0,int y=0):x(x),y(y){}
	node operator + (const node b)const{return node(x+b.x,y+b.y);}
	node operator - (const node b)const{return node(x-b.x,y-b.y);}
	ll operator * (const node b){return 1ll*x*b.y - 1ll*y*b.x;}
	bool operator < (const node b)const{
		return x == b.x ? y < b.y : x < b.x;
	}
	node get(){
		node r(-y,x);
		if(r.x < 0 || (r.x==0 && r.y) < 0)r.x=-r.x,r.y=-r.y;
		return r;
	}
	inline void output(){
		cout << "(" << x << "," << y << ")";
	}
};

node _cov[N];int sz;
node cov[N];int top,cutter;
node cov2[N];int top2;
inline void build_conv(){
	// cout << sz << "?? " << endl;
	sort(_cov+1,_cov+sz+1);
	for(int i=1;i<=sz;i++){
		// _cov[i].output();
		while(top>1 && (cov[top]-cov[top-1])*(_cov[i]-cov[top])<=0)--top;
		cov[++top]=_cov[i];
	}
	for(int i=sz;i>=1;i--){
		// _cov[i].output();
		while(top2>1 && (cov2[top2]-cov2[top2-1])*(_cov[i]-cov2[top2])<=0)--top2;
		cov2[++top2]=_cov[i];
	}
	cutter = top;
	for(int i=2;i<top2;i++)cov[++top]=cov2[i];
	// cout << top << "|" << cutter << "??" << endl;
	// for(int i=1;i<=top;i++)cov[i].output();
	// puts("");
}
node nd[N];
int type[N];
int n;
int ans=0;
typedef double db;
int rcmp(db a){
	if(a<-1e-6)return -1;
	if(a>1e-6)return 1;
	return 0;
}
bool judge(node a,node b,node c){
	int x=a.x+a.y,y=b.x+b.y,z=c.x+c.y;
	return x>=min(y,z)&&x<=max(y,z);
}
bool judge_in(node d){
	if(d.x<0)return 0;
	if(d.x==0&&d.y==0)return 1;
	int l=1,r=top;
	while(l<r){
		int mid=(l+r+1)>>1;
		if(cov[mid]*d>0)l=mid;
		else r=mid-1;
	}
	if(l==top)return 0;
	node a = d-cov[l], b = cov[l+1]-d;
	if(b.x==0&&b.y==0)return 1;
	if(a*b==0){
		return judge(d,cov[l],cov[l+1]);
	}
	return a*b<=0;
}

int query(node d,int l,int r,int x){
	while(l<r){
		int mid = (l+r)>>1;
		// cout << mid << "???" << endl;
		// (cov[mid+1]-d).output();
		// (cov[mid]-d).output();
		if((cov[mid+1]-d)*(cov[mid]-d)*x>=0)l=mid+1;
		else r=mid;
	}
	return l;
}

vector < pair<node,int> > op;
int ans2=0;
inline void get_range(node d){
	node a,b;
	if(d.x<0){
		a = (cov[query(d,1,cutter,1)] - d).get();
		b = (cov[query(d,cutter,top+1,-1)] - d).get();
		op.push_back(make_pair(a,1));
		op.push_back(make_pair(b,-1));
	}else{
		int l=1,r=top;
		while(l<r){
			int mid=(l+r+1)>>1;
			if(cov[mid]*d>0)l=mid;
			else r=mid-1;
		}
		// cout << "L=" << l << "?" << endl;
		a = (cov[query(d,l+1,top+1,1)] - d).get();
		b = (cov[query(d,1,l,-1)] - d).get();
		op.push_back(make_pair(a,1));
		op.push_back(make_pair(b,-1));
	}
	// a.output();b.output();cout << "!!" << endl;
	if(a*b<0)ans++;
}

int main()
{
	// freopen("6.in","r",stdin);
	cin >> n;
	for(int i=1;i<=n;i++){
		// cout << "reading" << i << endl;
		scanf("%d%d%d",&nd[i].x,&nd[i].y,&type[i]);
		if(type[i]==1){
			_cov[++sz] = nd[i];
			// ++ans;
		}
	}
	// cout << sz << endl;
	build_conv();
	// cout << "???" << endl;
	if(sz==1){
		cout << 1 << endl;
		return 0;
	}
	for(int i=1;i<=n;i++)nd[i]=nd[i]-cov[1];
	for(int i=2;i<=top;i++)cov[i]=cov[i]-cov[1];
	cov[1]=node(0,0);
	cov[top+1] = cov[1];
	for(int i=1;i<=n;i++){
		// nd[i].output();cout << "is checking" << endl;
		bool tmp = judge_in(nd[i]);
		// cout << tmp << "?" << endl;
		if(!tmp){
			get_range(nd[i]);
		}else ans2++;
	}
	sort(op.begin(),op.end(),[&](pair<node,int> a,pair<node,int> b){
		return a.first*b.first==0?a.second>b.second:a.first*b.first>0;
	});
	int cur=ans+ans2,mn=ans+ans2;
	// cout << ans << ":" << ans2 << endl;
	for(auto v:op){
		// v.first.output();
		// cout << v.second << endl;
		cur+=v.second;
		mn=min(mn,cur);
	}
	cout << mn << endl;
}
/* 
5
0 0 1
100 100 1
50 50 0
50 25 0
25 50 0
 */