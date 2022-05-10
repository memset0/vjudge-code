// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int c=0,h=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') h=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){c=c*10+(ch^48);ch=getchar();}
    return c*h;
}
#define N 22222222
using namespace std;
int tot=1,len,ans,f[N],t;
char ch[N],s[N];
int main() 
{
    scanf("%s", ch);
    s[0]='!';
    len=strlen(ch);
    for(register int i=0;i<len;i++)
        s[++tot]='#',s[++tot]=ch[i];
    s[++tot]='#',s[++tot]=')';
    for(register int i=1;i<tot;i++) 
    {
    	int r=t+f[t];
    	if(t*2-i>=0) f[i]=min(min(f[t*2-i],i-t),r-i);
        while(i+f[i]<=tot&&i-f[i]>=0 &&s[i+f[i]]==s[i-f[i]])f[i]++;
        if(i+f[i]>t+f[t]) t=i;
        ans=max(ans,f[i]-1);
 		//cout<<f[i]<<" "<<' '<<s[i]<<endl; 
    }
    printf("%d\n",ans);
    return 0;
}