
#include<bits/stdc++.h>
using namespace std;
const int N=25;
char c[3][9]={"center","left","right"},s[9];
int n,vcnt=1,low[N],le[N],st[N],w;
inline int go(int x,int y,int z){
	printf("%d %s %d\n",x,c[y],z);fflush(stdout);
	scanf("%s",s);if(*s=='t')exit(0);return *s=='c'?0:*s=='l'?1:2;
}
void dfs(int x){
	st[low[x]=++w]=x;
	for(int i=0;i<n;++i){
		int t=go(1,1,1);
		if(t==0){
			t=++vcnt;dfs(t);if(low[t]<low[x])low[x]=low[t],le[x]=i;
		}else{
			if(t==1){
				int c=0;
				t=go(0,2,0);
				for(;t!=2;++c,t=go(0,1,0));
				if(w-c<low[x])low[x]=w-c,le[x]=i;
				for(;c--;t=go(0,1,0));
			}else{
				int c=0,z=0;
				for(;++c,t=go(0,2,0),t!=1;);
				for(;++z,t=go(0,1,0),t!=2;);--z;
				if(w-z<low[x])low[x]=w-z,le[x]=i;
				for(;c--;t=go(0,2,0));for(;z--;t=go(0,1,0));
			}
		}
	}
	assert(w>1);
	int t=(le[x]+1)%n;for(t=go(t,2,t);t!=1;t=go(0,2,0));for(t=w-low[x]-1;t--;go(0,1,0));
	--w;
}
int main(){
	scanf("%d%s",&n,s);
	dfs(1);
}