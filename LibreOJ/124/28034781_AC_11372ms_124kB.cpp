#define l long long
const int p=1e9+7;int i,n,k,s;l f(int a,int b){int s=1;for(;b;b>>=1,a=(l)a*a%p)if(b&1)s=(l)s*a%p;return s;}main(){__builtin_scanf("%d%d",&n,&k);for(i=1;i<=n;i++)s=(s+n/i*f(i,k))%p;__builtin_printf("%d",s);}
