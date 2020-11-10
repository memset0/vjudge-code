#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

int sa[6000010],tp[6000010],rank[6000010],tax[6000010],a[6000010],n,m,S;
void Q()
{
    for(int i=0;i<=m;i++) tax[i]=0;
    for(int i=1;i<=n;i++) tax[rank[i]]++;
    for(int i=1;i<=m;i++) tax[i]+=tax[i-1];
    for(int i=n;i;i--) sa[tax[rank[tp[i]]]--]=tp[i];
}
void _S(){
    for(int i=1;i<=(n<<1);i++)rank[i]=tp[i]=0;
    for(int i=1;i<=n;i++)rank[i]=a[i],tp[i]=i;
    Q();
    for(int w=1,p=1;p<n;m=p,w<<=1){
        p=0;
        for(int i=1;i<=w;i++)tp[++p]=n-w+i;
        for(int i=1;i<=n;i++)if(sa[i]>w)tp[++p]=sa[i]-w;
        Q();
        for(int i=1;i<=n+w;i++)std::swap(rank[i],tp[i]);
        rank[sa[1]]=p=1;
        for(int i=2;i<=n;i++)
            rank[sa[i]]=(tp[sa[i-1]]==tp[sa[i]]&&tp[sa[i-1]+w]==tp[sa[i]+w])?p:++p;
    }
}
int T,q;
int nxt[3000010];
int head[3000010],Nxt[6000010],b[6000010],k,te[6000010],size[6000010],sum[6000010],pre[6000010],v[6000010];
std::vector<std::pair<int,int> >sons[3000010];
void push(int s,int t){
    Nxt[++k]=head[s];
    head[s]=k;
    b[k]=t;
}
void dfs(int x,int f){
    if(f<=n){
//        printf("%d %d\n",x,f);
        int u=a[x+(n-f+1)];
        v[x]=u;
        if(u==v[f])sum[x]=sum[f]+1,pre[x]=pre[f];
        else pre[x]=f,sum[x]=1;
    }
    else v[x]=S+1;
    size[x]=1;
    for(int i=head[x];i;i=Nxt[i]){
        dfs(b[i],x);
        size[x]+=size[b[i]];
        if(x<=n)sons[x].push_back(std::make_pair(a[b[i]+(n-x+1)],size[b[i]]));
    }
    std::sort(sons[x].begin(),sons[x].end());
    for(int i=1;i<(int)sons[x].size();i++)sons[x][i].second+=sons[x][i-1].second;
}
int read(){
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x;
}
void write(int x){
    if(x>9)write(x/10);
    putchar((x%10)+'0');
}
int main(){
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    scanf("%d",&T);
    for(int fd=1;fd<=T;fd++){
//        fprintf(stderr,"%d\n",fd);
        n=read(),S=read(),q=read();
        m=S;
        for(int i=1;i<=n;i++)a[i]=read();
        _S();
//        for(int i=1;i<=n;i++)printf("%d ",a[i]);putchar('\n');
//        for(int i=1;i<=n;i++)printf("%d ",rank[i]);putchar('\n');
        for(int i=1;i<=n;i++)nxt[i]=n+1;
        for(int i=n-1,j=n+1;i;--i){
            while(j!=n+1&&a[i]!=a[j-1])j=nxt[j];
            if(a[i]==a[j-1])--j;
            nxt[i]=j;
        }
        for(int i=1;i<=n+1;i++)sons[i].clear();
        for(int i=1;i<=n+1;i++)v[i]=sum[i]=pre[i]=0;
        for(int i=1;i<=n+1;i++)head[i]=0;
        k=0;
        for(int i=1;i<=n;i++)push(nxt[i],i);
        dfs(n+1,n+2);
        for(int i=0;i<=S;i++)te[i]=0;
        for(int i=1;i<=n;i++)++te[a[i]];
        for(int i=1;i<=S;i++)te[i]+=te[i-1];
        for(int i=1,t,c,j,lans=0;i<=q;i++){
//            printf("*%d\n",i);
            t=read(),c=read(),j=read();
            c^=lans;
            j^=lans;
//            printf("%d %d %d\n",t,c,j);
            if(t==1){
                if(j>1){
                    --j;
                    lans=rank[j];
                    if(c<a[j])++lans;
                    else if(c==a[j]&&j<n&&rank[1]<rank[j+1])++lans;
                    write(lans);
                    putchar('\n');
                }
                else{
                    int l=1,r=n,mid,ans=0;
                    while(l<=r){
                        mid=(l+r)>>1;
                        if(c>a[sa[mid]])ans=mid,l=mid+1;
                        else if(c==a[sa[mid]]){
                            if(sa[mid]==n||rank[1]>rank[sa[mid]+1])ans=mid,l=mid+1;
                            else r=mid-1;
                        }else r=mid-1;
                    }
                    write(lans=ans+1);
                    putchar('\n');
                }
            }
            else{
                if(j<n+1){
                lans=rank[j];
//                printf("%d\n",rank[j]);
//                for(int k=0;k<sons[j].size();k++)printf("%d ",sons[j][k]);putchar('\n');
                    int u=j;
                    while(u&&u<=n){
                        if(c>v[u])lans-=sum[u];
                        u=pre[u];
                    }
//                    printf("%d\n",lans);
                    std::vector<std::pair<int,int> >::iterator it=std::lower_bound(sons[j].begin(),sons[j].end(),std::make_pair(c,0));
                    if(it!=sons[j].begin())lans+=(--it)->second;
                    if(a[j]>=c)++lans;
                    write(lans);
                    putchar('\n');
                }
                else{
                    write(lans=te[c-1]+1);
                    putchar('\n');
                }
            }
        }
    }
}
