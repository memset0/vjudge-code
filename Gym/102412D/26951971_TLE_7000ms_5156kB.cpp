#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=1.2e5+10;
int n,m,a[N];
void shift(int *a,int l,int r,int x){
	static int tmp[N];
	for(int i=l;i<=r;i++)tmp[i]=a[i];
	for(int i=l;i<=r-x;i++)a[i+x]=tmp[i];
	for(int i=r-x+1;i<=r;i++)a[i+x-(r-l+1)]=tmp[i];
}
bool check(int *a){
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			for(int k=j+1;k<=n;k++)
				if(a[i]<a[j]&&a[j]<a[k]){
					return true;
				}
	return false;
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	read(m);
	for(int l,r,x,i=1;i<=m;i++){
		read(l),read(r),read(x);
		shift(a,l,r,x);
		puts(check(a)?"YES":"NO");
	}
}