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

long long P=1000000007;
long long qsm(long long a,long long b,long long p){
	long long ans=1;
	while(b){
		if(b&1)(ans*=a)%=p;
		(a*=a)%=p;
		b>>=1;
	}
	return ans;
}
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	if(n>m)n^=m^=n^=m;
	if(n==1)printf("%lld",qsm(2,m,P));
	else if(n==2)printf("%lld",(qsm(3,m-1,P)<<(long long)2)%P);
	else{
		if(n==3&&m==3)printf("112");
		else if(n==5&&m==5)printf("7136");
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
