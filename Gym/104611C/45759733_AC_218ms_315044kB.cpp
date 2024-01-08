#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
typedef long long ll;
const int MAXN = 1000011;
struct SAM
{
    int t[MAXN*2][26],len[MAXN],pre[MAXN];
    int last,tot;
    SAM(){last=tot=1;}
    int extend(int w)
    {
        int pos=last,cur=++tot;
        len[cur]=len[pos]+1,last=cur;
        while(pos&&!t[pos][w])t[pos][w]=cur,pos=pre[pos];
        if(!pos){pre[cur]=1;return len[cur];}
        int nxt=t[pos][w];
        if(len[nxt]==len[pos]+1)pre[cur]=nxt;
        else
        {
            int tmp=++tot;
            len[tmp]=len[pos]+1,memcpy(t[tmp],t[nxt],sizeof t[nxt]);
            pre[tmp]=pre[nxt],pre[cur]=pre[nxt]=tmp;
            while(pos&&t[pos][w]==nxt)t[pos][w]=tmp,pos=pre[pos];
        }
        return len[cur]-len[pre[cur]];
    }
}sam;
ll f[MAXN/2][26];
char a[MAXN],b[MAXN];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    scanf("%s%s",a+1,b+1);
    for(int i=1;i<=n;++i)
    {
        int c=a[i]-'a';
        int x=sam.extend(c);
        memcpy(f[i],f[i-1],sizeof f[i]);
        f[i][c]+=x;
    }
    ll ans=0;
    for(int i=m;i;--i)
    {
        for(int c=0;c<26;++c)
            if(i>1&&c==b[i-1]-'a')
            {
                ans+=f[n-(m-i)][c]>0;
            }
            else ans+=f[n-(m-i)][c];
    }
    printf("%lld\n",ans);
    return 0;
}