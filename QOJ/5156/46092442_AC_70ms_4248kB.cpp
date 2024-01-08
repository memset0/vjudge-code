#include<bits/stdc++.h>
// #define JUDGE
using namespace std;
const int N=5e3*3+500+9,p1=1e9+7,p2=1e9+9,base=131131;
int cnt;
#ifdef JUDGE
int n,k=0;
vector<int> a;
void init(int _n){
	n=_n;
	a.resize(n);
	for(int i=0;i<n;i++)a[i]=rand()&1;
}
int right(){
	++cnt;
	k=(k+1)%n;
	return a[k];
}
int flip(){
	++cnt;
	a[k]^=1;
	return a[k];
}
void find(int x){
	cerr<<"FIND "<<x<<endl;
	assert(n==x);
	exit(0);
}
#else
int _;
int right(){
	++cnt;
	cout<<"? right"<<endl;
	cin>>_;
	return _;
}
int flip(){
	++cnt;
	cout<<"? flip"<<endl;
	cin>>_;
	return _;
}
void find(int x){
	cout<<"! "<<x<<endl;
	exit(0);
}
#endif
int power(int a,int b,int p){
	int s=1;
	for(;b;b>>=1,a=(long long)a*a%p)
		if(b&1)s=(long long)s*a%p;
	return s;
}
int pw1[N],pw2[N],ipw1[N],ipw2[N];
struct hasharray{
	vector<int> f,g;
	hasharray(){
		f.push_back(0);
		g.push_back(0);
	}
	void push(int x){
		f.push_back(((long long)f.back()*base+x)%p1);
		g.push_back(((long long)g.back()*base+x)%p2);
	}
	pair<int,int> head(int m){
		return make_pair(f[m],g[m]);
	}
	pair<int,int> tail(int m){
		return make_pair(
			(f.back()-(long long)f[f.size()-m-1]*pw1[m]%p1+p1)%p1,
			(g.back()-(long long)g[g.size()-m-1]*pw2[m]%p2+p2)%p2
		);
	}
}in,out;
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
#ifdef JUDGE
	init(5000);
#else
	int tmp;
	cin>>tmp;
#endif
	pw1[0]=pw2[0]=ipw1[0]=ipw2[0]=1;
	int inv1=power(base,p1-2,p1),inv2=power(base,p2-2,p2);
	for(int i=1;i<N;i++){
		pw1[i]=(long long)pw1[i-1]*base%p1;
		pw2[i]=(long long)pw2[i-1]*base%p2;
		ipw1[i]=(long long)ipw1[i-1]*inv1%p1;
		ipw2[i]=(long long)ipw2[i-1]*inv2%p2;
	}
	for(int len=1;;len++){
		// cerr<<"len = "<<len<<endl;
		int x=right();
		in.push(x);
		if(rand()%3==0){
			x=flip();
		}
		out.push(x);
		if(cnt>=500){
			for(int n=1;n<=5000&&n<=len-100;n++){
				if(in.tail(len-n)==out.head(len-n)){
					find(n);
				}
			}
		}
	}
}