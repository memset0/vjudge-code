// luogu-judger-enable-o2
// test

// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using std::min;
std::map<std::pair<char,short>,int>ma[100001];
char get(){
    char ch=getchar();
    while(ch<'a'||ch>'z')ch=getchar();
    return ch;
}
int end[100010],pre[100010],cnt,n,length[100010],nxt[100010],ope[100010][2],len,P=998244353,f[100001];
int head[100010],Nxt[200010],b[200010],k;
void push(int s,int t){
    Nxt[++k]=head[s];
    head[s]=k;
    b[k]=t;
}
long long ans[100010],fin[100010],val[100010][3];
long long getsum(long long l,long long r){
    if(l>r)return 0;
    return (l+r)*(r-l+1)/2;
}
void dfs(int x,int f){
    if(ope[x][0]){
        int tem=nxt[len];
        ++len;
        ans[len]=0;
        val[len][0]=ope[x][0];
        val[len][1]=ope[x][1];
        val[len][2]=val[len-1][2]+ope[x][1];
        nxt[len]=0;
        if(len==1){
            ans[len]=getsum(1,val[1][1]-1);
        }
        else{
            while(tem&&(val[tem+1][0]!=ope[x][0]||val[tem+1][1]!=ope[x][1]))tem=nxt[tem];
            if(tem||(val[1][0]==ope[x][0]&&val[1][1]<=ope[x][1]))nxt[len]=tem+1;
            else nxt[len]=tem;
            tem=nxt[len-1];
            long long lastlength=0;
            while(lastlength<val[len][1]&&tem){
                if(val[tem+1][0]==ope[x][0]&&val[tem+1][1]>lastlength){
                    ans[len]+=getsum(val[tem][2]+lastlength+1,val[tem][2]+min(val[tem+1][1],val[len][1]));
                    lastlength=val[tem+1][1];
                }
                tem=nxt[tem];
            }
            if(lastlength<val[len][1]&&val[1][0]==val[len][0]){
                ans[len]+=getsum(lastlength+1,min(val[len][1],val[1][1]));
                lastlength=std::max(lastlength,min(val[len][1],val[1][1]));
                ans[len]+=val[1][1]*(val[len][1]-lastlength);
            }
            ans[len]+=ans[len-1];
        }
    }
    fin[x]=ans[len];
    for(int i=head[x];i;i=Nxt[i]){
        dfs(b[i],x);
    }
    if(ope[x][0])--len;
}
int read(){
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x;
}
void write(long long x){
    if(x>9)write(x/10);
    putchar((x%10)+'0');
}
signed main(){
//	freopen("jojo.in","r",stdin);
//	freopen("jojo.out","w",stdout);
    scanf("%d",&n);
    for(int i=1,opt,x;i<=n;i++){
        opt=read(),x=read();
        if(opt==1){
            ope[i][0]=get();
            ope[i][1]=x;
            auto y=std::make_pair(ope[i][0],ope[i][1]);
            f[i]=ma[f[i-1]][y];
            if(!f[i]) ma[f[i-1]][y]=i,push(f[i-1],i),f[i]=i;
        }
        else{
            f[i]=f[x];
        }
    }
    dfs(0,-1);
    for(int i=1;i<=n;i++)write(fin[f[i]]%P),putchar('\n');
}