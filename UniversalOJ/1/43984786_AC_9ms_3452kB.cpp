/**
 *    author:   memset0
 *    date:     Fri Jul 07 2023 11:45:13 GMT+0800 (China Standard Time)
 *    blog:     https://mem.ac/
 *    library:  https://github.com/memset0/competitive-programming-library
**/
#include<bits/stdc++.h>
// mem/global.hpp
#define OP operator
#define TT template<class T>
#define IL __attribute__((always_inline))inline
#define xx first
#define yy second
#define pb push_back
#define eb emplace_back
#define mp(a,b)std::make_pair(a,b)
typedef unsigned int uint;typedef long long ll;typedef unsigned long long ull;typedef double lf;typedef long double llf;
#ifdef __SIZEOF_INT128__
typedef __int128_t lll;typedef __uint128_t ulll;
#endif
typedef std::pair<int,int>pii;using std::cerr;using std::cin;using std::cout;using std::endl;
#define rep(i,l,r)for(int i=(l),i##end=(r);i<=i##end;i++)
#define per(i,l,r)for(int i=(l),i##end=(r);i>=i##end;i--)
// mem/io.hpp
#define RX x=0;char t=P();while((t<48||t>57)&&t!='-')t=P();bool f=0;if(t=='-')t=P(),f=1;x=t-48;for(t=P();t>=48&&t<=57;t\
=P())x=x*10+t-48
#define RL if(t=='.'){lf u=.1;for(t=P();t>=48&&t<=57;t=P(),u*=0.1)x+=u*(t-48);}if(f)x=-x
#define RU x=0;char t=P();while(t<48||t>57)t=P();x=t-48;for(t=P();t>=48&&t<=57;t=P())x=x*10+t-48
#define WI(S,T)if(x){if(x<0){P('-'),x=-x;if(x<0){*this,(T)x;return*this;}}unsigned char s[S],c=0;while(x)s[c++]=x%10+48\
,x/=10;while(c--)P(s[c]);}else P(48)
#define WL if(y){lf t=0.5;for(int i=y;i--;)t*=0.1;if(x>=0)x+=t;else x-=t,P('-');*this,(ll)(abs(x));P('.');if(x<0)x=-x;w\
hile(y--){x*=10;x-=floor(x*0.1)*10;P(((int)x)%10+48);}}else if(x>=0)*this,(ll)(x+0.5);else*this,(ll)(x-0.5);
#define WU(S)if(x){char s[S],c=0;while(x)s[c++]=x%10+48,x/=10;while(c--)P(s[c]);}else P(48)
constexpr bool IS(char x){return x==10||x==13||x==' ';}TT struct FastRead{T P;IL FastRead&OP,(int&x){RX;if(f)x=-x;retur\
n*this;}IL OP int(){int x;*this,x;return x;}IL FastRead&OP,(ll&x){RX;if(f)x=-x;return*this;}IL OP ll(){ll x;*this,x;ret\
urn x;}IL FastRead&OP,(char&x){for(x=P();IS(x);x=P());return*this;}IL OP char(){char x;*this,x;return x;}IL FastRead&OP\
,(char*x){char t=P();for(;IS(t)&&~t;t=P());if(~t){for(;!IS(t);t=P())*x++=t;}*x++=0;return*this;}IL FastRead&OP,(std::st\
ring&x){x="";char t=P();for(;IS(t)&&~t;t=P());if(~t){for(;!IS(t);t=P())x+=t;}return*this;}IL FastRead&OP,(lf&x){RX;RL;r\
eturn*this;}IL OP lf(){lf x;*this,x;return x;}IL FastRead&OP,(llf&x){RX;RL;return*this;}IL OP llf(){llf x;*this,x;retur\
n x;}IL FastRead&OP,(unsigned&x){RU;return*this;}IL OP unsigned(){unsigned x;*this,x;return x;}IL FastRead&OP,(ull&x){R\
U;return*this;}IL OP ull(){ull x;*this,x;return x;}void file(const char*x){P.file(x);}};struct Fwp{int p;};Fwp prec(int\
 x){return(Fwp){x};}TT struct FastWrite{T P;int p;IL FastWrite&OP,(int x){WI(10,unsigned);return*this;}IL FastWrite&OP,\
(unsigned x){WU(10);return*this;}IL FastWrite&OP,(ll x){WI(19,ull);return*this;}IL FastWrite&OP,(ull x){WU(20);return*t\
his;}IL FastWrite&OP,(char x){P(x);return*this;}IL FastWrite&OP,(const char*x){while(*x)P(*x++);return*this;}IL FastWri\
te&OP,(const std::string&x){return this->OP,(x.c_str());}IL FastWrite&OP,(const Fwp&x){p=x.p;return*this;}IL FastWrite&\
OP,(lf x){int y=p;WL;return*this;}IL FastWrite&OP()(lf x,int y){WL;return*this;}IL FastWrite&OP,(llf x){int y=p;WL;retu\
rn*this;}IL FastWrite&OP()(llf x,int y){WL;return*this;}void file(const char*x){P.file(x);}void flush(){P.flush();}};
#ifdef LOCAL
struct Cg{IL char OP()(){return getchar();}void file(const char*f){freopen(f,"r",stdin);}};struct Cp{IL void OP()(char \
x){putchar(x);}void file(const char*f){freopen(f,"w",stdout);}void flush(){fflush(stdout);}};struct Cpr{IL void OP()(ch\
ar x){fputc(x,stderr);}void file(const char*f){freopen(f,"w",stderr);}void flush(){fflush(stderr);}};TT struct Fd{FastW\
rite<T>*o;template<typename P>IL Fd&OP,(P x){(*o),x,' ';return*this;;}~Fd(){(*o),'\n';}};TT struct Fds{FastWrite<T>*o;t\
emplate<typename P>IL Fd<T>OP,(P x){(*o),x,' ';return(Fd<T>){o};}};FastWrite<Cpr>err;Fds<Cpr>dbg{&err};
#else
#define BSZ 131072
struct Cg{char t[BSZ+1],*o,*e;Cg(){e=o=t+BSZ;}IL char OP()(){if(o==e)t[fread(o=t,1,BSZ,stdin)]=0;return*o++;}void file(\
const char*f){freopen(f,"r",stdin);}};struct Cp{char t[BSZ+1],*o,*e;Cp(){e=(o=t)+BSZ;}IL void OP()(char p){if(o==e)fwri\
te(o=t,1,BSZ,stdout);*o++=p;}void file(const char*f){freopen(f,"w",stdout);}void flush(){fwrite(t,1,o-t,stdout),o=t,ffl\
ush(stdout);}~Cp(){fwrite(t,1,o-t,stdout);}};
#endif
FastRead<Cg>in;FastWrite<Cp>out;const char dl='\n';
int main() {
#ifdef memset0
  in.file("1.in");
#endif
  int a, b;
  in, a, b;
  out, (a + b), dl;
}
