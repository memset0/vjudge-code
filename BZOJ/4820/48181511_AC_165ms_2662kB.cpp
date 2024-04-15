// no spj

#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

template<typename T>
inline T read()
{
	T x=0,f=1;char c=getchar();
	while (c<'0' || c>'9'){if (c=='-')f=-1;c=getchar();}
	while (c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
	return x*f;
}

const int MAXN=305;
const double eps=1e-10;
int n,m,mx;
double res,temp;
char s[MAXN];
double len[MAXN],ans[MAXN],t[MAXN][MAXN];
unsigned long long mi[MAXN],head_Hash[MAXN][MAXN],tail_Hash[MAXN][MAXN];

int main()
{
	n=read<int>();m=read<int>();
	mi[1]=255;len[0]=1;
	for (int i=2;i<=m;i++) mi[i]=mi[1]*mi[i-1];
	for (int i=1;i<=m;i++) len[i]=0.5*len[i-1];
	for (int i=1;i<=n;i++)
	{
		scanf("%s",s+1);t[i][n+1]=1;
		for (int j=1;j<=m;j++) head_Hash[i][j]=head_Hash[i][j-1]*mi[1]+s[j];
		for (int j=1;j<=m;j++) tail_Hash[i][j]=head_Hash[i][m]-head_Hash[i][m-j]*mi[j];
		for (int j=1;j<i;j++)
			for (int k=1;k<=m;k++)
			{
				if (head_Hash[i][k]==tail_Hash[j][k]) t[i][j]+=len[m-k];
				if (head_Hash[j][k]==tail_Hash[i][k]) t[j][i]+=len[m-k]; 
			}
		for (int j=1;j<=m;j++)
			if (head_Hash[i][j]==tail_Hash[i][j]) t[i][i]+=len[m-j];
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=(mx=i)+1;j<=n;j++)
			if (t[j][i]>t[mx][i]) mx=j;
		if (mx!=i) swap(t[i],t[mx]);
		for (int j=1;j<=n;j++)
		{
			if (i==j) continue;
			temp=t[j][i]/t[i][i];
			if (fabs(temp)<=eps) continue;
			for (int k=i+1;k<=n+1;k++) t[j][k]-=t[i][k]*temp;
		}
	}
	for (int i=1;i<=n;i++) ans[i]=t[i][n+1]/t[i][i],res+=ans[i];
	for (int i=1;i<=n;i++) printf("%.10lf\n",ans[i]/res);
	return 0;
}