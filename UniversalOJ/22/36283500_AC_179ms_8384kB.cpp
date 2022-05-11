#include<bits/stdc++.h>

namespace mem{ //v1.6.11
#define MEM_IO
#define MEM_STL
#define MEM_MATH
#define MEM_UTILS
#define MEM_MODINT
#define MEM_RANDOM
#define MEM_STDVAL
#ifdef memset0
#else
  #define MEM_FASTIO
#endif

#ifdef __SIZEOF_INT128__
  #define MEM_INT128
#endif

#define __integer_mapper(func)     \
    func(int)                      \
    func(unsigned int)             \
    func(long long)                \
    func(unsigned long long)
#define __float_mapper(func)       \
    func(float)                    \
    func(double)
#define __string_mapper(func) \
    func(char *)              \
    func(string &)            \
    func(std::string &)
#define __string_join_mapper(func)                                              \
    func(vector<string>,string)                                                 \
    func(std::vector<string>,string)                                            \
    template<class T> func(vector<T>,to_string)                                 \
    template<class T> func(std::vector<T>,to_string)

#ifdef MEM_STDVAL
  namespace stdval{
    using i32=int;
    using i64=long long;
    using u32=unsigned int;
    using u64=unsigned long long;
    using f32=float;
    using f64=double;
#ifdef MEM_INT128
    using i128=__int128_t;
    using u128=__uint128_t;
#endif
  }
#endif

#ifdef MEM_UTILS
  namespace utils{
    using std::cin;
    using std::tie;
    using std::max;
    using std::min;
    using std::cout;
    using std::cerr;
    using std::endl;
    using std::swap;
    using std::sort;
    using std::reverse;
    using std::function;
    using std::make_pair;
    using std::lower_bound;
    using std::upper_bound;
    using std::max_element;
    using std::min_element;
  }
#endif

#ifdef MEM_IO
  namespace io{
#ifdef MEM_FASTIO
    namespace fastio{
      const int BUFFER=1<<21;
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
#else
    inline int getc(){return getchar();}
    inline void putc(int c){putchar(c);}
#endif
    
    template<class T> inline void readDigit(T &x){
      x=getc();
      while(!isdigit(x))x=getc();
    }
    inline int readDigit(){
      int x;
      readDigit(x);
      return x;
    }
    template<class T> inline void readAlpha(T &x){
      x=getc();
      while(!isalpha(x))x=getc();
    }
    inline int readAlpha(){
      int x;
      readAlpha(x);
      return x;
    }
    template<class T> inline void readInt(T &x){
      x=0;
      bool f=0;
      char c=getc();
      while(!isdigit(c))f^=c=='-',c=getc();
      while(isdigit(c))x=x*10+c-'0',c=getc();
      if(f)x=-x;
    }

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
    template<class T=int> inline T read(){
      T x;
      read(x);
      return x;
    }
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
      int len=strlen(s);
      for(int i=0;i<len;i++)putc(s[i]);
    }
    inline void print(const std::string &s){
      for(int i=0;i<s.length();i++)putc(s[i]);
    }
    
    template<class T,class... Args> inline void print(const T &x,Args... args){
      print(x),print(args...);
    }
    template<class... Args> inline void println(Args... args){
      print(args...),putchar('\n');
    }
  }
#endif

#ifdef MEM_RANDOM
  namespace random{
    const int LuckyNumber=20040725;
    std::mt19937 rng(LuckyNumber^std::chrono::steady_clock::now().time_since_epoch().count());
    std::mt19937_64 rng64(LuckyNumber^std::chrono::steady_clock::now().time_since_epoch().count());
    
    template<class T> inline T rand(T l,T r){return std::uniform_int_distribution<T>(l,r)(rng);}
    template<class T> inline T rand64(T l,T r){return std::uniform_int_distribution<T>(l,r)(rng);}
  }
#endif

#ifdef MEM_MODINT
  namespace modint{
    template<const int mod> struct Z{
      int x;
      inline Z(){x=0;}
      inline Z(int t){x=t;}
      
      inline void operator-=(Z a){(x-=a.x)<0&&(x+=mod);}
      inline void operator+=(Z a){(x+=a.x)>=mod&&(x-=mod);}
      inline void operator*=(Z a){x=(long long)x*a.x%mod;}
      
      friend inline Z operator*(Z a,Z b){return (long long)a.x*b.x%mod;}
      friend inline Z operator-(Z a,Z b){return ((a.x-=b.x)<0&&(a.x+=mod)),a;}
      friend inline Z operator+(Z a,Z b){return ((a.x+=b.x)>=mod&&(a.x-=mod)),a;}
    };
    
