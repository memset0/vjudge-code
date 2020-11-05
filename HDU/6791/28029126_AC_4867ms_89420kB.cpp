#include <cstdio>
#include <cstring>
#include <algorithm>

int p,n,len[600001],cnt[600001],son[600001][26],fail[600001],last,cur;
long long ans,tem;
char str[300010];
inline int getfail(register int x){
    while(str[n-len[x]-1]!=str[n])x=fail[x];
    return x;
}
void add(register int ch){
    ++n;
    cur=getfail(last);
    if(!son[cur][ch]){
        len[++p]=len[cur]+2;
        fail[p]=son[getfail(fail[cur])][ch];
        ++cnt[last=son[cur][ch]=p];
    }
    else ++cnt[last=son[cur][ch]];
}
void write(register long long x){
    if(x>9)write(x/10);
    putchar((x%10)+'0');
}
int fa[200001][21],dep[200001],head[200001],b[200001],nxt[200001],k;
void getans(int x,int f){
    fa[x][0]=f;
    for(int i=1;i<=20;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
    dep[x]=dep[f]+1; 
    for(int i=head[x];i;i=nxt[i])
        getans(b[i],x);
}
int get(int x,int l){
    for(int i=20;~i;--i)
        if(len[fa[x][i]]>=l)x=fa[x][i];
    return x;
}
void push(int s,int t){
    nxt[++k]=head[s];
    head[s]=k;
    b[k]=t;
}
void dfs(){
    for(int i=2;i<=p;i++)push(fail[i]?fail[i]:1,i);
    getans(1,0);
}
int t;
long long hash[200001],Pow[200001];
int pos[200001];
long long Get(int x,int l){
    return (hash[x]+1004535809-(1ll*hash[fa[x][l]]*Pow[1<<l])%1004535809)%1004535809;
}
int main(){
    scanf("%d",&t);
    for(int fd=1;fd<=t;fd++){
        int r=0;
        scanf("%d",&r);
        scanf("%s",str+1);
        memset(len,0,sizeof len);
        memset(cnt,0,sizeof cnt);
        memset(son,0,sizeof son);
        memset(fail,0,sizeof fail);
        n=last=p=cur=0;
        len[++p]=str[0]=-1;
        fail[0]=1;
        memset(head,0,sizeof head);
        k=0;
        for(register int i=1;i<=r;++i)add(str[i]-'a'),pos[i]=last;
        dfs();
        for(int i=2;i<=p;i++)hash[i]=(1ll*hash[fail[i]]*470289+len[i])%1004535809;
        Pow[0]=1;
        for(int i=1;i<=p;i++)Pow[i]=1ll*Pow[i-1]*470289%1004535809;
        int q;
        scanf("%d",&q);
        for(int i=1;i<=q;i++){
            int a,b,c,d;
            scanf("%d%d%d%d",&a,&b,&c,&d);
            a=b-a+1,b=pos[b];
            for(int j=20;~j;--j)if(len[fa[b][j]]>=a)b=fa[b][j];
            c=d-c+1,d=pos[d];
            for(int j=20;~j;--j)if(len[fa[d][j]]>=c)d=fa[d][j];
//            for(int i=1;i<=p;i++)printf("%d %d %d\n",i,len[i],fa[i][0]);
//            printf("%d %d\n",b,d);
            if(hash[b]==hash[d])puts("draw");
            else{
                for(int i=20;~i;--i)
                    if(Get(b,i)==Get(d,i))b=fa[b][i],d=fa[d][i];
                if(len[b]<len[d])puts("sjfnb");
                else puts("cslnb");
            }
        }
    }
}
//abcbcbcbaaabcbabcdfdafafasdfadfadsf