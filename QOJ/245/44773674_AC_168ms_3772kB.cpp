#include<bits/stdc++.h>
using namespace std;
int T,h,m;
char tim[114];
double z;
int toint(double x){
	return x<0?x-0.5:x+0.5;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&h,&m);
		scanf("%s",tim);
		if(tim[3]=='+'){
			sscanf(tim,"UTC+%lf",&z),z-=8;
			m+=toint(z*60);
		}else{
			sscanf(tim,"UTC-%lf",&z),z+=8;
			m-=z*60+0.5;
		}
		while(m<0)m+=60,--h;
		while(m>=60)m-=60,++h;
		while(h<0)h+=24;
		while(h>=24)h-=24;
		printf("%02d:%02d\n",h,m);
	}
	return 0;
}