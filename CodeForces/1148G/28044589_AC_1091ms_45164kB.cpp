/*
#include<bits/stdc++.h>
#undef assert
#define assert(f) if(!(f))printf("Assert: Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__),exit(0)
template<class T> inline void read(T &x){
  x=0; register char c=getchar(); register bool f=0;
  while(!isdigit(c))f^=c=='-',c=getchar();
  while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
  if(x<0)putchar('-'),x=-x;
  if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
template<class T> inline T gcd(T n,T m){return m?gcd(m,n%m):n;}
template<const int N> struct Prime:std::vector<int>{
  Prime(){
    std::vector<bool> vis(N);
    for(int i=2;i<N;i++){
      if(!vis[i])this->push_back(i);
      for(int j:*this){if(i*j>=N)break; vis[i*j]=true; if(!(i%j))break;}
    }
  }
};
const int N=1e5+10,M=1e7+10;
int n,k,A,B,C,a[N],deg[N],v[N][8],l[N],f[M];
Prime<10000> prime;
std::vector<int> pos;
std::unordered_map<int,int> primeid;
void affect(int *v,int l,int x){
  std::function<void(int,int)> dfs=[&](int i,int s){
    if(i==l){
      if(s!=1)f[s]+=x;
      return;
    }
    dfs(i+1,s);
    dfs(i+1,s*v[i]);
  };
  dfs(0,1);
}
int query(int *v,int l){
  int res=0;
  std::function<void(int,int)> dfs=[&](int i,int s){
    if(i==l){
      res+=s<0?-f[-s]:f[s];
      return;
    }
    dfs(i+1,s);
    dfs(i+1,s*-v[i]);
  };
  dfs(0,-1);
  return res;
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  read(n),read(k);
  for(int i=1;i<=n;i++)read(a[i]);
  for(int i=0;i<prime.size();i++)primeid[prime[i]]=i;
  for(int x,i=1;i<=n;i++){
    x=a[i];
    for(int j=0;prime[j]*prime[j]<=x;j++)
      if(x%prime[j]==0){
        v[i][l[i]++]=prime[j];
        while(x%prime[j]==0)x/=prime[j];
      }
    if(x!=1)v[i][l[i]++]=x;
    // printf("a[%d]=%d : ",i,a[i]);
    // for(int x:v[i])printf("%d ",x); putchar('\n');
  }
  for(int i=1;i<=n;i++)affect(v[i],l[i],1);
  for(int i=1;i<=n;i++)deg[i]=query(v[i],l[i])-1;
  for(int i=1;i<=n;i++)affect(v[i],l[i],-1);
  // for(int i=1;i<=n;i++)printf("%d%c",deg[i]," \n"[i==n]);
  int fulldeg=0;
  for(int i=1;i<=n;i++)fulldeg+=deg[i]==n-1;
  if(fulldeg>=k){
    for(int i=1;i<=n;i++)if(deg[i]==n-1)pos.push_back(i);
  }else{
    for(int i=1;i<=n;i++)if(n-1-deg[i]>=2){
      A=i;
      for(int j=1;j<=n;j++)if(j!=A&&gcd(a[i],a[j])==1){
        if(!B){B=j; continue;}
        if(!C){C=j; continue;}
        break;
      }
      break;
    }
    // for(int i=1;i<=n;i++)printf("%d%c",deg[i]," \n"[i==n]);
    // printf("A=%d B=%d C=%d\n",A,B,C);
    if(A){
      assert(B&&C);
      auto getp=[&](int cur){
        std::vector<int> res;
        for(int i=1;i<=n&&res.size()<cur;i++)
          if(i!=A&&i!=B&&i!=C){
            res.push_back(i);
          }
        // assert(res.size()==cur);
        return res;
      };
      auto solve=[&](int cur){
        int res=0;
        std::vector<int> p=getp(cur);
        for(int i:p)affect(v[i],l[i],1);
        for(int i:p)deg[i]=query(v[i],l[i])-1;
        for(int i:p)affect(v[i],l[i],-1);
        for(int i:p)res+=deg[i]!=cur-1;
        return res;
      };
      int l=1,r=n-3,mid,res=-1;
      while(l<=r){
        mid=(l+r)>>1;
        solve(mid)+3>=k?(res=mid,r=mid-1):(l=mid+1);
      }
      assert(~res);
      int now=solve(res);
      std::vector<int> p=getp(res);
      for(int i:p)if(deg[i]!=res-1)pos.push_back(i);
      if(pos.size()<k)pos.push_back(A);
      if(pos.size()<k)pos.push_back(B);
      if(pos.size()<k)pos.push_back(C);
    }else{
      uint64_t all=0;
      std::vector<int> match(n+1);
      std::vector<uint64_t> hsh(n+1);
      std::map<uint64_t,int> map;
      std::map<int,uint64_t> sta;
      std::mt19937_64 rng(20040725^std::chrono::steady_clock::now().time_since_epoch().count());
      for(int i=1;i<=n;i++)hsh[i]=rng(),all^=hsh[i],map[hsh[i]]=i;
      for(int i=1;i<=n;i++)
        for(int x=1;x<(1<<l[i]);x++){
          int s=1;
          for(int j=0;j<l[i];j++)
            if((x>>j)&1)s*=v[i][j];
          sta[s]^=hsh[i];
        }
      for(int i=1;i<=n;i++)if(deg[i]==n-2){
        uint64_t tem=all;
        for(int x=1;x<(1<<l[i]);x++){
          int s=1;
          for(int j=0;j<l[i];j++)
            if((x>>j)&1)s*=v[i][j];
          tem^=sta[s];
        }
        match[i]=map[tem];
        // assert(match[i]);
      }
      for(int i=1;i<=n;i++)
        if(!match[i]||i<match[i])
          pos.push_back(i);
    }
  }
  assert(pos.size()>=k);
  for(int i=0;i<k;i++)print(pos[i]," \n"[i+1==k]);
}
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, k, t;
int pcnt = 0, pri[100000];
bool isp[1000000];
void getprime(void) {
	memset(isp, 1, sizeof(isp));
	for (int i = 2; i < 1000000; i++)
		if (isp[i]) {
			pri[pcnt++] = i;
			for (int j = 2; i * j < 1000000; j++) isp[i * j] = 0;
		}
	return;
}

struct num {
	int fac[10], cnt;
} arr[100000];
int f[10000000];
void add(int i, int pos, int S) {
	if (pos == arr[i].cnt) {
		if (S != 1) f[S]++;
		return;
	}
	add(i, pos + 1, S);
	add(i, pos + 1, S * arr[i].fac[pos]);
	return;
}
void del(int i, int pos, int S) {
	if (pos == arr[i].cnt) {
		if (S != 1) f[S]--;
		return;
	}
	del(i, pos + 1, S);
	del(i, pos + 1, S * arr[i].fac[pos]);
	return;
}
void read(void) {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &t);
		arr[i].cnt = 0;
		for (int j = 0; pri[j] * pri[j] <= t; j++)
			if (t % pri[j] == 0) {
				arr[i].fac[arr[i].cnt++] = pri[j];
				while (t % pri[j] == 0) t /= pri[j];
			}
		if (t > 1) arr[i].fac[arr[i].cnt++] = t;
		if (i < 2 * k) add(i, 0, 1);
	}
	n = 2 * k;
	return;
}

int deg[100000], F = -1, G = -1, H = -1;
int getdeg(int i, int pos, int S, int opt) {
	if (pos == arr[i].cnt) return opt * f[S];
	return getdeg(i, pos + 1, S, opt) + getdeg(i, pos + 1, S * arr[i].fac[pos], -opt);
}
inline bool common(int a, int b) {
	int i = 0, j = 0;
	while (i < arr[a].cnt && j < arr[b].cnt) {
		if (arr[a].fac[i] == arr[b].fac[j]) return 1;
		if (arr[a].fac[i] > arr[b].fac[j])
			j++;
		else
			i++;
	}
	return 0;
}
void getFGH(int i) {
	F = i;
	for (int j = 0; j < n; j++)
		if (!common(i, j)) {
			if (G == -1)
				G = j;
			else if (H == -1)
				H = j;
		}
	return;
}

void solve1(void) {
	for (int i = 0; i < n; i++) del(i, 0, 1);
	int cnt = 0;
	for (int i = 0; i < n && cnt < k; i++)
		if (getdeg(i, 0, 1, -1) == cnt) {
			cnt++;
			printf("%d ", i + 1);
			add(i, 0, 1);
		}
	return;
}
int check(int m) {
	int m0 = m + 1;
	for (int i = 0; i <= m; i++)
		if (i != F && i != G && i != H)
			add(i, 0, 1);
		else
			m0--;
	int x = 0;
	for (int i = 0; i <= m; i++) {
		if (i == F || i == G || i == H) continue;
		deg[i] = m0 - getdeg(i, 0, 1, -1);
		if (deg[i] > 0) x++;
	}
	return x;
}

void solve2(void) {
	for (int i = 0; i < n; i++)
		if (i != F && i != G && i != H) del(i, 0, 1);
	int l = k - 4, r = n - 2, m;
	while (l < r) {
		m = (l + r + 1) >> 1;
		if (check(m) >= k - 3)
			r = m - 1;
		else
			l = m;
		for (int i = 0; i <= m; i++)
			if (i != F && i != G && i != H) del(i, 0, 1);
	}
	m = l + 1;

	int p = check(m);
	if (p >= k) {
		for (int i = 0; i < m && p > k; i++)
			if (i != F && i != G && i != H && deg[i] == 1 && !common(i, m)) {
				p--;
				deg[i] = -1;
			}
	} else {
		for (int i = 0; i < m && p > k - 2; i++)
			if (i != F && i != G && i != H && deg[i] == 1 && !common(i, m)) {
				p--;
				deg[i] = -1;
			}
		printf("%d %d ", F + 1, G + 1);
		if (p == k - 3) printf("%d ", H + 1);
	}
	for (int i = 0; i <= m; i++)
		if (i != F && i != G && i != H && deg[i] > 0) printf("%d ", i + 1);
	return;
}

int main(void) {
	getprime();
	read();
	int w = 0;
	for (int i = 0; i < n; i++) {
		deg[i] = getdeg(i, 0, 1, -1);
		if (deg[i] < n) w++;
		if (F == -1 && deg[i] <= n - 2) getFGH(i);
	}
	if (F == -1) {
		solve1();
		return 0;
	}
	for (int i = 0; i < n; i++) del(i, 0, 1);
	if (check(n - 1) < k - 3) {
		for (int i = 0; i < n && k > 0; i++)
			if (deg[i] == 0) {
				printf("%d ", i + 1);
				k--;
			}
	} else
		solve2();
	return 0;
}