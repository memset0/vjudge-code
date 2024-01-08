#include<bits/stdc++.h>
using namespace std;
int T,n,k,tmp,nw,sw,sa[15],cnt[10],ti,mm;
int a[15];
char s[15];
int td(int*x){
	int ret=0;
	for(int i=1;i<=n;++i)ret=ret*10+x[i];
	return ret;
}
int Getmin(int x,int num){
    if(num==k||x>=n)return td(a);
    int mm=9;
    for(int i=x;i<=n;++i)if(x>1||a[i])mm=min(mm,a[i]);
    if(mm==a[x])return Getmin(x+1,num);
    int ret=1e9;
    for(int i=x+1;i<=n;++i)if(a[i]==mm){
        swap(a[x],a[i]),ret=min(ret,Getmin(x+1,num+1)),swap(a[x],a[i]);
    }
    return ret;
}
int Getmax(int x,int num){
    if(num==k||x>=n)return td(a);
    int mm=0;
    for(int i=x;i<=n;++i)mm=max(mm,a[i]);
    if(mm==a[x])return Getmax(x+1,num);
    int ret=0;
    for(int i=x+1;i<=n;++i)if(a[i]==mm){
        swap(a[x],a[i]),ret=max(ret,Getmax(x+1,num+1)),swap(a[x],a[i]);
    }
    return ret;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%s%d",s+1,&k),n=strlen(s+1);
        for(int i=1;i<=n;++i)a[i]=s[i]-'0';
        printf("%d %d\n",Getmin(1,0),Getmax(1,0));
	}
	return 0;
}