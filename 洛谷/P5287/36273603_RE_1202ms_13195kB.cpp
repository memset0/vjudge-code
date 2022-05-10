// luogu-judger-enable-o2
// test

// luogu-judger-enable-o2
#include <cstdio>
#include <vector>
#include <algorithm>
#define int long long

using std::min;

char get(){
    char ch=getchar();
    while(ch<'a'||ch>'z')ch=getchar();
    return ch;
}
int end[100010],pre[100010],cnt,n,length[100010],nxt[100010],ope[100010][2],len,val[100010][3],P=998244353;
int head[100010],Nxt[200010],b[200010],k;
void push(int s,int t){
    Nxt[++k]=head[s];
    head[s]=k;
    b[k]=t;
}
long long ans[100010],fin[100010];
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
            int lastlength=0;
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
signed main(){
//	freopen("jojo.in","r",stdin);
//	freopen("jojo.out","w",stdout);
    scanf("%lld",&n);
    for(int i=1,opt,x;i<=n;i++){
        scanf("%lld%lld",&opt,&x);
        if(opt==1){
            push(i-1,i);
            ope[i][0]=get();
            ope[i][1]=x;
        }
        else{
            push(x,i);
        }
    }
    dfs(0,-1);
    for(int i=1;i<=n;i++)printf("%lld\n",fin[i]%P);
}