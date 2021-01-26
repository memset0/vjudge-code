#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL maxn=1e5+5;
LL dp[maxn*10];
LL prime[maxn],s=0;
bool vis[maxn];
void init_prime(){
    for(LL i=2;i<maxn;i++){
        if(!vis[i]){
            prime[s++]=i;
        }
        for(LL j=0;j<s&&i*prime[j]<maxn;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0){
                break;
            }
        }
    }
    return ;
}
LL pow_mod(LL a1,LL b1){
    LL ans=1;
    while(b1){
        if(b1&1){
            ans=ans*a1;
        }
        b1>>=1;
        a1*=a1;
    }
    return ans;
}
LL pow_mod2(LL a,LL b,LL p){
    LL ans=1;
    while(b){
        if(b&1){
            ans=ans*a%p;
        }
        b>>=1;
        a=a*a%p;
    }
    return ans;
}
LL gcd(LL a,LL b){
    return b?gcd(b,a%b):a;
}
bool f(LL n,LL p){
    if(pow_mod2(n,(p-1)>>1,p)!=1){
        return false;
    }
    return true;
}
struct matrix{
    LL x1,x2,x3,x4;
};
matrix matrix_a,matrix_b;
matrix M2(matrix aa,matrix bb,LL mod){
    matrix tmp;
    tmp.x1=(aa.x1*bb.x1%mod+aa.x2*bb.x3%mod)%mod;
    tmp.x2=(aa.x1*bb.x2%mod+aa.x2*bb.x4%mod)%mod;
    tmp.x3=(aa.x3*bb.x1%mod+aa.x4*bb.x3%mod)%mod;
    tmp.x4=(aa.x3*bb.x2%mod+aa.x4*bb.x4%mod)%mod;
    return tmp;
}
matrix M(LL n,LL mod){
    matrix a,b;
    a=matrix_a;b=matrix_b;
    while(n){
        if(n&1){
            b=M2(b,a,mod);
        }
        n>>=1;
        a=M2(a,a,mod);
    }
    return b;
}
/*bool g(matrix t){
    return t.m[0][0]==1&&t.m[0][1]==0&&t.m[1][0]==0&&t.m[1][1]==1;
}*/
LL fac[100][2],l,x,fs[1000];
void dfs(LL count,LL step){
    if(step==l){
        fs[x++]=count;
        return ;
    }
    LL sum=1;
    for(LL i=0;i<fac[step][1];i++){
        sum*=fac[step][0];
        dfs(count*sum,step+1);
    }
    dfs(count,step+1);
}
LL solve2(LL p){
    if(p<1e6&&dp[p]){
        return dp[p];
    }
    bool ok=f(5,p);//判断5是否为p的二次剩余 
    LL t;
    if(ok){
        t=p-1;
    }
    else{
        t=2*p+2;
    }
    l=0;
    for(LL i=0;i<s;i++){
        if(prime[i]>t/prime[i]){
            break;
        }
        if(t%prime[i]==0){
            LL count=0;
            fac[l][0]=prime[i];
            while(t%prime[i]==0){
                count++;t/=prime[i];
            }
            fac[l++][1]=count;
        }
    }
    if(t>1){
        fac[l][0]=t;
        fac[l++][1]=1;
    }
    x=0;
    dfs(1,0);//求t的因子 
    sort(fs,fs+x);
    for(LL i=0;i<x;i++){
        matrix m1=M(fs[i],p);
        if(m1.x1==m1.x4&&m1.x1==1&&m1.x2==m1.x3&&m1.x2==0){
            if(p<1e6){
                dp[p]=fs[i]; 
            }
            return fs[i];
        } 
    }
}
LL solve(LL n){
    LL ans=1,cnt;
    for(LL i=0;i<s;i++){
        if(prime[i]>n/prime[i]){
            break;
        }
        if(n%prime[i]==0){
            LL count=0;
            while(n%prime[i]==0){
                count++;n/=prime[i];
            }
            cnt=pow_mod(prime[i],count-1);
            cnt*=solve2(prime[i]);
            ans=(ans/gcd(ans,cnt))*cnt;
        }
    }
    if(n>1){
        cnt=1;
        cnt*=solve2(n);
        ans=ans/gcd(ans,cnt)*cnt;
    }
    return ans;
}
int main(){
    LL t,n;
    init_prime();
    matrix_a.x1=matrix_a.x2=matrix_a.x3=1;  
    matrix_a.x4=0;
    matrix_b.x1=matrix_b.x4=1;  
    matrix_b.x2=matrix_b.x3=0;
    dp[2]=3;dp[3]=8;dp[5]=20;
    scanf("%I64d",&t);
    while(t--){
        scanf("%I64d",&n);
        printf("%I64d\n",solve(n));
    }
    return 0;
}