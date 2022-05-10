#include<bits/stdc++.h>
const int N=3e5+10;
int lim,nod,lst,len; long long ans; char s[N];
struct node{
	int siz,len,fail,ch[26];
}e[N];
int find(int x){
	// printf("find(%d) [%d](%d) [%d](%d)\n",x,len,s[len],len-e[x].len+1,s[len-e[x].len+1]);
	while(s[len]!=s[len-e[x].len-1])x=e[x].fail;
	return x;
}
void append(int c){
	// printf("append %d\n",c);
	int u=find(lst);
	// printf("find(%d) = %d\n",lst,u);
	if(!e[u].ch[c]){
		e[u].ch[c]=++nod;
		e[nod].len=e[u].len+2;
		e[nod].fail=u==1?2:e[find(e[u].fail)].ch[c];
	}
	e[lst=e[u].ch[c]].siz++;
	// printf("%d[%d] -> %d[%d]\n",u,e[u].fail,lst,e[lst].fail);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	nod=2,e[2].fail=1,e[1].len=-1,lst=1;
	scanf("%s",s+1),lim=strlen(s+1);
	for(len=1;len<=lim;len++)append(s[len]-'a');
	for(int i=nod;i>=2;i--)e[e[i].fail].siz+=e[i].siz;
	for(int i=1;i<=nod;i++)ans=std::max(ans,(long long)e[i].siz*e[i].len);
	printf("%lld\n",ans);
}