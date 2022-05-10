#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
}

const int N=5e4+10,M=250;
int n,m,sqn,a[N],ans[N];
std::vector<std::pair<int,int>> q[N];

struct young{
	int fl,a[M][N];
	inline void out(){
		for(int i=1;a[i][0];i++)
			for(int j=1;j<=a[i][0];j++)
				printf("%d%c",a[i][j]," \n"[j==a[i][0]]);
	}
	inline void insert(int x,int k=1e9,int u=1){
		k=(fl?std::lower_bound<int*,int>:std::upper_bound<int*,int>)(a[u]+1,a[u]+std::min(a[u][0],k)+1,x)-a[u];
		if(k>a[u][0])a[u][++a[u][0]]=x,++a[0][a[u][0]];
		else{if(u<sqn)insert(a[u][k],k-1,u+1); a[u][k]=x;}
	}
}s,t;

int query(int k){
	int res=0;
	for(int i=1;i<=k;i++)res+=s.a[0][i];
	for(int i=1;i<=std::min(k,sqn);i++)res+=std::max(0,t.a[i][0]-sqn);
	return res;
}

int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);
#endif
	read(n),read(m),sqn=ceil(sqrt(n)),s.fl=1,t.fl=0;
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1,k,v;i<=m;i++){
		read(k),read(v);
		q[k].push_back(std::make_pair(v,i));
	}
	for(int i=1;i<=n;i++){
		s.insert(a[i]),t.insert(-a[i]);
		// printf(">> i=%d a[i]=%d\n",i,a[i]),s.out(),t.out(),putchar('\n');
		for(std::pair<int,int> it:q[i])ans[it.second]=query(it.first);
	}
	for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
	// s.out(),t.out();
}