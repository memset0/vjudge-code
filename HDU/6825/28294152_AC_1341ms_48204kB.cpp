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
int _mul[10000001],invmul[10000001],g[10000001],T;
int main(){
    scanf("%d",&T);
    for(int fd=1;fd<=T;fd++){
        scanf("%d",&n);
        _mul[0]=_mul[1]=invmul[0]=invmul[1]=1;
        g[0]=g[1]=1;
        for(int i=2;i<=(n);i++)_mul[i]=mul(_mul[i-1],i);
        for(int i=2;i<=(n);i++)invmul[i]=mul(P-P/i,invmul[P%i]);
        for(int i=2;i<=(n);i++)invmul[i]=mul(invmul[i-1],invmul[i]);
        for(int i=2;i<=(n);i++)g[i]=mul(g[i-2],i);
        if(n==1){
            puts("1");
            continue;
        }
        for(int i=1;i<=(n>>1);i++)printf("0 ");
        int v=qsm(g[n-1],P-2);
        for(int i=1;i<=(n>>1);i++)printf("%d ",mul(v,mul(g[(i<<1)-1],mul(_mul[(n>>1)+i-1],invmul[(i<<1)-1]))));
        printf("%d\n",mul(v,mul(g[((n>>1)<<1)-1],mul(_mul[(n>>1)+(n>>1)-1],invmul[((n>>1)<<1)-1]))));
    }
} 