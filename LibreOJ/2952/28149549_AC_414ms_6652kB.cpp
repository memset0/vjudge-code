// luogu-judger-enable-o2
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
#include <algorithm>

int head[100010],nxt[200010],b[200010],n,k,m,t1,t2,cnt,top,right[100010];
long long v[200010],t3,l,r,mid,ans,stack[100010];
bool vis[100010];
int find(int x){
	if(right[x]==x||!right[x])return right[x];
	return right[x]=find(right[x]);
}
void push(int s,int t,long long val){
	nxt[++k]=head[s];
	head[s]=k;
	b[k]=t;
	v[k]=val;
}
long long dfs(int x,int f){
	int start=top;
	for(int i=head[x];i;i=nxt[i])
		if(b[i]!=f){
			long long tem=dfs(b[i],x);
//			printf("%d %d %lld %lld %d\n",x,b[i],v[i],tem,cnt);
			if(v[i]+tem>=mid){
				++cnt;
				continue;
			}
			else stack[++top]=v[i]+tem;
		}
	if(top==start)return 0;
	//printf("%d %d %d\n",x,start,top);
	std::sort(stack+start+1,stack+top+1);
	//printf("(%d) ",x);
	for(int i=start+1;i<=top;++i)right[i]=i,vis[i]=0;
	for(int i=start+1,g,tem;i<top;++i)
		if(!vis[i]){
			if(stack[top]+stack[i]<mid)continue;
			tem=std::lower_bound(stack+i+1,stack+top+1,mid-stack[i])-stack,g=find(tem);
			if(!g)continue;
			vis[g]=1;
			if(g==top)right[g]=0;
			else right[g]=right[g+1];
			++cnt;
			vis[i]=1;
		}
	long long ret=0;
	for(int i=top;i>start;--i)
		if(!vis[i]){
			ret=stack[i];
			break;
		}
	top=start;
	return ret;
}
int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x;
}
int main(){
	freopen("track.in","r",stdin);
	freopen("track.out","w",stdout);
	n=read();
	m=read();
	for(int i=1;i<n;++i){
		t1=read();
		t2=read();
		t3=(long long)read();
		push(t1,t2,t3);
		push(t2,t1,t3);
		r+=t3;
	}
	while(l<=r){
		mid=(l+r)>>1;
//		printf("-----------------------%d\n",mid);
		cnt=0;
		dfs(1,0);
		if(cnt>=m)ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%lld",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
