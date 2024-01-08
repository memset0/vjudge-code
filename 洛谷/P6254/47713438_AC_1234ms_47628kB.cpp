#include<bits/stdc++.h>
int read(){
	int x=0; char c=getchar(); bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); return f?-x:x;
}
char readc(){
	char c=getchar();
	while(c!='s'&&c!='e')c=getchar(); return c;
}
const int N=1e6+10;
int n,m,ans,s[N],b[N];
std::vector<std::pair<int,int>> vet[N];
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	n=read();
	for(int c,v,i=1;i<=n;i++){
		c=readc(),v=read(),m=std::max(m,v);
		vet[v].push_back(std::make_pair(c=='s'?1:-1,i));
	}
	for(int min,c=1;c<=m;c++)if(vet[c].size()){
		// printf("=== %d ===\n",c);
		const auto &v=vet[c];
		s[0]=v[0].first;
		for(int i=1;i<v.size();i++)s[i]=s[i-1]+v[i].first;
		min=0;
		for(int i=1;i<v.size();i++)if(s[i]<s[min])min=i;
		// for(int i=0;i<v.size();i++){
		// 	printf("%d %d %d\n",v[i].first,v[i].second,s[i]);
		// }
		if(s[v.size()-1])continue;
		for(int i=0;i<v.size()-1;i++)
			if(s[i]==s[min]){
				b[v[i].second+1]++;
				b[v[i+1].second+1]--;
				// printf("++ %d | -- %d\n",v[i].second+1,v[i+1].second+1);
			}
		if(s[v.size()-1]==s[min]){
			b[1]++,b[v[0].second+1]--; 
			b[v[v.size()-1].second+1]++;
		}
	}
	ans=1,s[0]=0;
	for(int i=1;i<=n;i++){
		s[i]=s[i-1]+b[i];
		if(s[i]>s[ans])ans=i;
	}
	printf("%d %d\n",ans,s[ans]);
	// for(int i=1;i<=n;i++)printf("%d%c",s[i]," \n"[i==n]);
	// for(int i=1;i<=n;i++)printf("%d%c",b[i]," \n"[i==n]);
}