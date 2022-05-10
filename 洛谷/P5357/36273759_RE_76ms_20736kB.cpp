#include<bits/stdc++.h>
const int N=2e5+10;
char s[N];
std::queue<int> q;
std::vector<int> son[N];
int n,tot=1,pos[N],ch[N][26],sum[N],fail[N];
int insert(char *s,int l){
	int u=1;
	for(int i=1;i<=l;i++){
		if(!ch[u][s[i]-'a'])ch[u][s[i]-'a']=++tot;
		// printf("%c %d -> %d\n",s[i],u,ch[u][s[i]-'a']);
		u=ch[u][s[i]-'a'];
	}
	return u;
}
void buildfail(){
	q.push(1);
	while(q.size()){
		int u=q.front();q.pop();
		for(int i=0;i<26;i++)if(ch[u][i]){
			if(u==1)fail[ch[u][i]]=1;
			else{
				for(int t=fail[u];t;t=fail[t])if(ch[t][i]){fail[ch[u][i]]=ch[t][i];break;}
				if(!fail[ch[u][i]])fail[ch[u][i]]=1;
			}
			q.push(ch[u][i]);
		}
	}
}
void locate(char *s,int l){
	for(int i=1,u=1,c;c=s[i]-'a',i<=l;i++){
		while(!ch[u][c]&&u!=1)u=fail[u];
		if(ch[u][c])u=ch[u][c];++sum[u];
		// printf("locate %c %d\n",s[i],u);
	}
}
void dfs(int u){
	for(int v:son[u])dfs(v),sum[u]+=sum[v];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%s",s+1),pos[i]=insert(s,strlen(s+1));
	buildfail();
	for(int i=2;i<=tot;i++)son[fail[i]].push_back(i);
	scanf("%s",s+1),locate(s,strlen(s+1)),dfs(1);
	for(int i=1;i<=n;i++)printf("%d\n",sum[pos[i]]);
	// for(int i=1;i<=tot;i++)printf("%d : fail%d sum%d\n",i,fail[i],sum[i]);
}