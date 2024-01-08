#include<bits/stdc++.h>
using namespace std;

template<class T> inline void read(T &x){
	x=0; char c=getchar(); bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
namespace mem{

int T;
long long n;

void out(long long y,int m,int d){
	printf("%d %d ",d,m);
	if(y<0){
		printf("%lld BC\n",-y);
	}else{
		printf("%lld\n",y);
	}
}

void bruteforce(long long n){
	long long y=-4713;
	int m=1,d=1,t;
	while(n--){
		if(y==1582&&m==10&&d==4){
			d=15;
		}else{
			if(m==1||m==3||m==5||m==7||m==8||m==10||m==12){
				t=31;
			}else if(m==4||m==6||m==9||m==11){
				t=30;
			}else{
				if(y<=1582){
					if(y<0){
						t=(-y)%4==1?29:28;
					}else{
						t=y%4==0?29:28;
					}
				}else{
					t=(y%4==0&&y%100!=0)||y%400==0?29:28;
				}
			}
			++d;
			if(d>t)d=1,++m;
			if(m>12)m=1,++y;
			if(!y)++y;
		}
//		if(y==1600&&m==1&&d==1){
//			printf(">> %lld\n",n); 
//		}
//		out(y,m,d);
	}
	out(y,m,d);
}

int tem,am[370],ad[370],bm[370],bd[370],cy[6300],cm[6300],cd[6300];
void init(){
	am[1]=ad[1]=1;
	for(int m,i=2;i<=365;i++){
		m=am[i]=am[i-1],ad[i]=ad[i-1]+1;
		if(m==1||m==3||m==5||m==7||m==8||m==10||m==12){
			tem=31;
		}else if(m==4||m==6||m==9||m==11){
			tem=30;
		}else{
			tem=28;
		}
		if(ad[i]>tem)ad[i]=1,++am[i];
	}
	bm[1]=bd[1]=1;
	for(int m,i=2;i<=366;i++){
		m=bm[i]=bm[i-1],bd[i]=bd[i-1]+1;
		if(m==1||m==3||m==5||m==7||m==8||m==10||m==12){
			tem=31;
		}else if(m==4||m==6||m==9||m==11){
			tem=30;
		}else{
			tem=29;
		}
		if(bd[i]>tem)bd[i]=1,++bm[i];
	}
	cy[1]=1582,cm[1]=10,cd[1]=15;
	for(int m,y,i=2;i<=6288;i++){
		y=cy[i]=cy[i-1],m=cm[i]=cm[i-1],cd[i]=cd[i-1];
		if(m==1||m==3||m==5||m==7||m==8||m==10||m==12){
			tem=31;
		}else if(m==4||m==6||m==9||m==11){
			tem=30;
		}else{
			tem=(y%4==0&&y%100!=0)||y%400==0?29:28;
		}
		++cd[i];
		if(cd[i]>tem)cd[i]=1,++cm[i];
		if(cm[i]>12)cm[i]=1,++cy[i];
	}
}

void solve(long long n){
//	printf("\n>> solve %lld\n",n);
	if(n<=2299160){ // Julian calendar
		int y=-4712,m,d;
		y+=4*(n/1461),n%=1461; // four years period
		if(n<366){
			m=bm[n+1],d=bd[n+1];
		}else{
			y+=1,n-=366;
			for(int i=0;i<3;i++)if(n>=365)y+=1,n-=365;
			m=am[n+1],d=ad[n+1];
		}
		if(y<=0)--y;
		out(y,m,d);
	}else{ // Gregorian calendar
		n-=2299161;
		if(n<6287){
			out(cy[n+1],cm[n+1],cd[n+1]);
		}else{
			n-=6287;
			long long y=1600;
			y+=400*(n/146097),n%=146097;
			bool fl;
			if(n>=36525){
				y+=100,n-=36525;
				for(int i=0;i<3;i++)if(n>=36524)y+=100,n-=36524;
				fl=true;
			}else{
				fl=false;
			}
//			printf("> %lld %d\n",n,fl);
			if(fl&&n>=1460){
				y+=4,n-=1460;
				fl=false;
			}
			y+=4*(n/1461),n%=1461;
//			printf("> %lld %d\n",n,fl);
			if(fl){
				for(int i=0;i<4;i++)if(n>=365)y+=1,n-=365;
			}else{
				if(n>=366){
					y+=1,n-=366;
					for(int i=0;i<3;i++)if(n>=365)y+=1,n-=365;
				}
			}
			
			int m,d;
			if((y%4==0&&y%100!=0)||y%400==0){
				m=bm[n+1],d=bd[n+1];
			}else{
				m=am[n+1],d=ad[n+1];
			}
			out(y,m,d);
		}
	}
}

void akcsp(){
	init();
	read(T);
	while(T--){
		read(n);
		solve(n);
//		bruteforce(n);
	}
}

}

int main(){
#ifdef memset0
//	freopen("julian0.in","r",stdin);
	freopen("julian3.in","r",stdin);
	freopen("julian3.out","w",stdout);
#else
	freopen("julian.in","r",stdin);
	freopen("julian.out","w",stdout);
#endif
	mem::akcsp();
}