    template<const int mod> inline Z<mod> finv(Z<mod> x){
      if(x.x<2)return x;
      return (mod-mod/x.x)*finv(mod%x.x);
    }
    template<const int mod> inline Z<mod> fpow(Z<mod> a,int b){
      Z <mod> s=1;
      for(;b;b>>=1,a=a*a)
        if(b&1)s=s*a;
      return s;
    }
    
    template<const int mod> inline void init_inverse(int n,Z<mod> *inv){
      inv[0]=inv[1]=1;
      for(int i=2;i<n;i++)inv[i]=(mod-mod/i)*inv[mod%i];
    }
    template<const int mod> inline void init_factorial(int n,Z<mod> *fac,Z<mod> *ifac){
      fac[0]=1,init_inverse(n,ifac);
      for(int i=1;i<n;i++)fac[i]=fac[i-1]*i,ifac[i]=ifac[i-1]*ifac[i];
    }
  }
#endif

#ifdef MEM_MATH
  namespace math{
    using namespace stdval;
    using std::max;
    using std::min;
    template<class T> inline T abs(T x){return x<0?-x:x;}
    template<class T> inline T gcd(T n,T m){return m?gcd(m,n%m):n;}
    template<class T> inline T lcm(T n,T m){return n/gcd(n,m)*m;}
    
    template<const u64 p> struct FastDiv{
      u64 t,i;
      inline FastDiv():t(u64(-1)/p),i(mul_inv(p)){}
      
      inline bool divide(u64 n){return n*i<=t;}
      inline bool divide(i64 n){return u64(n<0?-n:n)*i<=t;}
      inline u64 mul_inv(u64 n){
        u64 x=n;
        for(int i=0;i<5;++i)x*=2-n*x;
        return x;
      }
    };

#ifdef MEM_INT128
    template<const u64 b> struct FastMod{
      u64 m;
      inline FastMod():m(u64((u128(1)<<64)/b)){}
      
      inline u64 reduce(u64 a){
        u64 q=(u64)((u128(m)*a)>>64);
        u64 r=a-q*b;
        return r>=b?r-b:r;
      }
    };
#endif
  }
#endif

#ifdef MEM_STL
  namespace stl{
    using std::pair;

    template<class T> struct vector:std::vector<T>{
      using std::vector<T>::vector;
      vector():std::vector<T>(){}
      vector(const std::vector<T> &plain):std::vector<T>(plain){}
      
      inline void read(int s=-1){
        if(~s)this->resize(s);
        for(size_t i=0;i<this->size();i++){
          io::read(this->operator[](i));
        }
      }
      inline void print(char pt0=' ',char pt1='\n'){
        for(size_t i=0;i<this->size();i++){
          io::print(this->operator[](i));
          if(i+1<this->size())io::putc(pt0);
        }
        io::putc(pt1);
      }
      
      inline void sort(){std::sort(this->begin(),this->end());}
      inline void concat(const vector &rhs){this->insert(this->end(),rhs.begin(),rhs.end());}
      inline bool includes(const T &x) const{return std::find(this->begin(),this->end(),x)!=this->end();}
      
      inline vector slice(int l,int r) const{
        if(l>r)return {};
        if(r<this->size())return vector(this->begin()+l,this->begin()+r);
        vector<int> rsp=(this->begin()+l,this->end());
        return rsp.resize(r-l),rsp;
      }
      
      inline void from(const std::set<T> &src){
        this->resize(src.size());
        auto it=this->begin();
        for(const T e:src)*it++=e;
      }
      
      template<class Function> inline void forEach(Function func){for(const auto &it:*this)func(it);}
      
      template<class R,class Function> inline vector<R> _map(Function func) const{
        vector <R> res(this->size());
        for(size_t i=0;i<this->size();i++)
          res[i]=func(this->operator[](i));
        return res;
      }
      template<class R> inline vector<R> map(R func(T)) const{return this->_map<R>(func);}
      template<class R> inline vector<R> map(const std::function<R(T)> &func) const{return this->_map<R>(func);}
    };
    
