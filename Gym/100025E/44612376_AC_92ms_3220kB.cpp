#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9,bx=131131,by=113311,px=998244353,py=1e9+7;
template<const int p> constexpr int sub(int x,int y){return x-=y,x<0?x+p:x;}
template<const int p> constexpr int add(int x,int y){return x+=y,x>=p?x-p:x;}
template<const int p> constexpr int mul(int x,int y){return (long long)x*y%p;}
int n,pre[N],nxt[N];
char s[N];
struct h{
	int x,y;
	friend inline h operator+(const h &u,const h &v){return {add<px>(u.x,v.x),add<py>(u.y,v.y)};}
	friend inline h operator-(const h &u,const h &v){return {sub<px>(u.x,v.x),sub<py>(u.y,v.y)};}
	friend inline h operator*(const h &u,const h &v){return {mul<px>(u.x,v.x),mul<py>(u.y,v.y)};}
	friend inline bool operator==(const h &u,const h &v){return u.x==v.x&&u.y==v.y;}
	friend inline bool operator!=(const h &u,const h &v){return u.x!=v.x||u.y!=v.y;}
}stp={bx,by},pw[N];
struct str_h{
	h hsh[N];
	inline void init(char *s){
		hsh[0]={1,1};
		for(int i=1;i<=n;i++)hsh[i]=hsh[i-1]*stp+h{(int)s[i],(int)s[i]};
	}
	inline h query(int l,int r){
		return hsh[r]-hsh[l-1]*pw[r-l+1];
	}
}pos,rev;
inline h query_pos(int l,int r){return pos.query(l,r);}
inline h query_rev(int l,int r){return rev.query(n-r+1,n-l+1);}
int main(){
#ifdef memset0
	freopen("E.in","r",stdin);
#else
	freopen("palindromes.in","r",stdin);
	freopen("palindromes.out","w",stdout);
#endif
	pw[0]={1,1};
	for(int i=1;i<N;i++)pw[i]=pw[i-1]*stp;
	scanf("%s",s+1),n=strlen(s+1);
	pos.init(s),reverse(s+1,s+n+1);
	rev.init(s),reverse(s+1,s+n+1);
	for(int lst=0,i=1;i<=n;i++){
		pre[i]=lst;
		if(s[i]=='?')lst=i;
	}
	for(int lst=n+1,i=n;i>=1;i--){
		nxt[i]=lst;
		if(s[i]=='?')lst=i;
	}
	double ans=0;
	s[0]='$';
	s[n+1]='^';
	// for(int i=1;i<=n;i++)cerr<<pre[i]<<" \n"[i==n];
	// for(int i=1;i<=n;i++)cerr<<nxt[i]<<" \n"[i==n];
	for(int i=1;i<=n;i++){
		double cur=1,sum=0;
		int l=pre[i],r=nxt[i];
		int lu=i,ru=i;
		for(int k=0;k<20;k++){
			int ln=lu-l-1,rn=r-ru-1,un=min(ln,rn);
			// fprintf(stderr,"i=%d lu=%d ru=%d ln=%d rn=%d un=%d\n",i,lu,ru,ln,rn,un);
			if(un&&query_rev(lu-un,lu-1)!=query_pos(ru+1,ru+un)){
				int ql=1,qr=un,qmid,qans=0;
				while(ql<=qr){
					qmid=(ql+qr)>>1;
					if(query_rev(lu-qmid,lu-1)==query_pos(ru+1,ru+qmid)){
						qans=qmid;
						ql=qmid+1;
					}else{
						qr=qmid-1;
					}
				}
				ans+=cur*qans;
				break;
			}
			sum+=cur*un;
			lu-=un+1;
			ru+=un+1;
			cur/=26;
			if(lu==0||ru==n+1)break;
			if(l==lu)l=pre[l];
			if(r==ru)r=nxt[r];
			sum+=cur;
		}
		// fprintf(stderr,"%.12lf\n",sum*2+1);
		ans+=sum;
	}
	ans=(ans/n)*2+1;
	printf("%.12lf\n",ans);
}