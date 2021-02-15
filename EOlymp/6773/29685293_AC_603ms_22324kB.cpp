// ====================================
//   author: M_sea
//   website: https://m-sea-blog.com/
// ====================================
#include <bits/stdc++.h>
#define file(x) freopen(#x".in","r",stdin); freopen(#x".out","w",stdout)
#define debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
typedef long long ll;

int read() {
	int X=0,w=1; char c=getchar();
	while (c<'0'||c>'9') { if (c=='-') w=-1; c=getchar(); }
	while (c>='0'&&c<='9') X=X*10+c-'0',c=getchar();
	return X*w;
}

const int N=1000000+10;
const int inf=0x3f3f3f3f;

int n,x[N][3][2];
vector<int> v[3];

bool check(int d1,int d2) {
	if (!v[d1].size()||!v[d2].size()) return 1;
	int d=d1,L=inf,R=-inf;
	for (int i:v[d1])
		L=min(L,x[i][d][1]),R=max(R,x[i][d][0]);
	for (int i:v[d2])
		if (x[i][d][0]>L||x[i][d][1]<R) return 0;
	d=d2,L=inf,R=-inf;
	for (int i:v[d1])
		L=min(L,x[i][d][1]),R=max(R,x[i][d][0]);
	for (int i:v[d2])
		if (x[i][d][0]>L||x[i][d][1]<R) return 0;
	d=3-d1-d2,L=inf,R=-inf;
	for (int i:v[d1])
		L=min(L,x[i][d][1]),R=max(R,x[i][d][0]);
	for (int i:v[d2])
		if (x[i][d][0]>L||x[i][d][1]<R) return 0;
	return 1;
}

int main() {
	int T=read();
	while (T--) {
		v[0].clear(),v[1].clear(),v[2].clear();
		n=read();
		for (int i=1;i<=n;++i) {
			x[i][0][0]=read(),x[i][1][0]=read(),x[i][2][0]=read();
			x[i][0][1]=read(),x[i][1][1]=read(),x[i][2][1]=read();
			if (x[i][0][0]>x[i][0][1]) swap(x[i][0][0],x[i][0][1]);
			if (x[i][1][0]>x[i][1][1]) swap(x[i][1][0],x[i][1][1]);
			if (x[i][2][0]>x[i][2][1]) swap(x[i][2][0],x[i][2][1]);
			if (x[i][0][0]==x[i][0][1]) v[0].emplace_back(i);
			if (x[i][1][0]==x[i][1][1]) v[1].emplace_back(i);
			if (x[i][2][0]==x[i][2][1]) v[2].emplace_back(i);
		}
		if (v[0].size()&&(v[1].size()||v[2].size())&&check(0,1)&&check(0,2)) { puts("YES"); continue; }
		if (v[1].size()&&(v[0].size()||v[2].size())&&check(1,0)&&check(1,2)) { puts("YES"); continue; }
		if (v[2].size()&&(v[0].size()||v[1].size())&&check(2,0)&&check(2,1)) { puts("YES"); continue; }
		puts("NO");
	}
	return 0;
}