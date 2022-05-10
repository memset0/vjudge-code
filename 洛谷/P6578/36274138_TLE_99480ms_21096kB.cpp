#include<bits/stdc++.h>

namespace mem{ //v2.1.2 => size: 14.19KiB
  #define MEM_IO
  #define MEM_MATH
  #define MEM_UTILS
  #define MEM_MODINT
  #define MEM_RANDOM
  #define MEM_STDVAL
  #define MEM_LOGGER
  #define MEM_CONTAINER
  #ifdef memset0
  #else
    #define MEM_FASTIO
  #endif

  #ifdef __SIZEOF_INT128__
    #define MEM_INT128
  #endif

  #define __integer_mapper(func)       \
        func(int)                      \
        func(unsigned int)             \
        func(long long int)            \
        func(unsigned long long int)
  #define __float_mapper(func)         \
        func(float)                    \
        func(double)                   \
        func(long double)
    
    namespace stdval{
  #ifdef MEM_STDVAL
      using i32=int;
      using i64=long long int;
      using u32=unsigned int;
      using u64=unsigned long long int;
      using f32=float;
      using f64=double;
      using f96=long double;
    #ifdef MEM_INT128
      using i128=__int128_t;
      using u128=__uint128_t;
    #endif
  #endif
    }
    
    namespace utils{
  #ifdef MEM_UTILS
      using std::cin;
      using std::tie;
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
  #endif
    }
    
    namespace random{
  #ifdef MEM_RANDOM
      const int LuckyNumber=20040726; // Kanbe Kotori's Birthday
      std::mt19937 rng(LuckyNumber^std::chrono::steady_clock::now().time_since_epoch().count());
      std::mt19937_64 rng64(LuckyNumber^std::chrono::steady_clock::now().time_since_epoch().count());
      
      template<class T> inline T rand(T l,T r){return std::uniform_int_distribution<T>(l,r)(rng);}
      template<class T> inline T rand64(T l,T r){return std::uniform_int_distribution<T>(l,r)(rng);}
  #endif
    }
    
    namespace modint{
  #ifdef MEM_MODINT
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
    
    namespace io{
      template<const int mod> inline void read(modint::Z<mod> &x){read(x.x);}
      template<const int mod> inline void print(modint::Z<mod> x){print(x.x);}
  #endif
    }
    
    namespace math{
  #ifdef MEM_MATH
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
  #endif
    }
    
    namespace container{
  #ifdef MEM_CONTAINER
      using std::pair;
      using std::tuple;
      using std::set;
      using std::unordered_set;
      using std::map;
      using std::unordered_map;
      
      using std::tie;
      using std::make_pair;
      using std::make_tuple;
      
