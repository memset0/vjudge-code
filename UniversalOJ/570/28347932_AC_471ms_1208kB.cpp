//code by mocania
#include<bits/stdc++.h>
using namespace std;
bool fl[500];
long long f1[13],f2[13];
inline void write(long long u){
	if(u>9) write(u/10); putchar(u%10+'0');
}
inline void solve(long long a,int b,int c){
	if(a<=0) write(c),putchar(' '),write(b),putchar(' '),write(1-a),puts(" BC");
	else write(c),putchar(' '),write(b),putchar(' '),write(a),puts("");
}
int main(){
//	freopen("julian.in","r",stdin);
//	freopen("julian.out","w",stdout);
	int q; cin>>q; long long ans=0;
	for(int i=1;i<=12;i++) f1[i]=f2[i]=30;
	f1[1]=f1[3]=f1[5]=f1[7]=f1[8]=f1[10]=f1[12]=31;
	for(int i=1;i<=12;i++) f2[i]=f1[i]; f1[2]=28,f2[2]=29;
	for(int i=0;i<400;i++) if(i%400==0||(i%4==0&&i%100!=0)) fl[i]=1;
	for(int i=0;i<400;i++) ans=ans+365+fl[i];
	while(q--){
		long long v; scanf("%lld",&v); long long a=-4712;
		while(v>=1461*25&&a+100<0){
			v-=1461*25,a+=100;
		}
		while(v>0){
			long long x=a;
			int y=365+(abs(x)%4==0);
			if(v>=y) v-=y,a++; else break;
			if(a==1) break;
		}
		while(v>=1461*25&&a+100<1582){
			v-=1461*25,a+=100;
		}
		
		while(v>0&&a>=0){
			long long x=a;
			int y=365+(abs(x)%4==0);
			if(v>=y) v-=y,a++; else break;
			if(a==1582) break; 
		}
		long long q=0;
		for(int i=1;i<10;i++) q+=f1[i]; q+=3;
		
		if(a==1582&&v<=q){
			for(int i=1;i<=12;i++)
				if(v>=f1[i]) v-=f1[i];
				else{
					solve(a,i,v+1); break;
				}
		}
		else if(a<1582||(a==1582&&v<=365)){
			if(a==1582) v+=10;
			long long c=abs(a);
//			cout<<a<<","<<v<<","<<c<<endl;
			if(c%4!=0){
				for(int i=1;i<=12;i++)
					if(v>=f1[i]) v-=f1[i];
					else{
						solve(a,i,v+1); break;
					}
			}
			else{
					for(int i=1;i<=12;i++)
						if(v>=f2[i]) v-=f2[i];
						else{
							solve(a,i,v+1); break;
						}
			}
		}
		else{
			v+=10;
			if(v>=ans) a+=(v/ans)*400,v%=ans;
			while(v>=0){
				long long x=(a)%400,y=365+fl[x];
				if(v>=y) v-=y,a++;
				else if(!fl[x]){
					for(int i=1;i<=12;i++)
						if(v>=f1[i]) v-=f1[i];
						else{
							solve(a,i,v+1); break;
						}
					break;
				}
				else{
					for(int i=1;i<=12;i++)
						if(v>=f2[i]) v-=f2[i];
						else{
							solve(a,i,v+1); break;
						}
					break;
				}
			}
		}
	}
}
//1
//2299004