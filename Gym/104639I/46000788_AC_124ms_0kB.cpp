#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define debug(x) cerr<<#x<<": "<<x<<endl
using namespace std;
using ll=long long;
using lf=long double;
const int N=1e5+9;
const int mod=998244353;
int n,c;
int f[2][2][2][63],g[2][2][2][63];
inline int dec(int x,int y){return x-=y,x<0?x+mod:x;}
inline int add(int x,int y){return x+=y,x>=mod?x-mod:x;}
inline void upd(int &x,int y){x+=y; if(x>=mod)x-=mod;}
int getc(){
	// return 0;
	int c=getchar();
	while(!isdigit(c)&&!islower(c)&&!isupper(c)&&c!='?'){
		c=getchar();
	}
	if(c=='?')return 0; //0
	if(islower(c))return 1+c-'a'; //1..26
	if(isupper(c))return 27+c-'A'; //27..52
	if(isdigit(c))return 53+c-'0'; //53..62
	return -1;
}
inline void push(int c){
	if(c>=53){
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				upd(g[i][j][1][c],add(f[i][j][0][c],f[i][j][1][c]));
	}else if(c>=27){
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				upd(g[i][1][j][c],add(f[i][0][j][c],f[i][1][j][c]));
	}else{
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				upd(g[1][i][j][c],add(f[0][i][j][c],f[1][i][j][c]));
	}
}
int main(){
#ifdef memset0
	freopen("I.in","r",stdin);
#endif
	scanf("%d",&n);
	for(int c=1;c<63;c++)
		f[0][0][0][c]=1;
	while(n--){
		int c=getc();
		memset(g,0,sizeof(g));
		if(c>=27){
			push(c);
		}else if(c>=1){
			push(c);
			push(c+26);
		}else{
			for(int c=1;c<63;c++)
				push(c);
		}
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				for(int k=0;k<2;k++){
					int s=0;
					for(int x=1;x<63;x++){
						upd(s,g[i][j][k][x]);
					}
					for(int x=1;x<63;x++){
						f[i][j][k][x]=dec(s,g[i][j][k][x]);
					}
				}

	}
	int ans=0;
	for(int x=1;x<63;x++){
		upd(ans,g[1][1][1][x]);
	}
	printf("%d\n",ans);
}