      template<class T> struct vector:std::vector<T>{
        using std::vector<T>::vector;
        vector():std::vector<T>(){}
        vector(const std::vector<T> &plain):std::vector<T>(plain){}
        
        inline void sort(){std::sort(this->begin(),this->end());}
        inline void concat(const vector &rhs){this->insert(this->end(),rhs.begin(),rhs.end());}
        inline bool includes(const T &x) const{return std::find(this->begin(),this->end(),x)!=this->end();}
        template<class Function> inline void forEach(Function func){for(const auto &it:*this)func(it);}
        
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
        
        template<class T> inline string join(const vector<T> &vet) const;
        
        vector<string> split(const string &dim) const{
          if(this->empty())return {};
          char *src=new char[this->length()+1];
          strcpy(src,this->c_str());
          char *tar=new char[dim.length()+1];
          strcpy(tar,dim.c_str());
          vector <string> rsp;
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
    
    #define __to_string(T)                 \
      inline string to_string(const T &x){ \
        return std::to_string(x);          \
      }
      __float_mapper(__to_string)
      __integer_mapper(__to_string)
    #undef __to_string
      
      inline string to_string(const string &s){return s;}
      inline string to_string(const char *s){return string(s);}
      inline string to_string(const std::string &s){return string(s);}
      
      template<const int mod> inline string to_string(const mem::modint::Z<mod> &v){return std::to_string(v.x);}
      
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
  #endif
    }
    
    namespace io{
  #ifdef MEM_IO
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
      inline void print(const container::string &s){
        for(int i=0;i<s.length();i++)putc(s[i]);
      }
      
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
  #endif
    }
    
    namespace logger{
  #ifdef MEM_LOGGER
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
  #endif
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
    using namespace logger;
    using namespace container;
} // namespace mem

using namespace mem::io;
using namespace mem::math;
using namespace mem::utils;
using namespace mem::logger;

const int N=3e5+10,sqn=600,S=sqn+10;
int n,m,a[N],bln[N];

struct atom{
  int l,r,c;
  long long s;
};
inline atom operator+(const atom &a,const atom &b){
  if(a.l==a.c&&b.l==b.c){
    return {a.l+b.l,a.r+b.r,a.c+b.c,a.s+b.s+a.c*b.c};
  }else if(a.l==a.c){
    return {a.l+b.l,b.r,a.c+b.c,a.s+b.s+a.c*b.l};
  }else if(b.l==b.c){
    return {a.l,a.r+b.r,a.c+b.c,a.s+b.s+a.r*b.c};
  }else{
    return {a.l,b.r,a.c+b.c,a.s+b.s+a.r*b.l};
  }
}
inline atom calc(int l,int r,int x){
  atom res{0,0,r-l+1,0};
  while(res.l<res.c&&a[l+res.l]<=x)res.l++;
  while(res.r<res.c&&a[r-res.r]<=x)res.r++;
  int pre=0;
  for(int i=l;i<=r;i++)if(a[i]<=x)res.s+=++pre; else pre=0;
  return res;
}
const atom c[2]={{0,0,1,0},{1,1,1,1}};

int anc[S],siz[S],tag[S];
int find(int x){return anc[x]==x?x:anc[x]=find(anc[x]);}
inline void merge(int a,int b,long long &s){
  a=find(a),b=find(b),s+=siz[a]*siz[b];
  if(siz[a]>siz[b])swap(a,b);
  anc[a]=b,siz[b]+=siz[a];
}
struct block{
  int l,r,n,val[S],pos[S];
  atom pre[S];
  inline int loc(int x){return upper_bound(val+1,val+n+1,x)-val-1;}
  inline void init(){
    n=r-l+1;
    pre[0]={0,0,n,0};
    pre[n]={n,n,n,(long long)n*(n-1)/2};
    for(int i=1;i<n;i++)pre[i].c=n;
    std::vector<std::pair<int,int>> t(n);
    for(int i=0;i<n;i++)t[i]={a[i+l],i};
    sort(t.begin(),t.end());
    for(int i=1;i<=n;i++)val[i]=t[i-1].first,pos[i]=t[i-1].second;
  }
  inline void modify(int k){
    for(int i=1;i<=n;i++)if(pos[i]==k){
      val[i]=a[k+l];
      while(i>1&&val[i]<val[i-1])swap(val[i],val[i-1]),swap(pos[i],pos[i-1]),i--;
      while(i<n&&val[i]>val[i+1])swap(val[i],val[i+1]),swap(pos[i],pos[i+1]),i++;
      return;
    }
  }
  inline void build(){
    for(int i=n-1;i>=1;i--){
      pre[i].l=min(pre[i+1].l,pos[i+1]);
      pre[i].r=min(pre[i+1].r,n-pos[i+1]-1);
    }
    for(int i=0;i<n;i++)anc[i]=i,siz[i]=1,tag[i]=0;
    for(int i=1;i<=n;i++){
      pre[i].s=i?pre[i-1].s+1:1;
      tag[pos[i]]=1;
      if(pos[i]&&tag[pos[i]-1])merge(pos[i]-1,pos[i],pre[i].s);
      if(pos[i]<n-1&&tag[pos[i]+1])merge(pos[i]+1,pos[i],pre[i].s);
    }
  }
}s[N/sqn+5];

int bas,_mem[N*12],*_p=_mem;
struct FC{
  int n,k,*arr,*l,*r;
  FC(){k=-1;}
  inline void loc(int x){
    if(arr[k+2]<=x)k+=2;
    if(arr[k+1]<=x)++k;
  }
  inline void source(int i){memcpy(arr+1,s[i].val+1,n<<2);}
  inline void land(int n){if(n)this->n=n,arr=_p,_p+=n+3,l=_p,_p+=n+1,r=_p,_p+=n+1,arr[n+1]=arr[n+2]=1e9;}
  inline void merge(const FC &a,const FC &b){
    #define pushI {if(!c)arr[++n]=a.arr[i++],l[n]=i-1,r[n]=j-1; else ++i; c=(c+1)&3;}
    #define pushJ {if(!c)arr[++n]=b.arr[j++],l[n]=i-1,r[n]=j-1; else ++j; c=(c+1)&3;}
    int i=1,j=1,c=0;n=0;
    while(i<=a.n&&j<=b.n)if(a.arr[i]<b.arr[j])pushI else pushJ;
    while(i<=a.n)pushI;
    while(j<=b.n)pushJ;
  }
  inline void out(){
    log("n=%d\n",n);
    for(int i=1;i<=n;i++)log<RED>("%d%c",arr[i]," \n"[i==n]);
    for(int i=1;i<=n;i++)log<BLUE>("%d%c",l[i]," \n"[i==n]);
    for(int i=1;i<=n;i++)log<GREEN>("%d%c",r[i]," \n"[i==n]);
  }
}tr[S<<1];
bool use[S<<1];
void locate(int x,int l,int r){
  for(int i=1;i<=bln[n];i++)tr[bas+i].k=l<=i&&i<=r?0:-1;
  for(int i=bas;i>=1;i--)tr[i].k=~tr[i<<1].k||~tr[i<<1|1].k?0:-1;
  tr[1].k=0;
  for(int i=1;i<=bas;i++)if(~tr[i].k){
    tr[i].loc(x);
    if(~tr[i<<1].k)tr[i<<1].k=tr[i].l[tr[i].k];
    if(~tr[i<<1|1].k)tr[i<<1|1].k=tr[i].r[tr[i].k];
  }
  for(int i=l;i<=r;i++)tr[i+bas].loc(x);
  // for(int i=l;i<=r;i++)log("%d%c",tr[i+bas].k," \n"[i==r]);
}

int main(){
#ifdef memset0 
  freopen("1.in","r",stdin);
  freopen("1.out","w",stdout);
#endif
  read(n,m);
  for(int i=1;i<=n;i++)read(a[i]);
  for(int i=1;i<=n;i++)bln[i]=(i-1)/sqn+1;
  for(int i=1;i<=n;i++)s[bln[i]].r=i;
  for(int i=n;i>=1;i--)s[bln[i]].l=i;
  for(int i=1;i<=bln[n];i++)s[i].init(),s[i].build();
  log<RED>("block=%d\n",bln[n]);
  for(bas=1;bas<=bln[n];bas<<=1);--bas;
  for(int i=1;i<=bln[n];i++)tr[bas+i].land(s[i].n);
  for(int i=bas;i>=1;i--)tr[i].land((tr[i<<1].n+tr[i<<1|1].n+3)>>2);
  for(int i=1;i<=bln[n];i++)tr[bas+i].source(i);
  for(int i=bas;i>=1;i--)tr[i].merge(tr[i<<1],tr[i<<1|1]);
  // for(int i=1;i<=bas+n;i++)tr[i].out();
  for(int o,l,r,x,y,i=1;i<=m;i++){
    read(o);
    if(o==1){
      read(x,y);
      a[x]=y;
      s[bln[x]].modify(x-s[bln[x]].l);
      s[bln[x]].build();
      tr[bas+bln[x]].source(bln[x]);
      for(int i=(bas+bln[x])>>1;i>=1;i>>=1)tr[i].merge(tr[i<<1],tr[i<<1|1]);
    }else{
      read(l,r,x);
      atom ans;
      if(bln[l]==bln[r]){
        ans=calc(l,r,x);
      }else{
        ans=calc(l,s[bln[l]].r,x);
        if(bln[l]+1<=bln[r]-1)locate(x,bln[l]+1,bln[r]-1);
        for(int i=bln[l]+1;i<=bln[r]-1;i++)ans=ans+s[i].pre[tr[i+bas].k];
        ans=ans+calc(s[bln[r]].l,r,x);
      }
      print(ans.s,'\n');
    }
    // if(i%10000==0)fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
  }
  fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
}