#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define Fast_IO ios::sync_with_stdio(false);
#define DEBUG fprintf(stderr,"Running on Line %d in Function %s\n",__LINE__,__FUNCTION__)
//mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
#define fir first
#define sec second
#define mod 998244353
#define ll long long
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
inline int read()
{
	char ch=getchar(); int nega=1; while(!isdigit(ch)) {if(ch=='-') nega=-1; ch=getchar();}
	int ans=0; while(isdigit(ch)) {ans=ans*10+ch-48;ch=getchar();}
	if(nega==-1) return -ans;
	return ans;
}
typedef pair<int,int> pii;
void print(vector<int> x){for(int i=0;i<(int)x.size();i++) printf("%d%c",x[i]," \n"[i==(int)x.size()-1]);}
#define N 505
long double C[N][N],f[N][N],g[N][N];
int n,d,r;
signed main()
{
	cin>>n>>d>>r;
	C[0][0]=1;
	for(int i=1;i<N;i++)
	{
		C[i][0]=1;
		for(int j=1;j<N;j++) C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int t=1;t*i<=d;t++)
		{
			int go=i*t;
			for(int j=go;j<=d;j++)
			{
				for(int k=0;k<i;k++)
				{
					f[i][j]+=C[i][k]*f[k][j-go];
					g[i][j]+=C[i][k]*(g[k][j-go]+min(i,r)*t*f[k][j-go]);
				}
			}
		}
	}
	// for(int i=0;i<=n;i++)
	// {
		// for(int j=0;j<=d;j++) printf("%.1Lf ",f[i][j]);
		// cout<<"\n";
	// }
	long double A=0,B=0;
	for(int i=1;i<=n;i++) A+=C[n][i]*g[i][d],B+=C[n][i]*f[i][d];
	printf("%.6Lf\n",A/B+r);
	return 0;
}

 