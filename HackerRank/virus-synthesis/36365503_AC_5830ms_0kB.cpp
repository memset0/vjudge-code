#include<bits/stdc++.h>
template<class T> inline void read(T &x){
	x=0; register bool f=0; register char c=getchar();
	while(!isdigit(c))f^=c=='-',c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=1e5+10;
int T,len,f[N],map[300],jump[N][20];
char s[N];
struct pam{
	int cur,nod,end,lst,s[N],fa[N],fail[N],trans[N],len[N],ch[N][4];
	int find(int x){
		// printf("find %d : %d[%d] %d[%d]\n",x,end,s[end],end-len[x]-1,s[end-len[x]-1]);
		while(s[end]!=s[end-len[x]-1])x=fail[x];return x;
	}
	void init(){end=0,s[0]=-1,lst=1,nod=2,fail[2]=1,len[1]=-1,memset(ch[1],0,16),memset(ch[2],0,16);}
	void append(int c){
		s[++end]=c,cur=find(lst);
		// printf("append %d : lst=%d cur=%d\n",c,lst,cur);
		if(!ch[cur][c]){
			++nod,memset(ch[nod],0,16);
			ch[cur][c]=nod,fa[nod]=cur;
			len[nod]=len[cur]+2;
			fail[nod]=cur==1?2:ch[find(fail[cur])][c];
		}
		lst=ch[cur][c];
		// printf("lst=%d : fa=%d len=%d fail=%d trans=%d\n",lst,fa[lst],len[lst],fail[lst],trans[lst]);
	}
	int solve(){
		for(int i=1;i<=nod;i++)jump[i][0]=fail[i];
		for(int i=1;i<20;i++){
			for(int j=1;j<=nod;j++)jump[j][i]=jump[jump[j][i-1]][i-1];
		}
		for(int i=3;i<=nod;i++)
			if(len[i]&1^1){
				trans[i]=i;
				for(int j=19;j>=0;j--)if(len[jump[trans[i]][j]]>len[i]/2)trans[i]=jump[trans[i]][j];
				if(len[trans[i]]>len[i]/2)trans[i]=fail[trans[i]];
			}
		f[1]=-1,f[2]=1;
		for(int i=3;i<=nod;i++)if(len[i]&1^1){
			f[i]=std::min(len[i]/2+1,f[fa[i]]+1);
			if(trans[i]>2)f[i]=std::min(f[i],f[trans[i]]+len[i]/2-len[trans[i]]+1);
		}else{
			f[i]=100000;
		}
		int ans=end;
		for(int i=1;i<=nod;i++)if(len[i]&1^1){
			ans=std::min(ans,f[i]+end-len[i]);
		}
		return ans;
	}
}p;
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
#endif
	map['A']=0,map['G']=1,map['T']=2,map['C']=3;
	for(read(T);T--;){
		scanf("%s",s+1),len=strlen(s+1),p.init();
		for(int i=1;i<=len;i++)p.append(map[s[i]]);
		print(p.solve(),'\n');
	}
}