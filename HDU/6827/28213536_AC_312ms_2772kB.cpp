#include <cstdio>

const int P=1000000007;
int qsm(int a,int b){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%P;
        a=1ll*a*a%P;
        b>>=1;
    }
    return ans;
}
int T,n,s[200001],H[200001];
int main(){
    scanf("%d",&T);
    H[0]=H[1]=1;
    for(int i=2;i<=200000;i++)H[i]=1ll*(P-P/i)*H[P%i]%P;
//    for(int i=1;i<=10;i++)printf("%d ",H[i]);putchar('\n');
    H[0]=0;
    for(int i=1;i<=200000;i++)H[i]=(H[i]+H[i-1])%P; 
    for(int fd=1;fd<=T;fd++){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%d",s+i);
        for(int i=1;i<=n;i++)s[i]=(s[i]+s[i-1])%P;
        int cnt=0;
        for(int i=1;i<=n;i++)cnt=(cnt+1ll*s[i]*H[i]%P)%P;
        for(int i=1;i<=n;i++)cnt=(cnt+P-(1ll*s[i]*H[n-i]%P))%P;
        printf("%d\n",1ll*cnt*qsm(((1ll*n*(n+1))>>1)%P,P-2)%P);
    }
}