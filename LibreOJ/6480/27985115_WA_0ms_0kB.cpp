#include<bits/stdc++.h>

namespace mem{ //v2.6.0 => size: 14.94KiB
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
    const int LuckyNumber=0726; // Kanbe Kotori's Birthday
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
    inline void read(container::string &s){
      char c=getc();
      s="";
      while(~c&&!isspace(c))s+=c,c=getc();
    }
    template<const int mod> inline void read(const modint::Z<mod> &x){read(x.x);}
    
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

namespace hash{
	template<const int mod> inline int mul(int a,int b){return (long long)a*b%mod;}
	template<const int mod> inline int sub(int a,int b){return (a-=b)<0&&(a+=mod),a;}
	template<const int mod> inline int add(int a,int b){return (a+=b)>=mod&&(a-=mod),a;}
	template<const int mod=998244353>
	struct singleHash{
		int a;
		inline singleHash(){}
		inline singleHash(int x){a=x;}
		inline singleHash operator+(const singleHash &rhs)const{return {add<mod>(a,rhs.a)};}
		inline singleHash operator-(const singleHash &rhs)const{return {sub<mod>(a,rhs.a)};}
		inline singleHash operator*(const singleHash &rhs)const{return {mul<mod>(a,rhs.a)};}
		inline bool operator<(const singleHash &rhs)const{return a<rhs.a;}
		inline bool operator>(const singleHash &rhs)const{return a>rhs.a;}
		inline bool operator==(const singleHash &rhs)const{return a==rhs.a;}
	};

	template<const int mod0=998244353,const int mod1=1000000007>
	struct doubleHash{
		int a,b;
		inline doubleHash(){}
		inline doubleHash(int x){a=b=x;}
		inline doubleHash(int x,int y){a=x,b=y;}
		inline doubleHash operator+(const doubleHash &rhs)const{return {add<mod0>(a,rhs.a),add<mod1>(b,rhs.b)};}
		inline doubleHash operator-(const doubleHash &rhs)const{return {sub<mod0>(a,rhs.a),sub<mod1>(b,rhs.b)};}
		inline doubleHash operator*(const doubleHash &rhs)const{return {mul<mod0>(a,rhs.a),mul<mod1>(b,rhs.b)};}
		inline bool operator<(const doubleHash &rhs)const{return a<rhs.a||a==rhs.a&&b<rhs.b;}
		inline bool operator>(const doubleHash &rhs)const{return a<rhs.a||a==rhs.a&&b>rhs.b;}
		inline bool operator==(const doubleHash &rhs)const{return a==rhs.a&&b==rhs.b;}
	};

	template<class hash,const size_t N,const int bas=131131>
	struct hashArray{
		hash base,pow[N],hsh[N];
    hashArray(){base=bas;}
		template<class T> inline void init(T *a,int n){
			hsh[0]=0,pow[0]=1;
			for(int i=1;i<=n;i++){
				pow[i]=pow[i-1]*base;
				hsh[i]=hsh[i-1]*base+hash(a[i-1]);
        // printf("%d[%d]%c",hsh[i].a,(hsh[i]-hsh[i-1]*base).a," \n"[i==n]);
			}
		}
		inline hash query(int l,int r){
      // printf("%d %d => %d %d %d => %d\n",l,r,hsh[r+1].a,hsh[l].a,pow[r-l+1].a,(hsh[r+1]-hsh[l]*pow[r-l+1]).a);
			return hsh[r+1]-hsh[l]*pow[r-l+1];
		}
	};
}

const int N=1e5+10,M=11;
int n,m,len,id[M];
char a[M][N];
bool b[M][N];

inline bool cmp(int x,int y){
  for(int i=1;i<=len;i++)if(b[x][i]^b[y][i])return b[x][i]<b[y][i];
  return x<y;
}

void getBorder(char a[N],bool b[N]){
  static hash::hashArray<hash::doubleHash<>,N> h;
  h.init(a,len);
  for(int i=1;i<=len;i++)b[i]=h.query(0,i-1)==h.query(len-i,len-1);
  // for(int i=1;i<=len;i++)putc(b[i]?'1':'0');putc('\n');
}

int main(){
  localFileInput("1.in");
  read(n,m);
  for(int i=1;i<=m;i++){
    read(a[i]),id[i]=i;
    if(i==1)len=strlen(a[1]);
    getBorder(a[i],b[i]);
  }
  sort(id+1,id+m+1,cmp);
  for(int i=1;i<=m;i++){
    for(int j=0;j<len;j++)putc(a[id[i]][j]);
    putc('\n');
  }
}