#include<bits/stdc++.h>
using namespace std;
template<class T> inline void read(T &x){
	x=0; char c=getchar(); bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
namespace mem{
	template<const int mod> inline int dec(int a,int b){return (a-=b)<0&&(a+=mod),a;}
	template<const int mod> inline int inc(int a,int b){return (a+=b)>=mod&&(a-=mod),a;}
	const int N=(1<<20)+9,P1=1e9+7,P2=998244353;
	int T,n,pre[N][27],cnt[N],cur[30];
	long long ans;
	char s[N];
	struct hash_t{
		int x,y;
		inline bool operator==(const hash_t &rhs)const{return x==rhs.x&&y==rhs.y;}
		inline hash_t operator-(const hash_t &rhs)const{return (hash_t){dec<P1>(x,rhs.x),dec<P2>(y,rhs.y)};}
		inline hash_t operator+(const hash_t &rhs)const{return (hash_t){inc<P1>(x,rhs.x),inc<P2>(y,rhs.y)};}
		inline hash_t operator*(const hash_t &rhs)const{return (hash_t){(long long)x*rhs.x%P1,(long long)y*rhs.y%P2};}
	}h[N],pw[N];
	const hash_t bs=(hash_t){131131,131131};
	inline hash_t query(int l,int r){
		return h[r]-h[l-1]*pw[r-l];
	}
	void aknoip(){
		pw[0]=bs;
		for(int i=1;i<N;i++)pw[i]=pw[i-1]*bs;
		scanf("%d",&T);
		while(T--){
			scanf("%s",s+1);
			n=strlen(s+1);
//			fprintf(stderr,"n=%d\n",n);
			for(int i=1;i<=n;i++){
				h[i]=h[i-1]*bs+(hash_t){s[i],s[i]};
//				printf("> %d %d %d\n",(int)(s[i]-'a'),h[i].x,h[i].y);
			}
//			for(int l=1;l<=n;l++){
//				for(int r=l;r<=n;r++){
//					hash_t u=(hash_t){0,0};
//					for(int i=l;i<=r;i++)u=u*bs+(hash_t){s[i],s[i]};
//					printf("> %d %d :: %d %d %d %d\n",l,r,u.x,u.y,query(l,r).x,query(l,r).y);
//				}
//			}
			memset(cur,0,26<<2);
			cnt[n+1]=0;
			for(int i=n;i>=1;i--){
				char c=s[i]-'a';
				if(cur[c]){
					cnt[i]=cnt[i+1]-1;
					cur[c]=0;
				}else{
					cnt[i]=cnt[i+1]+1;
					cur[c]=1;
				}
			}
			int lst=0;
			memset(cur,0,26<<2);
			for(int i=1;i<=n;i++){
				for(int j=0;j<=26;j++)pre[i][j]=pre[i-1][j];
				char c=s[i]-'a';
				if(cur[c]){
					lst--;
					cur[c]=0;
				}else{
					lst++;
					cur[c]=1;
				}
				pre[i][lst]++;
			}
			for(int i=1;i<=n;i++){
				for(int j=1;j<=26;j++)pre[i][j]+=pre[i][j-1];
			}
			ans=0;
			for(int i=2;i<n;i++){
				for(int l=1,r=i;r<n;l+=i,r+=i)
					if(h[i]==query(l,r)){
//						printf("%d %d >> %d | %d %d\n",i,j,pre[i-1][cnt[i*j+1]],query(1,i).x,query((j-1)*i+1,i*j).x);
						ans+=pre[i-1][cnt[r+1]];
					}else{
//						printf("%d %d >> %d | %d %d [%d %d] Failed\n",i,j,pre[i-1][cnt[i*j+1]],query(1,i).x,query((j-1)*i+1,i*j).x,(j-1)*i+1,i*j);
						break;
					}
			}
			printf("%lld\n",ans);
		}
//		fprintf(stderr,"%.2lf\n",clock()/(double)CLOCKS_PER_SEC);
	}
}
int main(){
#ifdef memset0
	freopen("string1.in","r",stdin);
	freopen("string1.out","w",stdout);
#else
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
#endif
	return mem::aknoip(),0;
}