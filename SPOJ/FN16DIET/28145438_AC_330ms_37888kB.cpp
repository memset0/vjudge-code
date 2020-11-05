#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int m,K,suma;
int a[maxn],b[maxn],buc[maxn];
vector<int> vec[maxn<<1];

inline int read(){
	int x=0;bool fopt=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar())if(ch=='-')fopt=0;
	for(;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+ch-48;
	return fopt?x:-x;
}

int main(){
	while(scanf("%d%d",&m,&K)!=EOF){
		memset(vec,0,sizeof(vec));suma=0;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(buc,0,sizeof(buc));
		for(int i=1;i<=m;i++){
			//a[i]=read();
			scanf("%d",&a[i]);
			suma+=a[i];
		}
		for(int i=1;i<=K;i++)
			//b[i]=read();
			scanf("%d",&b[i]);
		if(K%suma==0){
			puts("forever");continue;
		}
		for(int i=1;i<=K;i++)
			buc[b[i]]++;
		int maxf=max(suma+K-1,suma)/suma,maxt=maxf*suma;
		for(int i=1;i<=m;i++){
			for(int j=buc[i]+1;j<=a[i]*maxf;j++){
				int l=1LL*(j-1)*suma/a[i]+1,r=(1LL*j*suma-1)/a[i];
			    vec[l].push_back(r); 
			}
		}
		priority_queue<int,vector<int>,greater<int> > q;
		for(int i=1;i<=K;i++)
			for(int j=0;j<vec[i].size();j++)
				q.push(vec[i][j]);
		for(int i=K+1;i<=maxt;i++){
			for(int j=0;j<vec[i].size();j++)
				q.push(vec[i][j]);
			if(!q.empty())q.pop();
			if(!q.empty()&&q.top()<i){
				printf("%d\n",i-K-1);
				goto end;
			}
		}
		puts("forever");
		end:;
	}
	return 0;
}