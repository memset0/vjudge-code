#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
#include<stack>
#include<cstring>
#include<bitset>
#include<string>
#define ll long long
#define maxn 5005
#define re(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
inline int read(){char c=getchar();int f=1;int ans = 0;while(c>'9'||c<'0'){if(c=='-')f=-f;c=getchar();}while(c<='9'&&c>='0'){ans =ans*10+c-'0';c=getchar();}return ans*f;}
int n,m,fa[maxn];
bitset<maxn>bit[maxn];
int find(int x)
{return fa[x]==x?x:fa[x]=find(fa[x]);}
int main()
{
	n=read(),m=read();
	re(i,1,n) fa[i] = i;
	int ans = n;
	while(m--)
	{
		int x=read(),y=read();
		bit[x].set(y,1); bit[y].set(x,1);
		int xx = find(x),  yy=find(y);
		if(xx!=yy)
			--ans, fa[xx] = yy;
	}
	int q = read();
	char c[10] ;
	while(q--)
	{
		scanf("%s",c);
		if(c[0]=='Q') printf("%d\n",ans);
		else 
		{
			int x = read(),y=read();
			if(c[0]=='A')
			{
				if((bit[x]&bit[y]).none()) --ans;
				bit[x].set(y,1);bit[y].set(x,1);
			}
			else
			{
				bit[x].set(y,0);bit[y].set(x,0);
				if((bit[x]&bit[y]).none()) ++ans;
			}
		}
	}
	return 0;
}//dfadsfasdfasdfasdfadsfasd