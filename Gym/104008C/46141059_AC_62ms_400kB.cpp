#include<bits/stdc++.h>
using namespace std;
using matrix=array<array<int,2>,2>;
const int N=1e5+9,mod=1e9+7;
int n,m,a[N];
inline matrix operator*(const matrix &a,const matrix &b){
    matrix c;
    c[0][0]=c[0][1]=c[1][0]=c[1][1]=0;
    for(int i=0;i<2;i++)
        for(int k=0;k<2;k++)
            for(int j=0;j<2;j++){
                c[i][j]=(c[i][j]+(long long)a[i][k]*b[k][j])%mod;
            }
    return c;
}
inline int power(int a,int b){
    int s=1;
    for(;b;b>>=1,a=(long long)a*a%mod)
        if(b&1)s=(long long)s*a%mod;
    return s;
}
inline matrix power(matrix a,int b){
    matrix s={array<int,2>{1,0},array<int,2>{0,1}};
    for(;b;b>>=1,a=a*a)
        if(b&1)s=s*a;
    return s;
}
const matrix w={array<int,2>{2,1},array<int,2>{0,4}};
int solve(int sum,int pre,int len,int m){
    matrix s={array<int,2>{0,0},array<int,2>{1,0}};
    s=power(w,m)*s;
    // fprintf(stderr,"solve sum=%d pre=%d len=%d m=%d\n",sum,pre,len,m);
    // fprintf(stderr,"s=(%d,%d) || %d\n",s[0][0],s[1][0],power(2,m));
    int res=((long long)pre*power(2,m)+(long long)s[0][0]*len%mod*sum)%mod;
    // cerr<<"! "<<res<<endl;
    return res;
}
int main(){
#ifdef memset0
    freopen("C.in","r",stdin);
#endif
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int sum=0,pre=0,suf=0,len=n;
    for(int i=1;i<=n;i++){
        (sum+=a[i])%=mod;
        (pre+=sum)%=mod;
    }
    sum=0;
    for(int i=n;i>=1;i--){
        (sum+=a[i])%=mod;
        (suf+=sum)%=mod;
    }
    int ans=solve(sum,pre,len,m);
    int sumx,prex,sufx,lenx;
    for(int i=1;i<=m;i++){
        lenx=(len<<1)%mod;
        sumx=(sum<<1)%mod;
        ans=max(ans,solve(sumx,(pre+suf+1ll*sum*len)%mod,lenx,m-i));
        prex=(pre*2ll+1ll*sum*len)%mod;
        sufx=(suf*2ll+1ll*sum*len)%mod;
        len=lenx,sum=sumx,pre=prex,suf=sufx;
        // fprintf(stderr,"len=%d sum=%d pre=%d suf=%d\n",len,sum,pre,suf);
    }
    cout<<ans<<endl;
}