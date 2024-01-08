#include<bits/stdc++.h>
using namespace std;
const int N=12;
int n,ans,a[N][N],w[N][N];
bool ok[N][N];
int dp[1<<24],cnt[1<<12];
string str;
int u[N];
void to(unsigned s){
	int t=0,k=0;
	for(int i=0;i<(n<<1);i++)
		if((s>>i)&1){
			++t;
		}else{
			u[k++]=n-t;
		}
	// cerr<<s<<" >> ";for(int i=0;i<n;i++)cerr<<u[i]<<" \n"[i+1==n];
}
unsigned from(){
	int t=0,k=0;
	unsigned s=0;
	for(int i=0;i<n;i++){
		while(t<(n-u[i])){
			t++;
			s|=1<<(k++);
		}
		k++;
	}
	while(t<n){
		t++;
		s|=1<<(k++);
	}
	// cerr<<s<<" << ";for(int i=0;i<n;i++)cerr<<u[i]<<" \n"[i+1==n];
	return s;
}
inline void update(int v,int w){
	if(w>dp[v])dp[v]=w;
}
unsigned flip(unsigned x,int i){
	// assert(((x>>(n-u[i]+i-1))&1)==1);
	// assert(((x>>(n-u[i]+i))&1)==0);
	unsigned y=x;
	y^=1<<(n-u[i]+i);
	y^=1<<(n-u[i]+i-1);
	return y;
}
int main(){
#ifdef memset0
	freopen("G.in","r",stdin);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin>>n,getline(cin,str);
	for(int i=0;i<n;i++){
		getline(cin,str);
		for(int j=0;j<n;j++){
			if(str[j]=='.')a[i][j]=-1;
			if(str[j]=='B')a[i][j]=0;
			if(str[j]=='W')a[i][j]=1;
		}
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			cin>>w[i][j];
		}
	for(int l=0,r=n-1;l<r;l++,r--){
		for(int j=0;j<n;j++){
			swap(a[l][j],a[r][j]);
			swap(w[l][j],w[r][j]);
		}
	}
	for(int i=1;i<(1<<12);i++)cnt[i]=cnt[i>>1]+(i&1);
	for(unsigned x=0;x<(1<<(n<<1));x++)
		if(cnt[x>>12]+cnt[x^(x>>12<<12)]==n){
			to(x);
			ans=max(ans,dp[x]);
			// for(int i=0;i<n;i++)cerr<<u[i]<<" ";cerr<<":: "<<dp[x]<<" "<<x<<endl;
			for(int i=0;i<n;i++){
				if(i&&u[i]==u[i-1])continue;
				if(u[i]==n)continue;
				for(int j=i+1;j<n;j++){
					if(u[j]==u[j-1])continue;
					if(u[j]==u[i])continue;
					if(a[i][u[i]]+a[j][u[j]]==1){
						// cerr<<">>> "<<i<<" "<<y1<<" : "<<a[i][y1]<<" "<<w[i][y1]<<endl;
						// cerr<<"<<< "<<j<<" "<<y2<<" : "<<a[j][y2]<<" "<<w[j][y2]<<endl;
						int cst=min(w[i][u[i]],w[j][u[j]]);
						// for(int i=n-1;i>=0;i--)v[i-1]=max(v[i-1],v[i]);
						// for(int i=0;i<n;i++)cerr<<v[i]<<" ";cerr<<">> "<<dp[x]+min(w[i][y1],w[j][y2])<<" "<<from(v)<<endl;
						update(flip(flip(x,j),i),dp[x]+cst);
					}
				}
			}
			for(int i=0;i<n;i++){
				if(i&&u[i]==u[i-1])continue;
				if(u[i]==n)continue;
				assert(((x>>(n-u[i]+i-1))&1)==1);
				assert(((x>>(n-u[i]+i))&1)==0);
				update(flip(x,i),dp[x]);
			}
		}
	ans=-2*ans;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			ans+=w[i][j];
		}
	cout<<ans<<endl;
}