#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c)) f^=c=='-',c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar(); if(f) x=-x;
}
template<class T> inline void print(T x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=3e5+10;
int len; long long ans; char s[N];
struct pam{
	int u,lst,len,nod,s[N];
	struct node{int len,siz,ch[26],fail;}e[N];
	pam(){nod=1,e[0].fail=1,e[1].fail=0,e[1].len=-1,e[0].len=0,s[0]=30,lst=1;}
	int find(int x){
		while(s[len-e[x].len-1]!=s[len]&&x){
			// printf("%d fail-> %d : %d %d\n",x,e[x].fail,s[len],s[len-e[x].len-1]);
			x=e[x].fail;
		}
		return x;
	}
	void append(int c){
		printf("append %d lst=%d\n",c,lst);
		s[++len]=c,u=find(lst);
		printf("find(%d) => %d\n",lst,u);
		if(!e[u].ch[c]){
			e[u].ch[c]=++nod;
			e[nod].len=e[u].len+2;
			e[nod].fail=e[find(e[u].fail)].ch[c];
		}
		e[lst=e[u].ch[c]].siz++;
		printf(">> %d[%d] -> %d[%d] : %d\n",u,e[u].fail,lst,e[lst].fail,e[lst].len);
	}
	void dfs(int u){
		for(int i=0;i<26;i++)if(e[u].ch[i])dfs(e[u].ch[i]),e[u].siz+=e[e[u].ch[i]].siz;
		ans=std::max(ans,(long long)e[u].siz*e[u].len);
	}
}p;
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%s",s),len=strlen(s);
	for(int i=0;i<len;i++)p.append(s[i]-'a');
	p.dfs(1);
	for(int i=0;i<=p.nod;i++)printf("[%d %d]%c",p.e[i].siz,p.e[i].len," \n"[i==p.nod]);
	print(ans,'\n');
}