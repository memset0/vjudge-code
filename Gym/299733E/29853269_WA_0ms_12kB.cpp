#include<bits/stdc++.h>
using namespace std;
int a,b;
char c;
inline bool check(){
	if(c=='=')return a==b;
	if(c=='<')return a<b;
	if(c=='>')return a>b;
}
int main(){
  scanf("%d %c %d",&a,&c,&b);
	puts(check()?"Yes":"No");
}