#include<set>
#include<map>
#include<deque>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<string>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<climits>
#include<complex>
#include<algorithm>
#define ll long long
#define pb push_back
using namespace std;
 
const int maxn = 110000;
 
int n,m,K;
int a[maxn],et[maxn];
vector<int>V[maxn];
int s[maxn],nowd[maxn];
 
int main()
{
	//freopen("tmp.in","r",stdin);
	//freopen("tmp.out","w",stdout);
	
	scanf("%d%d",&m,&K);
	for(int i=1;i<=m;i++) scanf("%d",&a[i]),n+=a[i];
	for(int i=1;i<=K;i++) scanf("%d",&et[i]);
	if(K>=n)
	{
		int nk=K%n;
		for(int i=1;i<=nk;i++) et[i]=et[K-(nk-i)];
		K=nk;
	}
	
	for(int i=1;i<=m;i++)
	{
		int c=a[i];
		for(int j=1;j<c;j++)
		{
			int t=(ll)n*j/c;
			if((ll)t*c<(ll)n*j) t++;
			V[t].push_back(i);
		}
		V[n].push_back(i);
	}
	
	for(int i=1;i<=K;i++)
	{
		s[et[i]]++;
		for(int j=0;j<(int)V[i].size();j++) nowd[V[i][j]]++;
	}
	int oth=0;
	for(int i=K+1;i<=n;i++)
	{
		oth++; int ok=1;
		for(int j=0;j<(int)V[i].size();j++)
		{
			int k=V[i][j]; nowd[k]++;
			if(s[k]<nowd[k])
			{
				if(!oth) { ok=0; break; }
				oth--; s[k]++;
			}
		}
		if(!ok) return printf("%d\n",i-K-1),0;
	}
	puts("forever");
	
	return 0;
}
