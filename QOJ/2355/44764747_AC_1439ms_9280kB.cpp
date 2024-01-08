#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using lf=long double;
const int N=2e8+9,M=1e4+9,D=1e3;
// const int N=101;
// const int V=31831024+10;
const lf pi=acos(-1);
int T,nl[M],nr[M],pos,ans[M],qry[M],sum[N/D+9];
vector<int> q[N/D+9];
int ansx,ansy;
lf ansf;
bool found;
inline lf myabs(lf x){return x<0?-x:x;}
struct frac{
	int x,y;
	bool ge;
	frac(){}
	frac(int _x,int _y){
		x=_x;
		y=_y;
		int g=__gcd(x,y);
		x/=g;
		y/=g;
		ge=x>=y*pi;
		// cerr<<"! "<<x<<" "<<y<<endl;
	}
}res,cur;
inline void pushans(int x,int y){
	cur=frac(x,y);
	// fprintf(stderr,"res:%d,%d cur:%d,%d\n",res.x,res.y,cur.x,cur.y);
	// cerr<<"! pushans "<<x<<" "<<y<<endl;
	if(!found){
		found=true;
		res=cur;
	}else{
		if(cur.ge&&res.ge&&(ll)cur.x*res.y<(ll)cur.y*res.x){res=cur;}
		if(cur.ge&&!res.ge&&((ll)cur.x*res.y+(ll)cur.y*res.x)<2*pi*res.y*cur.y){res=cur;}
		if(!cur.ge&&res.ge&&((ll)cur.x*res.y+(ll)cur.y*res.x)>2*pi*res.y*cur.y){res=cur;}
		if(!cur.ge&&!res.ge&&(ll)cur.x*res.y>(ll)cur.y*res.x){res=cur;}
	}
}
int main(){
#ifdef memset0
	freopen("H.in","r",stdin);
#endif
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	for(int t=1;t<=T;t++){
		cin>>nl[t]>>nr[t];
		// cerr<<"! "<<l<<" "<<r<<endl;
		for(int n=nl[t];n<=nr[t];n++){
			q[n/D].push_back(pos);
			qry[pos++]=n;
			// pushans(n,solve(n)<<1);
		}
	}
	for(int i=1,i2=1;i2<N;i++,i2+=(i<<1)-1){
		// assert(i2==i*i);
		int M=N-i*i;
		int j=i+1;
		if((i+j)%2==0)++j;
		int j2=j*j;
		for(;j2<M;j+=2,j2+=(j<<2)-4){
			// assert(j2==j*j);
			if(__gcd(i,j)==1){
				// cerr<<j*j-i*i<<" "<<2*i*j<<" "<<i*i+j*j<<endl;
				int x=i2+j2;
				sum[x/D+1]++;
				for(int i:q[x/D]){
					if(x<=qry[i])ans[i]++;
				}
			}
		}
	}
	for(int i=1;i<=N/D;i++)sum[i]+=sum[i-1];
	pos=0;
	for(int t=1;t<=T;t++){
		found=false;
		for(int n=nl[t];n<=nr[t];n++){
			int s=sum[n/D]+ans[pos++];
			// fprintf(stderr,"solve %d -> %d\n",n,s);
			pushans(n,s<<1);
		}
		cout<<res.x<<" / "<<res.y<<endl;
	}
	// for(int x:vec)cerr<<x<<endl;
}