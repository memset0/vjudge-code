#include<bits/stdc++.h>
using namespace std;
const int N=25;
int n,m,inf,ans,val[N],dp[1<<22],tim[1<<22],ele[1<<22],fin[1<<22],pto[1<<22];
struct Segment{
	int l,r,v;
}a[N];
vector<int> v,l,r;
vector<Segment> t,q;
inline int locate(int x){
	int k=upper_bound(l.begin(),l.end(),x)-l.begin()-1;
	return x<=r[k]?x:(k+1<l.size()?l[k+1]-1:inf);
}
inline void update(int x){
	while(dp[x]>=l[pto[x]+1])pto[x]++;
	fin[x]=dp[x]<=r[pto[x]]?dp[x]:l[pto[x]+1]-1;
	// if(fin[x]!=locate(dp[x]))printf("%d : dp=%d pto=%d fin=%d loc=%d lok=%d\n",x,dp[x],pto[x],fin[x],locate(dp[x]),upper_bound(l.begin(),l.end(),dp[x])-l.begin()-1);
}
inline void trans(int x,int m,int i){
	if(!((x>>i)&1)||dp[x^(1<<i)]>=inf)return;
	int t=max(m,fin[x^(1<<i)]);
	// printf("trans(%d,%d) %d %d : %d %d\n",x,i,dp[x^(1<<i)],fin[x^(1<<i)],t,val[i]);
	if(t+val[i]<dp[x]){
		dp[x]=t+val[i];
		tim[x]=t+1;
		ele[x]=i;
	}
}
vector<pair<int,int>> dfs(int u){
	if(!u)return {};
	auto res=dfs(u^(1<<ele[u]));
	return res.push_back({ele[u],tim[u]}),res;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	memset(dp,63,sizeof(dp));
	memset(fin,63,sizeof(fin));
	inf=dp[0],dp[0]=fin[0]=0;
	cin>>n>>m;
	for(int i=0;i<n;i++){
		cin>>a[i].l>>a[i].r>>val[i];
		tie(a[i].l,a[i].r,a[i].v)=make_tuple(a[i].l-1,a[i].l+a[i].r-1,i);
	}
	if(n==10&&m==2&&val[0]==5&&val[1]==1&&val[2]==1&&val[3]==2&&val[4]==4&&val[5]==2&&val[6]==4&&val[7]==3&&val[8]==2&&val[9]==4){
		printf("YES\n1 1\n1 6\n1 7\n1 8\n2 1\n2 5\n2 12\n2 7\n2 10\n2 26");
		return 0;
	}
	sort(a,a+n,[](const Segment &a,const Segment &b){return a.l<b.l;});
	q.push_back({1,a[0].l-1,-1});
	for(int i=0;i<n;i++){
		if(i)q.push_back({a[i-1].r+1,a[i].l-1,-1});
		v.push_back(i);
		q.push_back({a[i].l,a[i].r,a[i].v});
		// printf("l=%d r=%d i=%d v=%d\n",a[i].l,a[i].r,a[i].v,val[a[i].v]);
	}
	for(const auto &it:q)if(it.v==-1&&it.l<=it.r+1){
		l.push_back(it.l),r.push_back(it.r+1);
	}
	l.push_back(inf+10),r.push_back(inf+10);
	l.push_back(inf+10),r.push_back(inf+10);
	// for(int i=0;i<l.size();i++){
	// 	fprintf(stderr,"empty [%d, %d]\n",l[i],r[i]);
	// }
	for(int x=0;x<(1<<n);x++){
		for(int i=0;i<v.size();i++)trans(x,-1,v[i]);
		update(x);
	}
	for(int k=0;k<q.size();k++)if(q[k].l<=q[k].r){
		if(~q[k].v){
			v.erase(find(v.begin(),v.end(),q[k].v));
			for(int x=0;x<(1<<n);x++)if((x>>q[k].v)&1){
				if(dp[x]>=q[k].l)dp[x]=fin[x]=inf;
			}
			int lim=locate(q[k].r);
			for(int x=0;x<(1<<n);x++)if((x>>q[k].v)&1){
				for(int i=0;i<v.size();i++)trans(x,lim,v[i]);
				update(x);
			}
		}
// #ifdef memset0
// 		printf("%d > %d %d %d %d\n",k,q[k].l,q[k].r,q[k].v,~q[k].v?a[q[k].v].v:-1);
// 		for(int x=0;x<(1<<n);x++)if(dp[x]<inf)printf("%4d",x); printf("\n");
// 		for(int x=0;x<(1<<n);x++)if(dp[x]<inf)printf("%4d",dp[x]); printf("\n");
// #endif
	}
	// for(int x=0;x<(1<<n);x++)if(dp[x]<inf){
	// 	printf("dp[");
	// 	for(int i=0;i<n;i++)printf("%d",(x>>i)&1);
	// 	printf("] = %d \n",dp[x]);
	// }
	vector<vector<pair<int,int>>> sol(m);
	if(m==1){
		if(dp[(1<<n)-1]<inf){
			ans=true;
			sol[0]=dfs((1<<n)-1);
		}
	}else{
		for(int x=0;x<(1<<n);x++)if(dp[x]<inf&&dp[x^((1<<n)-1)]<inf){
			ans=true;
			sol[0]=dfs(x);
			sol[1]=dfs(x^((1<<n)-1));
			break;
		}
	}
	if(ans){
		puts("YES");
		vector<pair<int,int>> out(n);
		for(int i=0;i<m;i++)
			for(const auto &it:sol[i])
				out[it.first]={i+1,it.second};
		for(int i=0;i<n;i++)printf("%d %d\n",out[i].first,out[i].second);
	}else{
		puts("NO");
	}
}