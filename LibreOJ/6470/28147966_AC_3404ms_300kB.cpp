#include<bits/stdc++.h>

namespace mem{ //v2.5.0 => size: 15.47KiB
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
  
  namespace random{
    const int LuckyNumber=20040726; // Kanbe Kotori's Birthday
    std::mt19937 rng(LuckyNumber^std::chrono::steady_clock::now().time_since_epoch().count());
    std::mt19937_64 rng64(LuckyNumber^std::chrono::steady_clock::now().time_since_epoch().count());
    
    template<class T> inline T rand(T l,T r){return std::uniform_int_distribution<T>(l,r)(rng);}
    template<class T> inline T rand64(T l,T r){return std::uniform_int_distribution<T>(l,r)(rng);}
  }
  
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
      Z<mod> s=1;
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
  
  namespace math{
    using std::max;
    using std::min;
    template<class T> inline T abs(T x){return x<0?-x:x;}
    template<class T> inline T gcd(T n,T m){return m?gcd(m,n%m):n;}
    template<class T> inline T lcm(T n,T m){return n/gcd(n,m)*m;}
    
    template<const stdval::u64 p> struct FastDiv{
      stdval::u64 t,i;
      inline FastDiv():t(stdval::u64(-1)/p),i(mul_inv(p)){}
      
      inline bool divide(stdval::u64 n){return n*i<=t;}
      inline bool divide(stdval::i64 n){return stdval::u64(n<0?-n:n)*i<=t;}
      inline stdval::u64 mul_inv(stdval::u64 n){
        stdval::u64 x=n;
        for(int i=0;i<5;++i)x*=2-n*x;
        return x;
      }
    };
  
  #ifdef MEM_INT128
    template<const stdval::u64 b> struct FastMod{
      stdval::u64 m;
      inline FastMod():m(stdval::u64((stdval::u128(1)<<64)/b)){}
      
      inline stdval::u64 reduce(stdval::u64 a){
        stdval::u64 q=(stdval::u64)((stdval::u128(m)*a)>>64);
        stdval::u64 r=a-q*b;
        return r>=b?r-b:r;
      }
    };
  #endif
  }
  
  namespace container{
    using std::pair;
    using std::tuple;
    using std::set;
    using std::unordered_set;
    using std::map;
    using std::unordered_map;
    using std::queue;
    using std::stack;
    using std::priority_queue;
    
    using std::tie;
    using std::get;
    using std::make_pair;
    using std::make_tuple;
    
