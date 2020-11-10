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

long long a[100010];
int n,st[100010][21],Loga[100010];
int gmin(int lhs,int rhs){return a[lhs]<a[rhs]?lhs:rhs;}
int SparseTable(int l,int r){
	int k=Loga[r-l+1];
	return gmin(st[l][k],st[r-(1<<k)+1][k]);
}
long long getans(int l,int r,long long delt){
	if(l>r)return 0;
	int x=SparseTable(l,r);
	return getans(l,x-1,a[x])+getans(x+1,r,a[x])+a[x]-delt;
}
int main(){
	scanf("%d",&n);
	Loga[0]=-1;
	for(int i=1;i<=n;++i){
		scanf("%lld",a+i);
		Loga[i]=Loga[i>>1]+1;
		st[i][0]=i;
	}
	for(int j=1;j<=19;++j)
		for(int i=1;i+(1<<j)-1<=n;++i)
			st[i][j]=gmin(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	printf("%lld",getans(1,n,0));
	fclose(stdin);
	fclose(stdout);
	return 0;
}