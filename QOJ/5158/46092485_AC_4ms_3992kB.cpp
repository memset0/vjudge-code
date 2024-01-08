#include<bits/stdc++.h>
using namespace std;
int l,r,len,ap1,ap2,ans1,ans2;
char s[15];
int main(){
	scanf("%d%d",&l,&r);
	for(int i=l;i<=r;++i){
		scanf("%s",s),len=strlen(s);
		if(isdigit(s[0]))continue;
		if(len==8||s[0]=='F'){
			if(ap1){
				if(!ans1)ans1=i-ap1;
			}
			else ap1=i;
		}
		if(len==8||s[0]=='B'){
			if(ap2){
				if(!ans2)ans2=i-ap2;
			}
			else ap2=i;
		}
	}
	printf("%d %d",ans1?ans1:(ap1?ap1:r+1),ans2?ans2:(ap2?ap2:r+1));
	return 0;
}
/*
7 11
7 8 Fizz Buzz 11
49999 50002
49999 FizzBuzz 50001 Fizz
*/