#include<bits/stdc++.h>
const int N=1e6+10;
int n;
char s[N];
struct SA{
	static const int N=::N<<1;
	int len,siz,sa[N],rnk[N],tmp[N],tax[N]; //sa排名为i的后缀 rnk后缀i的排名
	inline bool cmp(int i,int j,int k){return tmp[i]==tmp[j]&&tmp[i+k]==tmp[j+k];}
	void sort(){ //根据rnk分配新sa
		for(int i=1;i<=siz;i++)tax[i]=0;
		for(int i=1;i<=len;i++)tax[rnk[i]]++;
		for(int i=1;i<=siz;i++)tax[i]+=tax[i-1];
		for(int i=len;i>=1;i--)sa[tax[rnk[tmp[i]]]--]=tmp[i];
	}
	void build(int n,int m,char *s){
		len=n,siz=m;
		for(int i=1;i<=len;i++)rnk[i]=s[i],tmp[i]=i;
		sort();
		for(int now=1,cnt=0;cnt<len;now<<=1,siz=cnt){ //倍增now
			cnt=0;
			for(int i=len;i>=len-now+1;i--)tmp[++cnt]=i;
			for(int i=1;i<=len;i++)if(sa[i]>now)tmp[++cnt]=sa[i]-now;
			sort(),std::swap(rnk,tmp),rnk[sa[1]]=cnt=1; //根据sa分配新rnk
			for(int i=2;i<=len;i++)rnk[sa[i]]=cmp(sa[i],sa[i-1],now)?cnt:++cnt;
		}
	}
}sa;
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	scanf("%s",s+1),n=strlen(s+1);
	sa.build(n,300,s);
	for(int i=1;i<=n;i++)printf("%d%c",sa.sa[i]," \n"[i==n]);
}