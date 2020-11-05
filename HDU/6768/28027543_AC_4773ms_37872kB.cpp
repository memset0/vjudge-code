#include <cstdio>

int A,B,C,a[4000001],b[4000001],c[4000001],f[8000001],T,p[11];
int search(int P){
    f[1]=1,f[2]=2;
    for(int i=3;i<=C;i++)f[i]=(f[i-1]+f[i-2])%P;
    int _a=0,_b=0,_c=0;
    for(int i=1;i<=A;i++)if(a[i])_a=(_a+f[i])%P;
    for(int i=1;i<=B;i++)if(b[i])_b=(_b+f[i])%P;
    for(int i=1;i<=C;i++)if(c[i])_c=(_c+f[i])%P;
    _a=1ll*_a*_b%P;
    for(int i=1;i<=C;i++)
        if(!c[i]&&(_c+f[i])%P==_a)return i;
    return -1;
}
int main(){
    scanf("%d",&T);
    for(int fd=1;fd<=T;fd++){
        scanf("%d",&A);
        for(int i=1;i<=A;i++)scanf("%d",a+i);
        scanf("%d",&B);
        for(int i=1;i<=B;i++)scanf("%d",b+i);
        scanf("%d",&C);
        for(int i=1;i<=(A+B)<<1;i++)c[i]=0;
        for(int i=1;i<=C;i++)scanf("%d",c+i);
        C=(A+B)<<1;
        p[0]=search(998244353);
        p[1]=search(1000000007);
        p[2]=search(1000000009);
        p[3]=search(1004535809);
        int ans=0;
        for(int i=0;i<4;i++){
            int cnt=0;
            for(int j=0;j<4;j++)
                if(p[i]==p[j])++cnt;
            if(cnt>2)ans=p[i];
        }
        printf("%d\n",ans);
    }
}