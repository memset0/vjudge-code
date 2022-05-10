#include<bits/stdc++.h>
using namespace std;
const int N = 5e4+5;
typedef pair<int,int> pir;
typedef pair<int,int> pi;
int n;pir a[N];int dan[N];
#define mid ((l+r)>>1)
pi t[N<<2];
int s[N<<2],tag[N<<2];
inline void build(int x,int l,int r){
	if(l==r){
		t[x] = pi(a[l].second,l);
		tag[x] = 0, s[x] = n-l+1;
		return;
	}
	build(x<<1,l,mid),build(x<<1|1,mid+1,r);
	tag[x] = 0;
	s[x] = min(s[x<<1],s[x<<1|1]);
	t[x] = min(t[x<<1],t[x<<1|1]);
	// cout << x << " " << l << "-" << r << ":" << t[x].first << "," << t[x].second << endl;
}
void pushdown(int x,int l,int r){
	s[x] += tag[x];
	if(l^r)tag[x<<1]+=tag[x], tag[x<<1|1]+=tag[x];
	tag[x] = 0;
}
inline int bs(int x,int l,int r,int M){
	// if(x==1)cout << M << " " << s[x] << endl;
	pushdown(x,l,r);
	if(l==r){return s[x] >= M ? r : r-1;}
	if(s[x] >= M)return r;
	pushdown(x<<1,l,mid);
	if(s[x<<1] < M)return bs(x<<1,l,mid,M);
	else return bs(x<<1|1,mid+1,r,M);
}
inline void add(int x,int l,int r,int ql,int qr,int sum){
	pushdown(x,l,r);
	if(ql<=l&&qr>=r){tag[x] += sum;return;}
	if(ql<=mid)add(x<<1,l,mid,ql,qr,sum);
	if(qr>mid)add(x<<1|1,mid+1,r,ql,qr,sum);
	pushdown(x<<1,l,mid),pushdown(x<<1|1,mid+1,r);
	s[x] = min(s[x<<1],s[x<<1|1]);
}
inline pi find(int x,int l,int r,int ql,int qr){
	pushdown(x,l,r);
	if(ql<=l&&qr>=r)return t[x];
	if(qr<=mid)return find(x<<1,l,mid,ql,qr);
	if(ql>mid)return find(x<<1|1,mid+1,r,ql,qr);
	return min(find(x<<1,l,mid,ql,qr),find(x<<1|1,mid+1,r,ql,qr));
}
void del(int x,int l,int r,int p){
	pushdown(x,l,r);
	if(l==r){t[x]=pi(2000000000,l);return;}
	if(p<=mid)del(x<<1,l,mid,p);
	else del(x<<1|1,mid+1,r,p);
	t[x]=min(t[x<<1],t[x<<1|1]);
}
#undef mid
vector<int> ans;
inline bool check(int Lim){
	// cout << Lim << "|" << endl;
	for(int i=1;i<=n;i++)dan[i] = n;
	ans.clear();
	build(1,1,n);
	int Tar=1;
	for(int i=1;i<=n;i++){
		int le = bs(1,1,n,i+1);
		le=min(le+1,n);
		// cout << i << ":" << le << endl;
		int id = find(1,1,n,1,le).second;
		ans.push_back(id);
		int Ans = id;
		// cout << i << " ch " << id << endl;
		if(dan[id] < i || dan[id] == 0x3f3f3f3f)return 0;
		if(Ans!=n)add(1,1,n,Ans+1,n,1);
		add(1,1,n,Ans,Ans,0x3f3f3f3f-dan[Ans]);
		dan[Ans] = 0x3f3f3f3f;
		del(1,1,n,Ans);
		if(Lim+i<=n){
			while(Tar <= n && a[Ans].second >= a[Tar].first){
				if(dan[Tar] != 0x3f3f3f3f){
					// cout << "ad " << Tar << " " << i+Lim << endl;
					add(1,1,n,Tar,Tar,i+Lim-dan[Tar]);
					dan[Tar]=i+Lim;
				}
				Tar++;
			}
		}
	}
	return 1;
}

int main()
{
	int T;cin >> T;
	while(T--){
		cin >> n;
		for(int i=1;i<=n;i++){
			scanf("%d%d",&a[i].first,&a[i].second);
		}
		sort(a+1,a+n+1);
		int l=0,r=n;
		while(l<r){
			int mid = (l+r)>>1;
			if(check(mid)) r=mid;
			else l=mid+1;
		}
		check(l);
		printf("%d\n",l);
		for(int i=0;i<n;i++)printf("%d %d\n",a[ans[i]].first,a[ans[i]].second);
	}
}