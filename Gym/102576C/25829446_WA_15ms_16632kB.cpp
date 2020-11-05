#include<bits/stdc++.h>
#define log(...) (void(0))
// #define log(...) fprintf(stderr,__VA_ARGS__)
#define debug log("\33[2mPassing [%s] in LINE %d\33[0m\n",__FUNCTION__,__LINE__);
const int S=1<<21; char ibuf[S],*iS,*iT,obuf[S],*oS=obuf,*oT=oS+S-1;
#define flush() (fwrite(obuf,1,oS-obuf,stdout),oS=obuf,void())
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,S,stdin),(iS==iT?EOF:*iS++)):*iS++)
#define putchar(x) (*oS++=(x),oS==oT?flush():void())
struct Flusher_{~Flusher_(){flush();}}flusher_;
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=2e5+10;
int T,n,u,dec[N],pre[N];
long long d,ans,a[N],mov[N],lst[N];
std::priority_queue<long long,std::vector<long long>,std::greater<long long>> inc[N];
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	for(read(T);T--;){
		read(n),read(d),u=0;
		for(int i=1;i<=n;i++)read(a[i]);
		std::sort(a+1,a+n+1);
		for(int i=1;i<=n;i++){
			if(i==1||a[i]>a[u]+(i-u)*d){
				pre[i]=u,lst[i]=a[i]-(i==1?0:a[u]+(i-u)*d);
				dec[u=i]++,mov[u]=0;
			}else{
				ans+=a[u]+(i-u)*d-a[i];
				inc[u].push(a[u]+(i-u)*d-a[i]+mov[u]);
				a[i]=-1;
			}
			log("insert %d\n",i);
			for(int i=1;i<=n;i++)log("%lld%c",a[i]," \n"[i==n]);
			log(">> %lld\n",ans);
			while(inc[u].size()>dec[u]){
				long long delta=std::min(inc[u].top()-mov[u],lst[u]);
				if(!delta)break;
				mov[u]+=delta,a[u]-=delta,lst[u]-=delta;
				ans-=delta*(inc[u].size()-dec[u]);
				if(mov[u]==inc[u].top()){
					inc[u].pop(),++dec[u];
				}
				if(!lst[u]&&pre[u]){
					if(inc[u].size()>inc[pre[u]].size()){
						inc[u].swap(inc[pre[u]]);
						std::swap(mov[u],mov[pre[u]]);
						while(inc[u].size()){
							inc[pre[u]].push(inc[u].top()-mov[u]+mov[pre[u]]);
							inc[u].pop();
						}
					}
					dec[pre[u]]+=dec[u];
					a[u]=-1,u=pre[u];
				}
			}
			log("merge\n");
			for(int i=1;i<=n;i++)log("%lld%c",a[i]," \n"[i==n]);
			log(">> %lld\n\n",ans);
		}
		print(ans,'\n');
	}
}