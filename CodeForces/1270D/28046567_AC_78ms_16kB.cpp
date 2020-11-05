#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;register char c=getchar();register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
template<class T> inline void print(T a,int l,int r){for(int i=l;i<=r;i++)print(a[i]," \n"[i==r]);}
const int N=510;
int T,n,k,t,m,q[N];
inline std::pair<int,int> QY(){
	int pos,val;
	putchar('?'),putchar(' ');
	for(int i=1;i<=k;i++)print(q[i]," \n"[i==k]);
	fflush(stdout);
	read(pos),read(val);
	return std::make_pair(pos,val);
}
int main(){
#ifdef memset0
	// freopen("1.in","r",stdin);
#endif
	read(n),read(k);
	for(int i=1;i<=k;i++)q[i]=i;
	auto it=QY();
	int f=it.first,fw=it.second;
	q[f]=k+1;
	it=QY();
	int g=it.first,gw=it.second;
	if(fw>gw)std::swap(f,g);
	for(int i=1;i<=k+1;i++)if(i!=f&&i!=g)q[++t]=i;
	q[++t]=g;
	// for(int i=1;i<=t;i++)printf("%d%c",q[i]," \n"[i==k]);
	// printf(">> %d %d\n",f,g);
	for(int p,i=1;i<k;i++){
		p=q[i],q[i]=f;
		int h=QY().first;
		assert(h==f||h==g);
		if(h==g)++m;
		// printf("%d >> %d\n",p,h);
		q[i]=p;
	}
	printf("! %d\n",++m);
}