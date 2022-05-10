#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=3e5+10;
int n,m,end,nod,lst,cur;
char s[N];
int len[N],fail[N],ch[N][26];
inline int find(int x){while(s[end]!=s[end-len[x]-1])x=fail[x];return x;}
void append(int c){
	++end,cur=find(lst);
	if(!ch[cur][c]){
		ch[cur][c]=++nod;
		len[cur][c]=len[cur]+2;
		fail[nod]=cur==1?2:ch[find(fail[cur])][c];
	}
	lst=ch[cur][c];
}
int main(){
	len[1]=-1,fail[2]=1,nod=2;
	read(n),read(m),scanf("%s",s+1);
	for(int l,r,i=1;i<=m;i++){
		read(l),read(r);
	}
}