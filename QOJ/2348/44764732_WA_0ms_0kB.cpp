#include<bits/stdc++.h>
using namespace std;
const int B=1e3,N=600;
struct BN{
	vector<int>a;
	bool operator<=(const BN&y)const{
		if(a.size()!=y.a.size())return a.size()<y.a.size();
		if(!a.size())return 1;
		for(int i=a.size()-1;i>=0;--i)if(a[i]!=y.a[i])return a[i]<y.a[i];
		return 1;
	}
	BN operator+(const BN&y)const{
		BN ret;
		ret.a.resize(max(a.size(),y.a.size()));
		int w=0;
		for(int i=0;i<ret.a.size();++i){
			ret.a[i]=w;
			if(i<a.size())ret.a[i]+=a[i];
			if(i<y.a.size())ret.a[i]+=y.a[i];
			if(ret.a[i]>=B)ret.a[i]-=B,w=1;
			else w=0;
			if(w&&i+1==ret.a.size())ret.a.push_back(0);
		}
		return ret;
	}
	BN operator-(const BN&y)const{
		BN ret;
		ret.a=a;
		for(int i=0;i<y.a.size();++i)ret.a[i]=a[i]-y.a[i];
		for(int i=0;i<y.a.size();++i)if(ret.a[i]<0)ret.a[i]+=B,--ret.a[i+1];
		while(ret.a.size()&&!ret.a[ret.a.size()-1])ret.a.pop_back();
		return ret;
	}
	/*BN operator*(const BN&y)const{
		BN ret;
		ret.a.resize(a.size()+y.a.size()+1);
		for(int i=0;i<a.size();++i)for(int j=0;j<y.a.size();++j){
			ret.a[i+j]+=a[i]*y.a[j];
		}
		int w=0;
		for(int i=0;i<ret.a.size();++i){
			ret.a[i]+=i;
			w=ret.a[i]/B,ret.a[i]%=B;
			if(w&&i+1==ret.a.size())ret.a.push_back(0);
		}
		return ret;
	}*/
	BN operator*(const int&y)const{
		BN ret;
		ret.a=a;
		for(int i=0;i<a.size();++i)ret.a[i]*=y;
		int w=0;
		for(int i=0;i<ret.a.size();++i){
			ret.a[i]+=w;
			w=ret.a[i]/B,ret.a[i]%=B;
			if(w&&i+1==ret.a.size())ret.a.push_back(0);
		}
		return ret;
	}
	void prt(){
		for(int i=(int)a.size()-1;i>=0;--i)cout<<a[i];
		puts("");
	}
}C[N+10][N+10],B0;
int n,m,k;
char s[15],prt[N+10],a[N+10];
BN Div(BN x,int mm,int&t){
	t=0;
	BN ret;
	ret.a.resize(x.a.size());
	for(int i=(int)x.a.size()-1;i>=0;--i){
		t=t*B+x.a[i];
		ret.a[i]=t/mm,t%=mm;
	}
	while(ret.a.size()&&!ret.a[ret.a.size()-1])ret.a.pop_back();
	return ret;
}
BN Calc(int x,int y){
	if(x<0||y<0)return B0;
	//cout<<"CALC "<<x<<" "<<y<<"\n";
	//cout<<"=",C[x+y][x].prt();
	return C[x+y][x];
}
BN Calc_b(int x,int y){
	if(x>n||y>n||y>x)return B0;
	//cout<<"CALCB "<<x<<" "<<y<<"\n";
	return Calc(n-x,n-y)-Calc(n-y+1,n-x-1);
}
BN Calc_p(int x,int y){
	if(x>n||y>n)return B0;
	return Calc(n-x,n-y);
}
BN p2i(char*x){
	BN ret=B0;
	int nx=0,ny=0;
	for(int i=0;i<(n<<1);++i){
		if(x[i]=='R')++nx;
		else{
			ret=ret+Calc_p(nx+1,ny);
			++ny;
		}
	}
	return ret;
}
BN b2i(char*x,int y){
	BN ret=B0;
	int nx=0,ny=0;
	for(int i=0;i<(n<<1);++i){
		if(x[i]=='(')++nx;
		else{
			ret=ret+Calc_b(nx+1,ny);
			++ny;
		}
	}
	//cout<<"RET=";ret.prt();
	return ret*(n+1)+(BN){vector<int>{y}};
}
void i2p(BN x){
	//cout<<"TO p";x.prt();
	int nx=0,ny=0;
	for(int i=0;i<(n<<1);++i){
		BN tmp=Calc_p(nx+1,ny);
		if(ny<n&&tmp<=x){
			prt[i]='U';
			++ny;
			x=x-tmp;
		}else{
			prt[i]='R';
			++nx;
		}
	}
	printf("%s",prt);
}
void i2b(BN x){
	int nx=0,ny=0;
	int t=0;
	x=Div(x,n+1,t);
	for(int i=0;i<(n<<1);++i){
		//cout<<"i="<<i<<"\n";
		//cout<<"nx="<<nx<<" ny="<<ny<<"\n";
		BN tmp=Calc_b(nx+1,ny);
		//cout<<"TMP=";tmp.prt();
		if(ny<nx&&tmp<=x){
			prt[i]=')';
			++ny;
			x=x-tmp;
		}else{
			prt[i]='(';
			++nx;
		}
	}
	printf("%s\n%d",prt,t);
}
int main(){
	freopen("A.in","r",stdin);
	scanf("%s",s),scanf("%d",&n),m=(n<<1)+5;
	C[0][0]=(BN){vector<int>{1}};
	for(int i=1;i<=m;++i){
		C[i][0]=(BN){vector<int>{1}};
		for(int j=1;j<=i;++j)C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	scanf("%s",a);
	if(s[0]=='b'){
		scanf("%d",&k);
		i2p(b2i(a,k));
	}else i2b(p2i(a));
	return 0;
}
/*
path
2
RRUU

brackets
3
(()())
3
*/