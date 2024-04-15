// 缺spj

#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
#define N 2000005
#define mod 1000000007
#define eps 1e-6
#define ll long long
#define rint register int
#define db double
using namespace std;
inline int read (){
	register int num,sign=1;register char c;
	while (((c=getchar())<'0'||c>'9')&&c!='-');c=='-'?num=sign=0:num=c-48;
	while ((c=getchar())>='0'&&c<='9')num=(num<<3)+(num<<1)+(c-48);
	return sign?num:-num;
}
int n,ok,len;
double  A[N],ans;
inline void fwt(db *A,rint s){
	for(rint i=1;i<len;i<<=1)
		for(rint j=0;j<len;j+=i<<1)
			for(rint k=0;k<i;++k)
				A[i+j+k]=s*A[j+k]+A[i+j+k];
}
int main(){
	n=read();len=1<<n;
	for(rint i=0;i<len;++i)scanf("%lf",A+i),ok|=A[i]>eps?i:0;fwt(A,1);
	if(ok!=(len-1)){puts("INF");return 0;}
	for(rint i=0;i<len-1;++i){
		rint res=0,tmp=i;
		while(tmp)++res,tmp-=tmp&-tmp;
		(n-res)&1?ans+=1/(1-A[i]):ans-=1/(1-A[i]);
	}
	printf("%.10lf\n",ans);

}
