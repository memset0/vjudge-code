#include<bits/stdc++.h>
template<class T> inline void read(T &x){
    x=0;register char c=getchar();register bool f=0;
    while(!isdigit(c))f^=c=='-',c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
const int N=2e5+10;
int n,m,a[N],b[N];
long long l,r,mid,res;
inline int real(int x){return (x-1)%n+1;}
inline bool check(int mid){
    int lst=0,sum=0,k=-1;
    for(int i=1;i<=n;i++)b[i]=a[i]<=(mid>>1),sum+=b[i];
    if(sum==0)return false;
    for(int i=1;i<=n;i++)if(b[i]){k=i;break;}
    for(int i=k;i<n+k;i++)if(b[real(i)])lst=real(i);
    else if(b[real(i+1)]==true){
        bool fl=false;
        for(int j=lst+1;j<=i;j++)if(a[real(lst)]+a[real(j)]<=mid&&a[real(j)]+a[real(i+1)]<=mid){fl=true;break;}
        sum+=fl;
    }
    // printf("check %d %d %d\n",mid,sum,k);
	// for(int i=1;i<=n;i++)printf("%d%c",b[i]," \n"[i==n]);
    return sum>=m;
}
int main(){
#ifdef memset0
    freopen("1.in","r",stdin);
#endif
    read(n),read(m);
    for(int i=1;i<=n;i++)read(a[i]);
    for(l=0,r=2000000000;l<=r;)check(mid=l+r>>1)?(res=mid,r=mid-1):(l=mid+1);
    printf("%lld\n",res);
}

/*
5 3
17 18 17 30 35
*/