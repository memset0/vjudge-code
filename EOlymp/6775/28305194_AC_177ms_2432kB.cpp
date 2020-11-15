#include<bits/stdc++.h>

namespace mem{
  #ifdef memset0
  #else
    #define MEM_FASTIO
  #endif

  #ifdef __SIZEOF_INT128__
    #define MEM_INT128
  #endif

  #define __integer_mapper(func)    \
      func(int)                     \
      func(unsigned int)            \
      func(long long int)           \
      func(unsigned long long int)
  #define __float_mapper(func)      \
      func(float)                   \
      func(double)                  \
      func(long double)
  
  namespace stdval{
    using i32=int;
    using i64=long long;
    using u32=unsigned;
    using u64=unsigned long long;
    using f32=float;
    using f64=double;
    using f96=long double;
  #ifdef MEM_INT128
    using i128=__int128_t;
    using u128=__uint128_t;
  #endif
  }
  
  namespace utils{
    using std::cin;
    using std::tie;
    using std::get;
    using std::cout;
    using std::cerr;
    using std::endl;
    using std::swap;
    using std::sort;
    using std::find;
    using std::unique;
    using std::reverse;
    using std::shuffle;
    using std::function;
    using std::make_pair;
    using std::make_tuple;
    using std::accumulate;
    using std::lower_bound;
    using std::upper_bound;
    using std::max_element;
    using std::min_element;
  }
  
  namespace math{
    using namespace stdval;
    using std::max;
    using std::min;
    template<class T> inline T abs(T x){return x<0?-x:x;}
    template<class T> inline T gcd(T n,T m){return m?gcd(m,n%m):n;}
    template<class T> inline T lcm(T n,T m){return n/gcd(n,m)*m;}
    
    struct FastDiv{
      u64 t,i;
      inline FastDiv(u64 p):t(u64(-1)/p),i(mul_inv(p)){}
      
      inline bool divide(u64 n){return n*i<=t;}
      inline bool divide(i64 n){return u64(n<0?-n:n)*i<=t;}
      inline u64 mul_inv(u64 n){
        u64 x=n;
        for(int i=0;i<5;++i)x*=2-n*x;
        return x;
      }
    };
  
  #ifdef MEM_INT128
    struct FastMod{
      u64 m,b;
      inline FastMod(u64 b):m(u64((u128(1)<<64)/b)),b(b){}
      
      inline u64 reduce(u64 a){
        u64 q=(u64)((u128(m)*a)>>64);
        u64 r=a-q*b;
        return r>=b?r-b:r;
      }
    };
  #endif
  }
  
  namespace io{
  #ifdef MEM_FASTIO
    namespace fastio{
      const int BUFFER=1<<18;
      char ibuf[BUFFER],*iS,*iT;
      inline int getc(){
        if(iS==iT){
          iT=(iS=ibuf)+fread(ibuf,1,BUFFER,stdin);
          return iS==iT?EOF:*iS++;
        }else{
          return *iS++;
        }
      }
      char obuf[BUFFER],*oS=obuf,*oT=oS+BUFFER-1;
      inline void flush(){
        fwrite(obuf,1,oS-obuf,stdout);
        oS=obuf;
      }
      inline void putc(int x){
        *oS++=x;
        if(oS==oT)flush();
      }
      struct Flusher{~Flusher(){flush();}}flusher;
    }
    using fastio::getc;
    using fastio::putc;
    inline void flush(){fastio::flush(),fflush(stdout);}
  #else
    inline int getc(){return getchar();}
    inline void putc(int c){putchar(c);}
    inline void flush(){fflush(stdout);}
  #endif
    
    template<class T> inline void read_digit(T &x){x=getc(); while(!isdigit(x))x=getc();}
    template<class T> inline void read_alpha(T &x){x=getc(); while(!isalpha(x))x=getc();}
    template<class T> inline void read_lower(T &x){x=getc(); while(!islower(x))x=getc();}
    template<class T> inline void read_upper(T &x){x=getc(); while(!isupper(x))x=getc();}
    inline int read_digit(){int x; read_digit(x); return x;}
    inline int read_alpha(){int x; read_alpha(x); return x;}
    inline int read_lower(){int x; read_lower(x); return x;}
    inline int read_upper(){int x; read_upper(x); return x;}
  
  #define __read(T)                             \
      inline void read(T &x) {                  \
        x=0; bool f=0; char c=getc();           \
        while(!isdigit(c))f^=c=='-',c=getc();   \
        while(isdigit(c))x=x*10+c-'0',c=getc(); \
        if(f)x=-x;                              \
      }
    __integer_mapper(__read)
  #undef __read
    
    inline void read(char &x){x=getc();}
    inline void read(char *s){
      char c=getc();
      while(~c&&!isspace(c))*s++=c,c=getc();
      *s++='\0';
    }
    
    template<class T=int> inline T read(){T x; read(x); return x;}
    template<class T,class... Args> inline void read(T &x,Args &... args){
      read(x),read(args...);
    }
  
  #define __print(T)           \
      inline void print(T x){  \
        if(x<0)putc('-'),x=-x; \
        if(x>9)print(x/10);    \
        putc('0'+x%10);        \
      }
    __integer_mapper(__print)
  #undef __print
    
    inline void print(char x){putc(x);}
    inline void print(const char *s){
      size_t len=strlen(s);
      for(size_t i=0;i<len;i++)putc(s[i]);
    }
    
    template<class T,class... Args> inline void print(const T &x,Args... args){
      print(x),print(args...);
    }
    template<class... Args> inline void println(Args... args){
      print(args...),putc('\n');
    }
  }
  
  #undef __integer_mapper
  #undef __float_mapper
  #undef __string_mapper
  #undef __string_join_mapper

  using namespace io;
  using namespace math;
  using namespace utils;
  using namespace stdval;
} // namespace mem
using namespace mem;

const int N=4e3+9;
int T,n,mod,a[N],f[N];

int main(){
  read(T);
  while(T--){
    read(n,mod);
    FastMod moder(mod);
    for(int i=1;i<=n;i++){
      read(a[i]);
    }
    f[1]=1,f[2]=2;
    for(int i=3;i<=n;i++){
      f[i]=f[i-1]+f[i-2];
      if(f[i]>=mod)f[i]-=mod;
    }
    a[n+1]=0;
    for(int i=1;i<=n;i++){
      for(int j=n+1;j>i;j--){
        a[j]-=moder.reduce((unsigned long long)a[j-1]*f[i]);
        if(a[j]<0)a[j]+=mod;
      }
    }
    println((mod-a[n+1])%mod); 
  }
}