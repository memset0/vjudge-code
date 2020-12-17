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

typedef unsigned long long ull;

const int N=1e6+10,M=70,T=1e8+9;
int n,m,c,k,l[M],r[M];
ull a,all;
bool tag[T];

struct atom{
	int b,c;
	inline bool operator<(const atom &rhs)const{
		return b<rhs.b;
	}
}b[N];

void akcsp(){
	read(n),read(m),read(c),read(k);
	for(int i=1;i<=n;i++){
		read(a);
		all|=a;
	}
	for(int i=1;i<=m;i++){
		read(b[i].b),read(b[i].c);
	}
	sort(b+1,b+m+1);
	for(int i=0,p=0;i<k;i++){
		l[i]=p;
		while(p<=m&&b[p].b==i)p++;
		r[i]=p;
	}
	for(int i=0;i<k;i++)
		if((all>>i)&1){
			for(int j=l[i];j<r[i];j++){
				tag[b[j].c]=true;
			}
		}
	int cnt=0;
	for(int i=0;i<k;i++){
		bool fl=true;
		for(int j=l[i];j<r[i];j++)
			if(!tag[b[j].c]){
				fl=false;
				break;
			}
		if(fl){
			++cnt;
		}
	}
//	fprintf(stderr,"cnt=%d\n",cnt);

	if(!n&&cnt==64){
		cout<<"18446744073709551616"<<endl;
		return;
	}
	
	ull ans;
	if(cnt==64){
		ans=0;
	}else{
		ans=1ull<<cnt;
	}
	ans-=n;
	print(ans,'\n');
}

}

int main(){
	freopen("zoo.in","r",stdin);
	freopen("zoo.out","w",stdout);
	mem::akcsp();
}