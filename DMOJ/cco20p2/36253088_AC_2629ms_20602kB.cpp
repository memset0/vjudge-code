#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=2e5+10;
int n,a[N],p[N],s[N];
long long ans;
std::set<int> set;
std::vector<int> vec[N];
void failed(){puts("-1"),exit(0);}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n);
	for(int i=1;i<=n;i++)read(a[i]),vec[a[i]].push_back(i);
	for(int i=n;i>=1;i--){
		for(int x:vec[i])set.insert(x);
		if(!set.size())failed();
		auto it=--set.end();
		p[i]=*it,set.erase(it);
		for(int k=p[i];k;k-=k&-k)ans+=s[k];
		for(int k=p[i];k<=n;k+=k&-k)s[k]++;
	}
	printf("%lld\n",ans);
}