    template<class T> struct vector:std::vector<T>{
      using std::vector<T>::vector;
      vector():std::vector<T>(){}
      explicit vector(const std::vector<T> &plain):std::vector<T>(plain){}
      
      inline void concat(const vector &rhs){this->insert(this->end(),rhs.begin(),rhs.end());}
      inline bool includes(const T &x) const{return std::find(this->begin(),this->end(),x)!=this->end();}
      template<class Function> inline void forEach(Function func){for(const auto &it:*this)func(it);}

      inline void sort(){std::sort(this->begin(),this->end());}
      template<class Function> inline void sort(Function func){std::sort(this->begin(),this->end(),func);}
      
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
      
      template<class R,class Function> inline vector<R> _map(Function func) const{
        vector<R> res(this->size());
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
      
      template<class T> inline string join(const vector<T> &vet) const;
      
      vector<string> split(const string &dim) const{
        if(this->empty())return {};
        char *src=new char[this->length()+1];
        strcpy(src,this->c_str());
        char *tar=new char[dim.length()+1];
        strcpy(tar,dim.c_str());
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
    
    inline string to_string(const string &s){return s;}
    inline string to_string(const char *s){return string(s);}
    inline string to_string(const std::string &s){return string(s);}
    template<const int mod> inline string to_string(const modint::Z<mod> &v){return std::to_string(v.x);}
    
    template<class T> inline string to_string(const vector<T> &ctn){return "["+string(",").join(ctn)+"]";}
    template<class T> inline string to_string(const set<T> &ctn){
      string result="{";
      bool flag=false;
      for(const auto &it:ctn){
        if(flag)result+=",";
        flag=true;
        result+=to_string(it);
      }
      return result+"}";
    }
    template<class T1,class T2> inline string to_string(const map<T1,T2> &ctn){
      string result="{";
      bool flag=false;
      for(const auto &it:ctn){
        if(flag)result+=",";
        flag=true;
        result+=to_string(it.first)+":"+to_string(it.second);
      }
      return result+"}";
    }
    
    template<class T> inline string string::join(const vector<T> &vet) const{
      if(!vet.size())return "";
      string res=to_string(vet[0]);
      for(size_t i=1;i<vet.size();i++){
        res+=*this;
        res+=to_string(vet[i]);
      }
      return res;
    }
    
    inline string operator "" _s(const char *s){return string(s);}
    inline string operator "" _s(const char *s,size_t len){return string(s,len);}
    inline string operator "" _s(long double x){return to_string(x);}
    inline string operator "" _s(unsigned long long int x){return to_string(x);}
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
    inline void read(container::string &s){
      char c=getc();
      s="";
      while(~c&&!isspace(c))s+=c,c=getc();
    }
    template<const int mod> inline void read(const modint::Z<mod> &x){read(x.x);}
    
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
      size_t len=strlen(s);
      for(size_t i=0;i<len;i++)putc(s[i]);
    }
    inline void print(const container::string &s){
      for(size_t i=0;i<s.length();i++)putc(s[i]);
    }
    template<const int mod> inline void print(const modint::Z<mod> &x){print(x.x);}
    
    template<class T,class... Args> inline void print(const T &x,Args... args){
      print(x),print(args...);
    }
    template<class... Args> inline void println(Args... args){
      print(args...),putc('\n');
    }
    
    template<class... Args> inline void printfm(const char *formatter,Args... arguments){
      print(container::string().format(formatter,arguments...));
    }
    template<class... Args> inline void printfm(const container::string &formatter,Args... arguments){
      print(container::string().format(formatter,arguments...));
    }
  }
  
  namespace logger{
    enum ConsoleColor{
      NOPE=-1,BLACK,RED,GREEN,YELLOW,BLUE,PURPLE,DEEPBLUE
    };
    template<const ConsoleColor color=NOPE,class... Args> inline void log(const char *formatter,Args... args){
      if(~color){
        fprintf(stderr,"\033[%dm",30+color);
        fprintf(stderr,formatter,args...);
        fprintf(stderr,"\033[0m");
      }else{
        fprintf(stderr,formatter,args...);
      }
    }
    template<const ConsoleColor color=NOPE,class... Args> inline void logln(const char *formatter,Args... args){
      if(~color){
        fprintf(stderr,"\033[%dm",30+color);
        fprintf(stderr,formatter,args...);
        fprintf(stderr,"\033[0m\n");
      }else{
        fprintf(stderr,formatter,args...);
        fprintf(stderr,"\n");
      }
    }
    template<class T> inline void logs(const T &x){
      fprintf(stderr,container::to_string(x).c_str());
    }
    template<class T,class... Args> inline void logs(const T &x,Args... args){
      logs(x),logs(args...);
    }
    template<class... Args> inline void logsln(Args... args){
      logs(args...);
      fprintf(stderr,"\n");
    }
  }
  
  namespace fileio{
    inline void fileInput(const char *dir){freopen(dir,"r",stdin);}
    inline void fileOutput(const char *dir){freopen(dir,"w",stdout);}
    inline void fileInput(const std::string &dir){fileInput(dir.c_str());}
    inline void fileOutput(const std::string &dir){fileOutput(dir.c_str());}
    inline void fileInput(const container::string &dir){fileInput(dir.c_str());}
    inline void fileOutput(const container::string &dir){fileOutput(dir.c_str());}

    template<class T> inline void fileIO(const T name){
      using namespace container;
      fileInput(name+".in"_s);
      fileOutput(name+".out"_s);
    }

  #ifdef memset0
    template<class T> inline void localFileIO(T name){fileIO(name);}
    template<class T> inline void localFileInput(T dir){fileInput(dir);}
    template<class T> inline void localFileOuput(T dir){fileOutput(dir);}
    template<class T> inline void judgeFileIO(T name){}
    template<class T> inline void judgeFileInput(T dir){}
    template<class T> inline void judgeFileOuput(T dir){}
  #else
    template<class T> inline void localFileIO(T name){}
    template<class T> inline void localFileInput(T dir){}
    template<class T> inline void localFileOuput(T dir){}
    template<class T> inline void judgeFileIO(T name){fileIO(name);}
    template<class T> inline void judgeFileInput(T dir){fileInput(dir);}
    template<class T> inline void judgeFileOuput(T dir){fileOutput(dir);}
  #endif

    inline void fastCppIO(){
      std::ios::sync_with_stdio(0);
      std::cin.tie(0);
      std::cout.tie(0);
    }
  }

  #undef __integer_mapper
  #undef __float_mapper
  #undef __string_mapper
  #undef __string_join_mapper

  using namespace io;
  using namespace math;
  using namespace utils;
  using namespace modint;
  using namespace random;
  using namespace stdval;
  using namespace fileio;
  using namespace logger;
  using namespace container;
} // namespace mem
using namespace mem;

namespace geometry{
  const double eps=0;
  struct node{
    double x,y;
    inline double atan()const{return atan2(y,x);}
    inline node operator+(const node &rhs)const{return {x+rhs.x,y+rhs.y};}
    inline node operator-(const node &rhs)const{return {x-rhs.x,y-rhs.y};}
    inline bool operator<(const node &rhs)const{return abs(x-rhs.x)<=eps?y+eps<rhs.y:x+eps<rhs.x;}
    inline bool operator>(const node &rhs)const{return abs(x-rhs.x)<=eps?rhs.y+eps<y:rhs.x+eps<x;}
    inline bool operator==(const node &rhs)const{return abs(x-rhs.x)<=eps&&abs(y-rhs.y)<=eps;}
  };
  inline double distance(const node &a,const node &b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
  inline double cross(const node &a,const node &b){return a.x*b.y-b.x*a.y;}
  inline double cross(const node &u,const node &a,const node &b){return (a.x-u.x)*(b.y-u.y)-(b.x-u.x)*(a.y-u.y);}
  struct line{
    node a,b;
    inline bool through(const node &t)const{
      return cross(t,a,b)==0;
    }
  };
}
using namespace geometry;

const int N=205;
int n;
node a[N];
line e[N];
double ans;

inline pair<int,node> intersection(const line &a,const line &b){ //a->segment b->line
  if((a.a.x-a.b.x)*(b.a.y-b.b.y)==(a.a.y-a.b.y)*(b.a.x-b.b.x)){
    return {a.through(b.a)?3:0,{0,0}};
  }
  double u=((a.a.y-b.a.y)*(b.a.x-b.b.x)-(a.a.x-b.a.x)*(b.a.y-b.b.y))/
    ((a.a.x-a.b.x)*(b.a.y-b.b.y)-(a.a.y-a.b.y)*(b.a.x-b.b.x));
  node p={u*(a.a.x-a.b.x)+a.a.x,u*(a.a.y-a.b.y)+a.a.y};
  if(abs(u+1)<=eps||abs(u)<=eps)return {2,p};
  return {-eps-1<=u&&u<=eps,p};
}

int main(){
  localFileInput("1.in"),fastCppIO();
  cin>>n;
  for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
  for(int i=1;i<=n;i++){
    e[i]={a[i],a[i%n+1]};
    ans=max(ans,distance(e[i].a,e[i].b));
  }
  for(int i=1;i<=n;i++)
    for(int j=i+1;j<=n;j++){
      line u={a[i],a[j]};
      vector<node> vec,tem;
      vector<int> crs;
      for(int k=1;k<=n;k++){
        auto it=intersection(e[k],u);
        if(it.first==1)vec.push_back(it.second);
        if(it.first==2)crs.push_back(it.second==e[k].a?k:k%n+1);
        if(it.first==3)crs.push_back(k),crs.push_back(k%n+1);
      }
      crs.sort();
      for(int fl,i=0;i<crs.size();i+=2){
        int x=crs[i];
        vector<pair<node,bool>> tem={
          {u.a-u.b,1},{u.b-u.a,1},
          {a[x%n+1]-a[x],0},{a[x==1?n:x-1]-a[x],0},
        };
        tem.sort([](const pair<node,bool> &a,const pair<node,bool> &b){
          return a.first.atan()<b.first.atan();
        });
        fl=false;
        for(int i=0;i<4;i++)fl|=tem[i].first.atan()==tem[(i+1)&3].first.atan();
        if(fl){
          fl=cross(a[x],a[x==1?n:x-1],a[x%n+1])<0;
        }else{
          fl=true;
          for(int i=0;i<4;i++)fl&=tem[i].second^tem[(i+1)&3].second;
        }
        if(fl)vec.push_back(a[x]);
      }
      vec.sort();
      for(int i=0;i+1<vec.size();i+=2)ans=max(ans,distance(vec[i],vec[i+1]));
    }
  cout<<std::fixed<<std::setprecision(10)<<ans<<endl;
}