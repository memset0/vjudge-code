#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef std::vector<int> poly;
typedef long long ll;
#define pb push_back
int n,R[20000001],lim,w[20000001],t1[20000001],t2[20000001];
poly A;
const int P=998244353;
inline int read(){
    static int x;x=0;
    static char ch;ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x;
}
inline void write(const int &x){if(x>9)write(x/10);putchar((x%10)+'0');}
inline void print(poly A,int n=-1){if(!~n)n=A.size();for(int i=0;i<n;i++)write(A[i]),putchar(' ');putchar('\n');}
inline int mul(const int &a,const int &b){return (ll)a*b-(ll)a*b/P*P;}
inline int add(int a,const int &b){a+=b;return a>=P?a-P:a;}
inline int sub(int a,const int &b){a-=b;return a<0?a+P:a;}
inline int qsm(int a,int b=P-2){
    int ans=1;
    while(b){if(b&1)ans=mul(ans,a);a=mul(a,a),b>>=1;}
    return ans;
}
inline int inv(const int &a){return (a<=1)?1:mul(P-P/a,inv(P%a));}
inline int upp(int x){
    while((x&-x)!=x)x+=x&-x;
    return x;
}
inline void getRev(int x){
    lim=upp(x);
    for(int i=1;i<lim;i++)R[i]=(R[i>>1]>>1)|((i&1)?(lim>>1):0);
}
inline void NTT(int *A){
    for(register int i=0;i<lim;++i)if(i<R[i])swap(A[i],A[R[i]]);
    for(register int i=1;i<lim;i<<=1)
        for(register int j=0;j<lim;j+=(i<<1))
            for(register int k=0,t=1;k<i;++k){
                const int Ny=mul(A[i+j+k],w[i+k]);
                A[i+j+k]=sub(A[j+k],Ny);
                A[j+k]=add(A[j+k],Ny);
            }
}
inline void NTT_with_limit(int *A,const int &len){
    for(register int i=0;i<lim;++i)if(i<R[i])swap(A[i],A[R[i]]);
    static int half;half=lim>>1;
    for(register int i=1;i<half;i<<=1){
        for(register int j=0;j<lim;j+=(i<<1))
            for(register int k=0;k<i;++k){
                const int Ny=mul(A[i+j+k],w[i+k]);
                A[i+j+k]=sub(A[j+k],Ny);
                A[j+k]=add(A[j+k],Ny);
            }
    }
    for(register int k=0;k<len;++k){
        const int Ny=mul(A[half+k],w[half+k]);
        A[half+k]=sub(A[k],Ny);
        A[k]=add(A[k],Ny);
    }
}
inline poly Res(poly A,int x){return A.resize(x),A;}
inline poly mul(poly A,poly B,int len=-1){
    if(~len){
        if(A.size()>len)A.resize(len);
        if(B.size()>len)B.resize(len);
    }
    int size=A.size()+B.size()-1;
    getRev(size);
    for(int i=A.size()-1;~i;--i)t1[i]=A[i];
    for(int i=A.size();i<lim;++i)t1[i]=0;
    for(int i=B.size()-1;~i;--i)t2[i]=B[i];
    for(int i=B.size();i<lim;++i)t2[i]=0;
    NTT(t1);
    NTT(t2);
    for(int i=0;i<lim;i++)t1[i]=mul(t1[i],t2[i]);
    std::reverse(t1+1,t1+lim);
    if(~len)size=len;
    if(size<(lim>>1))NTT_with_limit(t1,size);
    else NTT(t1);
    lim=inv(lim);
    A.resize(0);
    for(int i=0;i<size;i++)A.pb(mul(t1[i],lim));
    return A;
}
inline int mul_inv(const int &a,const int &b){return sub(add(b,b),mul(a,mul(b,b)));}
inline poly mul_inv(poly A,const poly &B,int len=-1){
    int size=A.size()+B.size()-1;
    getRev(size);
    for(int i=A.size()-1;~i;--i)t1[i]=A[i];
    for(int i=A.size();i<lim;++i)t1[i]=0;
    for(int i=B.size()-1;~i;--i)t2[i]=B[i];
    for(int i=B.size();i<lim;++i)t2[i]=0;
    NTT(t1);
    NTT(t2);
    for(int i=0;i<lim;i++)t1[i]=sub(add(t2[i],t2[i]),mul(t1[i],mul(t2[i],t2[i])));
    std::reverse(t1+1,t1+lim);
    if(~len)size=len;
    if(size<(lim>>1))NTT_with_limit(t1,size);
    else NTT(t1);
//    NTT(t1);
    lim=inv(lim);
    A.resize(0);
    for(int i=0;i<size;i++)A.pb(mul(t1[i],lim));
    return A;
}
inline poly inv(poly A,int n){
    A.resize(n);
    poly B(1,inv(A[0])),t;
    static int last;last=0;
    for(register int len=2;(len>>1)<n;len<<=1){
        for(;last<len;++last)t.pb(last<n?A[last]:0);
        B=mul_inv(t,B);
        B.resize(len);
    }
    B.resize(n);
    return B;
}
inline poly operator+(poly A,const poly &B){
    if(A.size()<B.size())A.resize(B.size());
    for(int i=0;i<A.size();++i)A[i]=add(A[i],i<B.size()?B[i]:0);
    return A;
}
inline poly operator-(poly A,const poly &B){
    if(A.size()<B.size())A.resize(B.size());
    for(int i=0;i<A.size();++i)A[i]=sub(A[i],i<B.size()?B[i]:0);
    return A;
}
inline poly operator-(const int &n,poly B){
    for(int i=0;i<B.size();++i)B[i]=P-B[i];
    B[0]=add(B[0],n);
    return B;
}
inline poly diff(poly A){
    for(int i=0;i<A.size()-1;++i)A[i]=mul(A[i+1],i+1);
    A[A.size()-1]=0;
    return A;
}
inline poly inte(poly A){
    for(int i=A.size()-1;i;--i)A[i]=mul(A[i-1],inv(i));
    A[0]=0;
    return A;
}
inline poly ln(const poly &A,const int &len){return inte(mul(diff(A),inv(A,len),len));}
inline poly exp(const poly &A,const int &n){
    poly B(1,1);
    for(register int i=2;(i>>1)<n;i<<=1)B=mul(B,1-ln(B,i)+A,i);
    B.resize(n);
    return B;
}
int phi[2000001],prime[2000001],top,T,calc[2000001],mu[2000001];//,g[2000001];
bool pri[2000001];
poly operator/(poly &a,poly &b){
    poly c;
}
poly getpoly(int n){
    poly ans(1);
    ans[0]=1;
    for(int i=1;i<=n;i++)
        if(n%i==0&&mu[n/i]==1){
            ans.resize(ans.size()+i);
            for(int j=ans.size()-1;~j;j--){
                ans[j]=-ans[j];
                if(j>=i)ans[j]+=ans[j-i];
            }
        }
    for(int i=1;i<=n;i++)
        if(n%i==0&&mu[n/i]==-1){
            for(int j=0;j<=ans.size();j++){
                if(j>=i)ans[j]-=ans[j-i];
                ans[j]=-ans[j];
            }
            while(!ans.back())ans.pop_back();
        }
    for(int i=0;i<ans.size();i++)printf("%d ",ans[i]);putchar('\n');
    return ans;
}
poly vec[6001];
int num[6001];
bool cmp(int a,int b){
    if(vec[a].size()>vec[b].size())return 0;
    if(vec[a].size()<vec[b].size())return 1;
    for(int i=0;i<vec[a].size()&&i<vec[b].size();i++)
        if(vec[a][i]<vec[b][i])return 1;
        else if(vec[a][i]>vec[b][i])return 0;
    return 0;
}
void out(poly &a){
    bool last=0;
    putchar('(');
    for(int i=a.size()-1;~i;--i)
        if(a[i]){
            if(a[i]>0&&last)putchar('+');
            last=1;
            if(i==0||(a[i]!=1&&a[i]!=-1))printf("%d",a[i]);
            else if(a[i]==-1)putchar('-');
            if(i>1)printf("x^%d",i);
            else if(i==1)printf("x");
        }
    putchar(')');
}
int _mul[4000001],invmul[4000001];
int main(){
    scanf("%d",&n);
    for(int i=1;i<((n+1)<<3);i<<=1){
        int wn=qsm(3,(P-1)/(i<<1));
        w[i]=1;
        for(int j=1;j<i;j++)w[i+j]=mul(w[i+j-1],wn);
    }
    _mul[0]=_mul[1]=invmul[0]=invmul[1]=1;
    for(int i=2;i<=(n<<1);i++)_mul[i]=mul(_mul[i-1],i);
    for(int i=2;i<=(n<<1);i++)invmul[i]=mul(P-P/i,invmul[P%i]);
    for(int i=2;i<=(n<<1);i++)invmul[i]=mul(invmul[i-1],invmul[i]);
    poly f(n+2);
    for(int i=0;i<f.size();i++)f[i]=mul(qsm(i,i),invmul[i]);
    poly g=ln(f,f.size());
    f=mul(f,g);
    for(int i=1;i<=n;i++){
        int u=mul(mul(f[i],_mul[i]),qsm(qsm(i,i),P-2));
        printf("0 %d %d\n",sub(i,u),add(sub(i,u),mul(qsm(i-1,i),qsm(qsm(i,i-1),P-2))));
    }
//    for(int i=1;i<=n;i++)printf("%d ",mul(f[i],_mul[i]));
} 
