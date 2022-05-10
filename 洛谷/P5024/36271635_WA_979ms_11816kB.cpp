/*
Sooke bless me.
LJC00118 bless me.
Dilute bless me.
memset0 bless me.
memset1 bless me.
Daniel14311531 bless me.
T_AK bless me.
*/
#include <cstdio>

int n,m,head[100010],nxt[200010],b[200010],k,t1,t2,t3,t4,fa[100010];
long long p[100010],f[100010][2],maxn,top[100010][2];
void push(int s,int t){
	nxt[++k]=head[s];
	head[s]=k;
	b[k]=t;
}
char opt1,opt2;
long long min(long long a,long long b){
	return a<b?a:b;
}
void dfs(int x,int F){
	fa[x]=F;
	f[x][0]=f[x][1]=0;
	for(int i=head[x];i;i=nxt[i])
		if(b[i]!=F){
			dfs(b[i],x);
			f[x][0]+=f[b[i]][1];
			f[x][1]+=min(f[b[i]][1],f[b[i]][0]);
		}
	f[x][1]+=p[x];
	if(x==t1){
		if(t2)f[x][0]=maxn;
		else f[x][1]=maxn;
	}
	else if(x==t3){
		if(t4)f[x][0]=maxn;
		else f[x][1]=maxn;
	}
}
void getans(int x,int F,bool tuio){
	if(x==1&&tuio)f[x][0]=maxn;
	top[x][0]=top[F][1]+f[x][0];
	top[x][1]=min(top[F][1],top[F][0])+f[x][1];
	for(int i=head[x];i;i=nxt[i])
		if(b[i]!=F){
			top[x][0]-=f[b[i]][1];
			top[x][1]-=min(f[b[i]][0],f[b[i]][1]);
			getans(b[i],x,tuio);
			top[x][0]+=f[b[i]][1];
			top[x][1]+=min(f[b[i]][0],f[b[i]][1]);
		}
}
int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x;
}
char get(){
	char ch=getchar();
	while((ch<'0'||ch>'9')&&(ch<'A'||ch>'C'))ch=getchar();
	return ch;
}
int main(){
	n=read(),m=read();
	opt1=get();opt2=get();
	for(int i=1;i<=n;i++)p[i]=(long long)read(),maxn+=p[i];
	for(int i=1;i<n;i++)t1=read(),t2=read(),push(t1,t2),push(t2,t1);
	t1=t2=t3=t4=0;
	dfs(1,0);
	if(opt2=='1')getans(1,0,1);
	else if(opt2=='2')getans(1,0,0);
	for(int i=1;i<=m;i++){
		t1=read(),t2=read(),t3=read(),t4=read();
		if((fa[t1]==t3||fa[t3]==t1)&&!t2&&!t4)puts("-1");
		else if(n<=2000&&m<=2000){
			dfs(1,0);
			printf("%lld\n",min(f[1][0],f[1][1]));
		}
		else if(opt2=='1'){
			printf("%lld\n",top[t3][t4]);
		}
		else if(opt2=='2'){
			if(fa[t3]==t1)t1^=t3^=t1^=t3,t2^=t4^=t2^=t4;
			if(t4){
				int tem=t2?f[t1][1]:f[t1][0];
				printf("%lld\n",top[t3][t4]-min(f[t1][0],f[t1][1])+tem);
			}
			else printf("%lld\n",top[t3][t4]);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
