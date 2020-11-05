#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register char c=getchar(); register bool f=0;
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=5e3+10;
int cur,lst,nod,end,f[N],siz[N],fail[N],len[N],s[N],ch[N][26],jump[N][20];
long long ans[N];
int find(int x){while(s[end]!=s[end-len[x]-1])x=fail[x];return x;}
int search(int x,int lim){
	for(int i=19;i>=0;i--){
		if(len[jump[x][i]]>=lim)x=jump[x][i];
	}
	return len[x]==lim&&x>2?x:-1;
}
void append(int c){
	// printf("append %d\n",c);
	s[++end]=c,cur=find(lst);
	if(!ch[cur][c]){
		ch[cur][c]=++nod;
		len[nod]=len[cur]+2;
		fail[nod]=cur==1?2:ch[find(fail[cur])][c];
	}
	siz[lst=ch[cur][c]]++;
	// printf("%d %d : %d %d\n",cur,lst,len[lst],fail[lst]);
}
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
	nod=2,lst=1,fail[2]=1,len[1]=-1,s[0]=-1;
	for(char c=getchar();c!='\n'&&c!='\r'&&c!=-1;c=getchar())append(c-'a');
	for(int i=nod;i>=3;i--)siz[fail[i]]+=siz[i];
	for(int i=1;i<=nod;i++)jump[i][0]=fail[i];
	for(int i=1;i<20;i++){
		for(int j=1;j<=nod;j++)jump[j][i]=jump[jump[j][i-1]][i-1];
	}
	for(int i=3;i<=nod;i++){
		if(len[i]<=1)f[i]=1;
		else{
			int to=search(i,len[i]>>1);
			if(~to)f[i]=f[to]+1;
			else f[i]=1;
		}
		ans[f[i]]+=siz[i];
	}
	// for(int i=1;i<=nod;i++)printf("%d [%d] len=%d\n",i,f[i],len[i]);
	for(int i=end;i>=1;i--)ans[i]+=ans[i+1];
	for(int i=1;i<=end;i++)print(ans[i]," \n"[i==end]);
} // 123