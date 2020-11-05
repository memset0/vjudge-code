#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=1e5+10;
int T,n,rt,ans,p[N],ch[N][2],min[N],siz[N];
bool tag[N];
void dfs(int u){
	min[u]=u,siz[u]=1;
	for(int i=0;i<2;i++)if(ch[u][i]){
		dfs(ch[u][i]);
		siz[u]+=siz[ch[u][i]];
		min[u]=std::min(min[u],min[ch[u][i]]);
	}
}
void solve(int u,int l,int r){
	if(ch[u][0]&&ch[u][1]){
		if(u<min[ch[u][0]]&&u<min[ch[u][1]]){
			if((siz[ch[u][0]]>siz[ch[u][1]])||(siz[ch[u][0]]==siz[ch[u][1]]&&min[ch[u][0]]>min[ch[u][1]]))std::swap(ch[u][0],ch[u][1]);
		}else{
			if(min[ch[u][0]]>min[ch[u][1]])std::swap(ch[u][0],ch[u][1]);
		}
	}else if(ch[u][0]){
		if(u<min[ch[u][0]])std::swap(ch[u][0],ch[u][1]);
	}else if(ch[u][1]){
		if(min[ch[u][1]]<u)std::swap(ch[u][0],ch[u][1]);
	}
	p[u]=l+siz[ch[u][0]];
	if(ch[u][0])solve(ch[u][0],l,l+siz[ch[u][0]]-1);
	if(ch[u][1])solve(ch[u][1],r-siz[ch[u][1]]+1,r);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(read(T);T--;ans=0){
		read(n),memset(tag+1,0,n);
		for(int i=1;i<=n;i++)for(int j=0;j<2;j++)read(ch[i][j]),tag[ch[i][j]]=1;
		for(int i=1;i<=n;i++)if(!tag[i])rt=i;
		dfs(rt);
		for(int i=1;i<=n;i++)p[i]=-1;
		solve(rt,1,n);
		// for(int i=1;i<=n;i++)printf("%d%c",p[i]," \n"[i==n]);
		for(int i=1,w=1;i<=n;i++){
			w=(long long)w*233%1000000007;
			ans=(ans+(long long)(p[i]^i)*w)%1000000007;
		}
		printf("%d\n",ans);
	}
}