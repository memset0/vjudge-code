#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0;char c=getchar();bool f=0; while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-48,c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)x=-x,putchar('-');
	if(x>9)print(x/10); putchar(x%10+48);
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
int a,b;
int main(){
	read(a),read(b);
	print(a+b,'\n');
}