    struct string:std::string{
      using std::string::string;
      string():std::string(""){}
      string(const std::string &plain):std::string(plain){}

#define __join_declaration(Vector,_)            \
      inline string join(const Vector &) const;
      __string_join_mapper(__join_declaration)
#undef __join_declaration
      
      vector<string> split(const string &delim)const{
        if(this->empty())return {};
        char *src=new char[this->length()+1];
        strcpy(src,this->c_str());
        char *tar=new char[delim.length()+1];
        strcpy(tar,delim.c_str());
        vector<string> rsp;
        for(char *pos=strtok(src,tar);pos;pos=strtok(nullptr,tar))
          rsp.push_back(string(pos));
        delete[] src;
        delete[] tar;
        return rsp;
      }
      
      template<class... Args> static inline string format(const char *fm,Args... args){
        int len=snprintf(nullptr,0,fm,args...);
        char *buf=new char[len+1];
        snprintf(buf,len+1,fm,args...);
        string str(buf);
        delete[] buf;
        return str;
      }
      template<class... Args> static inline string format(const string &fm,Args... args){
        return format(fm.c_str(),args...);
      }
    };

#define __to_string(T)                   \
    inline string to_string(const T &x){ \
      return std::to_string(x);          \
    }
    __float_mapper(__to_string)
    __integer_mapper(__to_string)
#undef __to_string
    template<class T> inline string to_string(const vector<T> &vet){return "{"+string(",").join(vet)+"}";}
    template<class T> inline string to_string(const std::vector<T> &vet){return to_string(vector<T>(vet.begin(),vet.end()));}
    template<const int mod> inline string to_string(const mem::modint::Z<mod> &zval){return std::to_string(zval.x);}

#define __join_instantiation(Vector,to_string)          \
    inline string string::join(const Vector &vet)const{ \
      if(!vet.size())return "";                         \
      string res=to_string(vet[0]);                     \
      for(size_t i=1;i<vet.size();i++){                 \
        res+=*this;                                     \
        res+=to_string(vet[i]);                         \
      }                                                 \
      return res;                                       \
    }
    __string_join_mapper(__join_instantiation)
#undef __join_instantiation
    
    inline void print(const stl::string &s){
      for(size_t i=0;i<s.length();i++)mem::io::putc(s[i]);
    }

#define __printfm(T)                                                      \
    template<class... Args> inline void printfm(const T fm,Args... args){ \
      print(stl::string().format(fm,args...));                            \
    }
    __string_mapper(__printfm)
#undef __printfm
  }
#endif

#undef __integer_mapper
#undef __float_mapper
#undef __string_mapper
#undef __string_join_mapper

#ifdef MEM_IO
  using namespace io;
#endif
#ifdef MEM_STL
  using namespace stl;
#endif
#ifdef MEM_MATH
  using namespace math;
#endif
#ifdef MEM_UTILS
  using namespace utils;
#endif
#ifdef MEM_MODINT
  using namespace modint;
#endif
#ifdef MEM_RANDOM
  using namespace random;
#endif
#ifdef MEM_STDVAL
  using namespace stdval;
#endif
}

