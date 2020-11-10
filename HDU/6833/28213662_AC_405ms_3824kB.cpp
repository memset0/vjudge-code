#include <cstdio>

const int P=1000000007;
inline int mul(const int &a,const int &b){return 1ll*a*b%P;}
inline int add(int a,const int &b){a+=b;return(a>=P)?a-P:a;}
inline int sub(int a,const int &b){a-=b;return (a<0)?a+P:a;}
int qsm(int a,long long b){
    int ans=1;
    while(b){
        if(b&1ll)ans=mul(ans,a);
        a=mul(a,a);
        b>>=1;
    }
    return ans;
}
int t,k,x,prime[200010],top,mu[200010],f[200010],g[200010];
bool pri[200010];
int main(){
    scanf("%d%d%d",&t,&k,&x);
    mu[1]=1;
    for(int i=2;i<=200000;i++){
        if(!pri[i])prime[++top]=i,mu[i]=P-1;
        for(int j=1;j<=top&&1ll*i*prime[j]<=200000;j++){
            pri[i*prime[j]]=1;
            if(i%prime[j]==0)break;
//            printf("%d %d %d %d\n",i,prime[j],i*prime[j],mu[i]);
            mu[i*prime[j]]=sub(0,mu[i]);
        }
    }
//    for(int i=1;i<=20;i++)printf("%d ",(mu[i]!=0)?i:0);putchar('\n');
    for(int i=1;i<=200000;i++)
        if(mu[i])
            for(int j=i;j<=200000;j+=i)
                f[j]=add(f[j],mul(i,mu[j/i]));
//    for(int i=1;i<=20;i++)printf("%d ",g[i]);putchar('\n');
    for(int i=1;i<=200000;i++)f[i]=mul(f[i],qsm(i,1ll*x*k));
    for(int i=1;i<=200000;i++)f[i]=add(f[i],f[i-1]);
    for(int i=1;i<=200000;i++)g[i]=add(g[i-1],qsm(i,k));
    for(int i=1;i<=200000;i++)g[i]=qsm(g[i],x);
    for(int i=1;i<=t;i++){
        int n;
        scanf("%d",&n);
        int ans=0;
        for(int l=1,r;l<=n;l=r+1){
            r=n/(n/l);
            ans=add(ans,mul(sub(f[r],f[l-1]),g[n/l]));
        }
        printf("%d\n",ans);
    }
}