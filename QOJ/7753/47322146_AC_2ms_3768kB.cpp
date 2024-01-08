#include<bits/stdc++.h>
#define all(x) begin(x),end(x)
using namespace std;
const int N=10;
const double eps=1e-9;
int n,m,w[N+5][N+5],vis[N+5],TIM,v2[N+5],tim;
int sz,l,p[N+5],pos[N+5];
double a[N+5][N+5],sl[N+5];
double ans=0,tmp;
void dfs(int x){
	vis[x]=TIM,p[++sz]=x,pos[x]=sz;
	for(int i=1;i<=n;++i)if(w[x][i]&&((m>>i-1)&1)&&vis[i]!=TIM)dfs(i);
}
void Ins(int x,int y){
	//cerr<<"INS "<<x<<" "<<y<<"\n";
	++l;
	for(int i=1;i<=sz+1;++i)a[l][i]=0;
	a[l][pos[x]]=w[x][y],a[l][pos[y]]=-w[x][y];
	for(int i=1;i<=n;++i)if(i!=x&&i!=y&&pos[i])a[l][pos[i]]=w[y][i]-w[x][i];
	a[l][sz+1]=0;
}
void Gete(int x){
	//cerr<<"GETE "<<x<<"\n";
	v2[x]=tim;
	for(int i=1;i<=n;++i)if(w[x][i]&&((m>>i-1)&1)&&v2[i]!=tim)Gete(i),Ins(x,i);
}
void Solve(){
	assert(l==sz);
	double mx;
	int mi;
	/*for(int i=1;i<=l;++i){
		for(int j=1;j<=sz+1;++j)cerr<<a[i][j]<<" |\n"[(j>=sz)+(j==sz+1)];
	}*/
	for(int i=1;i<=l;++i){
		mx=abs(a[i][i]),mi=i;
		for(int j=i+1;j<=l;++j)if(abs(a[j][i])>mx)mx=abs(a[j][i]),mi=j;
		//assert(mx>eps);
		if(i!=mi)for(int j=i;j<=sz+1;++j)swap(a[i][j],a[mi][j]);
		for(int j=1;j<=l;++j)if(j!=i){
			double T=-a[j][i]/a[i][i];
			for(int k=i;k<=sz+1;++k)a[j][k]+=T*a[i][k];
		}
	}
	for(int i=1;i<=sz;++i)sl[i]=a[i][sz+1]/a[i][i];
	//for(int i=1;i<=sz;++i)cout<<"SL "<<i<<"="<<sl[i]<<"\n";
}
int main(){
#ifdef memset0
	//freopen(".in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)cin>>w[i][j];
	for(m=1;m<(1<<n);++m)
	//if(m=(1<<6)-1)
	{
		//cerr<<"m="<<m<<"\n";
		++TIM;
		for(int i=1;i<=n;++i)if(((m>>i-1)&1)&&vis[i]!=TIM){
			//cerr<<"I="<<i<<"\n";
			sz=0;
			for(int j=1;j<=n;++j)pos[j]=0;
			dfs(i);
			//cerr<<"SZ="<<sz<<"\n";
			++tim;
			l=1;
			for(int j=1;j<=sz;++j)a[l][j]=1;
			a[l][sz+1]=1;
			Gete(i);
			Solve();
			for(int j=1;j<=sz;++j)if(sl[j]<-eps)goto Skip;
			tmp=0;
			for(int j=1;j<=sz;++j)for(int k=j+1;k<=sz;++k)tmp+=w[p[j]][p[k]]*sl[j]*sl[k];
			/*if(tmp>ans){
				for(int j=1;j<=sz;++j)cout<<"x_"<<p[j]<<"="<<sl[j]<<"\n";
			}*/
			ans=max(ans,tmp);
		}
		Skip:;
	}
	cout<<fixed<<setprecision(12)<<ans;
}
/*
3
0 2 2
2 0 2
2 2 0

5
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0

6
0 1 1 0 0 0
1 0 1 0 0 0
1 1 0 0 0 0
0 0 0 0 1 2
0 0 0 1 0 1
0 0 0 2 1 0

4
0 1 2 2
1 0 1 3
2 1 0 3
2 3 3 0

6
0 1 1 1 1 1
1 0 1 1 1 1
1 1 0 1 1 1
1 1 1 0 1 1
1 1 1 1 0 1
1 1 1 1 1 0
*/