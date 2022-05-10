//没写完 备份下代码
#include<bits/stdc++.h>
namespace mem{ //v2.10.2 => size: 15.87KiB
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
  #define __float_mapper(func)        \
      func(float)                     \
      func(double)                    \
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
    using std::copy;
    using std::fill;
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
    using std::next_permutation;
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
      inline Z(long long t){x=t%mod,x<0&&(x+=mod);}
      
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
  
  namespace container{
    using std::pair;
    using std::tuple;
    using std::set;
    using std::multiset;
    using std::unordered_set;
    using std::unordered_multiset;
    using std::map;
    using std::multimap;
    using std::unordered_map;
    using std::unordered_multimap;
    using std::queue;
    using std::stack;
    using std::priority_queue;
    using std::deque;
    using std::bitset;
    
    using std::tie;
    using std::get;
    using std::make_pair;
    using std::make_tuple;
    
    template<class T> struct vector:std::vector<T>{
      using std::vector<T>::vector;
      using iterator=typename std::vector<T>::iterator;
      using const_iterator=typename std::vector<T>::const_iterator;
      vector():std::vector<T>(){}
      explicit vector(const std::vector<T> &plain):std::vector<T>(plain){}
      
      inline void reverse(){std::reverse(this->begin(),this->end());}
      inline void unique(){this->erase(std::unique(this->begin(),this->end()),this->end());}
      inline void concat(const vector &rhs){this->insert(this->end(),rhs.begin(),rhs.end());}
      inline bool includes(const T &x) const{return std::find(this->begin(),this->end(),x)!=this->end();}
      template<class Function> inline void forEach(Function func){for(const auto &it:*this)func(it);}
      
      inline iterator find(const T &x){return std::find(this->begin(),this->end(),x);}
      inline iterator lower_bound(const T &x){return std::lower_bound(this->begin(),this->end(),x);}
      inline iterator upper_bound(const T &x){return std::upper_bound(this->begin(),this->end(),x);}
      inline const_iterator find(const T &x)const{return std::find(this->begin(),this->end(),x);}
      inline const_iterator lower_bound(const T &x)const{return std::lower_bound(this->begin(),this->end(),x);}
      inline const_iterator upper_bound(const T &x)const{return std::upper_bound(this->begin(),this->end(),x);}

      inline void sort(){std::sort(this->begin(),this->end());}
      template<class Function> inline void sort(Function func){std::sort(this->begin(),this->end(),func);}
      
      inline vector slice(int l,int r) const{
        if(l>r)return {};
        if(r<this->size())return vector(this->begin()+l,this->begin()+r);
        vector rsp(this->begin()+l,this->end());
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
            
      inline string slice(int l,int r) const{
        if(l>r)return {};
        if(r<this->size())return string(this->begin()+l,this->begin()+r);
        string rsp(this->begin()+l,this->end());
        return rsp.resize(r-l),rsp;
      }
      
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
    #ifdef MEM_INT128
      __read(__int128_t)
      __read(__uint128_t)
    #endif
  #undef __read
    
    inline void read(char &x){x=getc();}
    inline void read(char *s){
      char c=getc();
      while(isspace(c))c=getc();
      while(~c&&!isspace(c))*s++=c,c=getc();
      *s++='\0';
    }
    inline void read(container::string &s){
      char c=getc();
      while(isspace(c))c=getc();
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
    #ifdef MEM_INT128
      __print(__int128_t)
      __print(__uint128_t)
    #endif
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
  #ifdef memset0
      if(~color){
        fprintf(stderr,"\033[%dm",30+color);
        fprintf(stderr,formatter,args...);
        fprintf(stderr,"\033[0m");
      }else{
        fprintf(stderr,formatter,args...);
      }
  #endif
    }
    template<const ConsoleColor color=NOPE,class... Args> inline void logln(const char *formatter,Args... args){
  #ifdef memset0
      if(~color){
        fprintf(stderr,"\033[%dm",30+color);
        fprintf(stderr,formatter,args...);
        fprintf(stderr,"\033[0m\n");
      }else{
        fprintf(stderr,formatter,args...);
        fprintf(stderr,"\n");
      }
  #endif
    }
    template<class T> inline void logs(const T &x){
  #ifdef memset0
      fprintf(stderr,container::to_string(x).c_str());
  #endif
    }
    template<class T,class... Args> inline void logs(const T &x,Args... args){
      logs(x),logs(args...);
    }
    template<class... Args> inline void logsln(Args... args){
      logs(args...);
  #ifdef memset0
      fprintf(stderr,"\n");
  #endif
    }
  }
  
  namespace fileio{
    inline void file_input(const char *dir){freopen(dir,"r",stdin);}
    inline void file_output(const char *dir){freopen(dir,"w",stdout);}
    inline void file_input(const std::string &dir){file_input(dir.c_str());}
    inline void file_output(const std::string &dir){file_output(dir.c_str());}
    inline void file_input(const container::string &dir){file_input(dir.c_str());}
    inline void file_output(const container::string &dir){file_output(dir.c_str());}

    template<class T> inline void file_io(const T name){
      using namespace container;
      file_input(name+".in"_s);
      file_output(name+".out"_s);
    }

    inline void fast_cpp_io(){
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

template<const int MAXV,class flow_t,class cost_t,const int SCALE=8>
struct MCMF{
  struct edge_t{
    int to,rev;
    flow_t cap,resCap;
    cost_t cost;
    edge_t(int to,flow_t cap,cost_t cost,int rev):to(to),cap(cap),resCap(cap),cost(cost),rev(rev){}
  };
  int top,cnt[MAXV*2],h[MAXV],stk[MAXV];
  flow_t FLOW_EPS,maxFlow,ex[MAXV];
  cost_t COST_INF,COST_EPS,bnd,minCost,negCost,phi[MAXV];
  vector<int> hs[MAXV*2];
  vector<edge_t> adj[MAXV];
  typename vector<edge_t>::iterator cur[MAXV];
  inline void addEdge(int v,int w,flow_t flow,cost_t cost){
    // cerr<<v<<" "<<w<<" "<<flow<<" "<<cost<<endl;
    if(v==w)return negCost+=cost<0?flow*cost:0,void();
    adj[v].emplace_back(w,flow,cost,int(adj[w].size()));
    adj[w].emplace_back(v,0,-cost,int(adj[v].size())-1);
  }
  inline void clear(int V=MAXV){
    negCost=0;
    for(int i=0;i<V;i++)adj[i].clear();
  }
  flow_t getMaxFlow(int V,int s,int t){
    auto push=[&](int v,edge_t &e,flow_t df){
      if(abs(ex[e.to])<=FLOW_EPS&&df>FLOW_EPS)hs[h[e.to]].push_back(e.to);
      e.resCap-=df,adj[e.to][e.rev].resCap+=df,ex[v]-=df,ex[e.to]+=df;
    };
    if(s==t)return maxFlow=0;
    fill(h,h+V,0),h[s]=V;
    fill(ex,ex+V,0),ex[t]=1;
    fill(cnt,cnt+V*2,0),cnt[0]=V-1;
    for(int v=0;v<V;v++)cur[v]=adj[v].begin();
    for(int i=0;i<V*2;i++)hs[i].clear();
    for(auto &&e:adj[s])push(s,e,e.resCap);
    if(!hs[0].empty())
      for(int hi=0;hi>=0;){
        int v=hs[hi].back();
        hs[hi].pop_back();
        while(ex[v]>FLOW_EPS){
          if(cur[v]==adj[v].end()){
            h[v]=INT_MAX;
            for(auto e=adj[v].begin();e!=adj[v].end();e++)
              if(e->resCap>FLOW_EPS&&h[v]>h[e->to]+1)
                h[v]=h[e->to]+1,cur[v]=e;
            cnt[h[v]]++;
            if(--cnt[hi]==0&&hi<V)
              for(int i=0;i<V;i++)
                if(hi<h[i]&&h[i]<V)
                  cnt[h[i]]--,h[i]=V+1;
            hi=h[v];
          }else if(cur[v]->resCap>FLOW_EPS&&h[v]==h[cur[v]->to]+1){
            push(v,*cur[v],min(ex[v],cur[v]->resCap));
          }else cur[v]++;
        }
        while(hi>=0&&hs[hi].empty())hi--;
      }
    return maxFlow=-ex[s];
  }
  pair<flow_t,cost_t> getMaxFlowMinCost(int V,int s=-1,int t=-1){
    auto costP=[&](int v,const edge_t &e){return e.cost+phi[v]-phi[e.to];};
    auto push=[&](int v,edge_t &e,flow_t df,bool pushToStack){
      if(e.resCap<df)df=e.resCap;
      e.resCap-=df,adj[e.to][e.rev].resCap+=df,ex[v]-=df,ex[e.to]+=df;
      if(pushToStack&&FLOW_EPS<ex[e.to]&&ex[e.to]<=df+FLOW_EPS)stk[top++]=e.to;
    };
    auto relabel=[&](int v,cost_t delta){phi[v]-=delta+bnd;};
    auto lookAhead=[&](int v){
      if(abs(ex[v])>FLOW_EPS)return false;
      cost_t delta=COST_INF;
      for(auto &&e:adj[v]){
        if(e.resCap<=FLOW_EPS)continue;
        cost_t c=costP(v,e);
        if(c<-COST_EPS)return false;
        else delta=min(delta,c);
      }
      relabel(v,delta);
      return true;
    };
    auto discharge=[&](int v){
      cost_t delta=COST_INF;
      for(int i=0;i<int(adj[v].size());i++){
        edge_t &e=adj[v][i];
        if(e.resCap<=FLOW_EPS)continue;
        if(costP(v,e)<-COST_EPS){
          if(lookAhead(e.to)){i--;continue;}
          push(v,e,ex[v],true);
          if(abs(ex[v])<=FLOW_EPS)return;
        }else delta=min(delta,costP(v,e));
      }
      relabel(v,delta);
      stk[top++]=v;
    };
    minCost=0,bnd=0;
    cost_t mul=2<<std::__lg(V);
    for(int v=0;v<V;v++)
      for(auto &&e:adj[v])
        minCost+=e.cost*e.resCap,e.cost*=mul,bnd=max(bnd,e.cost);
    maxFlow=(s==-1||t==-1)?0:getMaxFlow(V,s,t);
    fill(ex,ex+V,0),fill(phi,phi+V,0);
    while(bnd>1){
      top=0,bnd=max(bnd/SCALE,cost_t(1));
      for(int v=0;v<V;v++)for(auto &&e:adj[v])if(costP(v,e)<-COST_EPS&&e.resCap>FLOW_EPS)push(v,e,e.resCap,false);
      for(int v=0;v<V;v++)if(ex[v]>FLOW_EPS)stk[top++]=v;
      while(top>0)discharge(stk[--top]);
    }
    for(int v=0;v<V;v++)
      for(auto &&e:adj[v])
        e.cost/=mul,minCost-=e.cost*e.resCap;
    return make_pair(maxFlow,(minCost/=2)+=negCost);
  }
  MCMF(flow_t FLOW_EPS,cost_t COST_INF,cost_t COST_EPS):FLOW_EPS(FLOW_EPS),COST_INF(COST_INF),COST_EPS(COST_EPS){}
};

const int N=110,V=410;
const long long inf=1e14;
int n,s,e,id,a[N][N],c[N][N],k[N],dl[N],dr[N],p[N][2][2],delta[V];
MCMF<V,long long,long long> mcmf(0,(long long)1e18,0);

inline void add(int u,int v,int x,int y,int w){
  cerr<<"add (bordered) "<<u<<" "<<v<<" "<<x<<" "<<y<<" "<<w<<endl;
  delta[u]-=x,delta[v]+=x;
  mcmf.addEdge(u,v,y-x,w);
}

long long solve(){
  int S=++id,E=++id;
  long long ned=0;
  for(int i=1;i<=id;i++){
    if(delta[i]>0)mcmf.addEdge(S,i,delta[i],0),ned+=delta[i];
    if(delta[i]<0)mcmf.addEdge(i,E,-delta[i],0);
  }
  pair<long long,long long> res=mcmf.getMaxFlowMinCost(id+1,1,id);
  cerr<<"ned="<<ned<<endl;
  cerr<<"res="<<res.first<<endl;
  cerr<<"cst="<<res.second<<endl;
  // assert(ned==res.first);
  return res.second;
}

int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  read(n);
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
      read(a[i][j]);
    }
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
      read(c[i][j]);
    }
  s=++id,e=++id;
  for(int i=1;i<=n;i++){
    for(int a=0;a<2;a++)
      for(int b=0;b<2;b++)
        p[i][a][b]=++id;
  }
  for(int i=1;i<=n;i++){
    read(dl[i],dr[i],k[i]);
    for(int j=0;j<2;j++){
      add(p[i][j][0],p[i][j][1],dl[i],dr[i],0);
    }
    add(p[i][1][1],p[i][0][0],0,k[i]<<1,0);
    add(p[i][0][0],e,k[i],k[i],0);
  }
  long long ans=0;
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
      if(c[i][j]==-1){
        if(a[i][j])add(p[i][0][1],p[j][1][0],1,1,0);
      }else if(a[i][j]){
        add(p[i][0][1],p[j][1][0],0,1,-c[i][j]);
        ans+=c[i][j];
      }else{
        add(p[i][0][1],p[j][1][0],0,1,c[i][j]);
      }
    }
  ans+=solve();
  println(ans);
}