/*
 ██░ ██ ▓█████  ██▓     ██▓     ▒█████     ▄▄▄█████▓ ██░ ██ ▓█████     ▄████▄   ██▀███   █    ██ ▓█████  ██▓        █     █░ ▒█████   ██▀███   ██▓    ▓█████▄  ▐██▌ 
▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    ▒██▒  ██▒   ▓  ██▒ ▓▒▓██░ ██▒▓█   ▀    ▒██▀ ▀█  ▓██ ▒ ██▒ ██  ▓██▒▓█   ▀ ▓██▒       ▓█░ █ ░█░▒██▒  ██▒▓██ ▒ ██▒▓██▒    ▒██▀ ██▌ ▐██▌ 
▒██▀▀██░▒███   ▒██░    ▒██░    ▒██░  ██▒   ▒ ▓██░ ▒░▒██▀▀██░▒███      ▒▓█    ▄ ▓██ ░▄█ ▒▓██  ▒██░▒███   ▒██░       ▒█░ █ ░█ ▒██░  ██▒▓██ ░▄█ ▒▒██░    ░██   █▌ ▐██▌ 
░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    ▒██   ██░   ░ ▓██▓ ░ ░▓█ ░██ ▒▓█  ▄    ▒▓▓▄ ▄██▒▒██▀▀█▄  ▓▓█  ░██░▒▓█  ▄ ▒██░       ░█░ █ ░█ ▒██   ██░▒██▀▀█▄  ▒██░    ░▓█▄   ▌ ▓██▒ 
░▓█▒░██▓░▒████▒░██████▒░██████▒░ ████▓▒░     ▒██▒ ░ ░▓█▒░██▓░▒████▒   ▒ ▓███▀ ░░██▓ ▒██▒▒▒█████▓ ░▒████▒░██████▒   ░░██▒██▓ ░ ████▓▒░░██▓ ▒██▒░██████▒░▒████▓  ▒▄▄  
 ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░░ ▒░▒░▒░      ▒ ░░    ▒ ░░▒░▒░░ ▒░ ░   ░ ░▒ ▒  ░░ ▒▓ ░▒▓░░▒▓▒ ▒ ▒ ░░ ▒░ ░░ ▒░▓  ░   ░ ▓░▒ ▒  ░ ▒░▒░▒░ ░ ▒▓ ░▒▓░░ ▒░▓  ░ ▒▒▓  ▒  ░▀▀▒ 
 ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░  ░ ▒ ▒░        ░     ▒ ░▒░ ░ ░ ░  ░     ░  ▒     ░▒ ░ ▒░░░▒░ ░ ░  ░ ░  ░░ ░ ▒  ░     ▒ ░ ░    ░ ▒ ▒░   ░▒ ░ ▒░░ ░ ▒  ░ ░ ▒  ▒  ░  ░ 
 ░  ░░ ░   ░     ░ ░     ░ ░   ░ ░ ░ ▒       ░       ░  ░░ ░   ░      ░          ░░   ░  ░░░ ░ ░    ░     ░ ░        ░   ░  ░ ░ ░ ▒    ░░   ░   ░ ░    ░ ░  ░     ░ 
 ░  ░  ░   ░  ░    ░  ░    ░  ░    ░ ░               ░  ░  ░   ░  ░   ░ ░         ░        ░        ░  ░    ░  ░       ░        ░ ░     ░         ░  ░   ░     ░    
*/

const int N=5e3+10,mod=998244353;
using z=mem::Z<mod>;
using namespace mem::io;
using namespace mem::utils;

int n,m,lim,a[N],b[N],s[N];
bool tag[N],pre[N>>2][N];
z f[N],inv[N],fac[N],ifac[N];

inline z C(int n,int m){return n<m?0:fac[n]*ifac[m]*ifac[n-m];}

int solve1(){
  for(int i=n;i>=1;i--){
    pre[i][m%a[i]]=tag[m%a[i]]=true;
    for(int j=0;j<=m;j++){
      pre[i][j%a[i]]|=tag[j];
      tag[j%a[i]]|=pre[i][j%a[i]];
    }
  }
  for(int i=m;i>=0;i--)
    if(pre[1][i]){
      return i;
    }
  assert(0);
}

int solve2(){
  for(int i=0;i<=m;i++)if(b[i]){ //i=mod
    for(int j=i;j<=m;j++)if(f[j%i].x){ //j=last
      int x=s[j%i],y=s[j]-s[j%i];
      // printf("i=%d j=%d j%%i=%d => %d %d => %d %d %d\n",i,j,j%i,x,y,f[j%i].x,b[i],C(x+y-1,x).x);
      f[j]+=f[j%i]*b[i]*C(x+y-1,x)*fac[y-1];
    }
  }
  // for(int i=0;i<=m;i++)print(f[i].x," \n"[i==m]);
  z res=f[m]*fac[n]*ifac[s[m]];
  return (int&&)res;
}

int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  mem::modint::init_inverse(N,inv);
  mem::modint::init_factorial(N,fac,ifac);
  read(n,m);
  for(int i=1;i<=n;i++)read(a[i]),b[a[i]]++;
  sort(a+1,a+n+1);
  lim=max(*max_element(a+1,a+n+1),m);
  for(int i=1;i<=lim;i++)s[i]=s[i-1]+b[i];
  int ans1=solve1();
  f[ans1]=1;
  int ans2=solve2();
  print(ans1,'\n',ans2,'\n');
}