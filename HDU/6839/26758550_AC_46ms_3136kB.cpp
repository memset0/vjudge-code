#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=1e5+10;
int T,n,ans,a[N],b[N],s[N],t[N];
char A[N],B[N];
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(read(T);T--;){
		read(n);
		scanf("%s%s",A+1,B+1);
		a[n+1]=b[n+1]=0;
		for(int i=1;i<=n;i++){
			a[i]=A[i]=='1';
			b[i]=B[i]=='1';
		}
		s[n+1]=s[n+2]=0;
		for(int i=n;i>=1;i--)s[i]=s[i+1]+(a[i]!=b[i]);
		t[0]=0;
		for(int i=1;i<=n;i++){
			t[i]=t[i-1]+(a[i]!=1)+(b[i]!=0);
		}
		ans=s[1];
		for(int i=1;i<=n;i++){
			ans=std::min(ans,t[i]+s[i+2]+(a[i+1]!=0)+(b[i+1]!=1)+1);
			// printf("%d %d %d %d\n",i,t[i],s[i+2],(a[i+1]!=0)+(b[i+1]!=1));
		}
		print(ans,'\n');
	}
}