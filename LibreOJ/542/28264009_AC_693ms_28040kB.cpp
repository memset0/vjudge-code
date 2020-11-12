#include<bits/stdc++.h>
// fread
const int S=1<<21; char ibuf[S],*iS,*iT,obuf[S],*oS=obuf,*oT=oS+S-1;
#define flush() (fwrite(obuf,1,oS-obuf,stdout),oS=obuf,void())
#define getchar() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,S,stdin),(iS==iT?EOF:*iS++)):*iS++)
#define putchar(x) (*oS++=(x),oS==oT?flush():void())
struct Flusher_{~Flusher_(){flush();}}flusher_;
// debug tool
#define log(...) (void(0))
// #define log(...) fprintf(stderr,__VA_ARGS__)
#define debug log("\33[2mPassing [%s] in LINE %d\33[0m\n",__FUNCTION__,__LINE__);
#define GG puts("No"),exit(0)
// main
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
const int N=1e6+10;
int T,n,k,tl,tr,a[N],s[N],l[N],r[N];
std::vector<int> vet[N];
void clear(){
	for(int i=1;i<=k;i++)vet[i].clear();
}
void output(){
	printf("Yes\n%d\n",k);
	for(int i=1;i<=k;i++){
		print(vet[i].size(),' ');
		for(int j=0;j<vet[i].size();j++)print(vet[i][j]," \n"[j+1==vet[i].size()]);
	}
	exit(0);
}
void move(int &p,int k,std::vector<int> &vet){
	log("\e[33mMOVE %d %d %d\e[0m\n",p,k,&vet);
	while(k--){
		while(p<=n&&a[p])p++;
		if(p>n)return;
		log("vet.push_back <= %d\n",p);
		vet.push_back(p++);
	}
}
void solve1(){
debug;
	int sum=0,p=1;
	for(int i=1;i<k;i++){
		vet[i].push_back(l[i]);
		sum+=k-2,move(p,k-2,vet[i]);
		while(sum<s[l[i+1]])sum+=k,move(p,k,vet[i]);
		if(sum>s[r[i]])return;
		vet[i].push_back(r[i]);
	}
	vet[k].push_back(l[k]);
	move(p,s[n]-sum,vet[k]);
	vet[k].push_back(r[k]);
	output();
}
void solve2(){
debug;
	int sum=s[l[2]],p=l[2];
	for(int i=1;i<k;i++){
		vet[i].push_back(l[i+1]);
		sum+=k-2,move(p,k-2,vet[i]);
		if(sum>s[r[i]])return;
		vet[i].push_back(r[i]);
	}
	for(int i=1;i<k;i++){
		for(int j=0;j<vet[i].size();j++)a[vet[i][j]]=1;
	}
	vet[k].push_back(l[1]);
	move(p=1,s[n]-sum+s[l[2]],vet[k]);
	vet[k].push_back(r[k]);
	output();
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	read(T),read(n),read(k);
	for(int i=1;i<=n;i++)read(a[i]),a[i]=a[i]%k==0;
	if(n<(long long)k*k||n%k||!a[1]||!a[n])GG;
	for(int i=1;i<=n;i++)if(a[i])l[++tl]=i;
	for(int i=n;i>=1;i--)if(a[i])r[++tr]=i;
	if(tl<k||tr<k||l[k]>=r[k])GG;
	std::reverse(r+1,r+k+1);
	for(int i=l[k]+1;i<r[1];i++)a[i]=0;
	for(int i=1;i<=n;i++)s[i]=s[i-1]+(a[i]^1);
#ifdef local
	log("A | "); for(int i=1;i<=n;i++)log("%d%c",a[i]," \n"[i==n]);
	log("S | "); for(int i=1;i<=n;i++)log("%d%c",s[i]," \n"[i==n]);
	log("L | "); for(int i=1;i<=k;i++)log("%d%c",l[i]," \n"[i==k]);
	log("R | "); for(int i=1;i<=k;i++)log("%d%c",r[i]," \n"[i==k]);
#endif
	solve1(),clear(),solve2(),GG;
}