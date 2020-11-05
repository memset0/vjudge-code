#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define add(a,b) if((a+=b)>=mod)a-=mod;
template<class T> inline void read(T &x){
    x=0;register char c=getchar();register bool f=0;
    while(!isdigit(c))f^=c=='-',c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar();
    if(f)x=-x;
}
template<class T> inline void print(T x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=105,mod=998244353;
int T,n,m,ans,f[N][N][N],g[N][N][N];
int vet[N][N],val[N][N],len[N];
int main(){
#ifdef memset0
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
#endif
    for(read(T);T--;){
        read(n),read(m),ans=0;
        for(int i=1;i<=n;i++)len[i]=0;
        for(int i=1,l,r,x;i<=m;i++){
            read(l),read(r),read(x);
            vet[r][len[r]]=l,val[r][len[r]]=x-1,len[r]++;
        }
        memset(f,0,sizeof(f)),f[0][0][0]=1;
        for(int i=2;i<=n;i++){
            for(int a=0;a<n;a++)
                for(int b=a?a+1:0;b<=n;b++)
                    for(int c=b?b+1:0;c<=n;c++)
                        g[a][b][c]=0;
            add(g[0][0][0],f[0][0][0]);
            add(g[0][0][i-1],f[0][0][0]);
            for(int a=1;a<i-1;a++){
                add(g[0][0][a],f[0][0][a]);
                add(g[0][0][i-1],f[0][0][a]);
                add(g[0][a][i-1],f[0][0][a]);
            }
            for(int a=1;a<i-1;a++)
                for(int b=a+1;b<i-1;b++){
                    add(g[0][a][b],f[0][a][b]);
                    add(g[0][a][i-1],f[0][a][b]);
                    add(g[0][b][i-1],f[0][a][b]);
                    add(g[a][b][i-1],f[0][a][b]);
                }
            for(int a=1;a<i-1;a++)
                for(int b=a+1;b<i-1;b++)
                    for(int c=b+1;c<i-1;c++){
                        add(g[a][b][c],f[a][b][c]);
                        add(g[a][b][i-1],f[a][b][c]);
                        add(g[a][c][i-1],f[a][b][c]);
                        add(g[b][c][i-1],f[a][b][c]);
                    }
            bool flag=true;
            for(int k=0;k<len[i];k++){
                if(val[i][k]){flag=false;break;}
            }
            f[0][0][0]=flag?g[0][0][0]:0;
            for(int a=1;a<i;a++)
                if(g[0][0][a]){
                    bool flag=true;
                    for(int k=0;k<len[i];k++){
                        if((int)(a>=vet[i][k])!=val[i][k]){flag=false;break;}
                    }
                    f[0][0][a]=flag?g[0][0][a]:0;
                }
            for(int a=1;a<i;a++)
                for(int b=a+1;b<i;b++)
                    if(g[0][a][b]){
                        bool flag=true;
                        for(int k=0;k<len[i];k++){
                            if((int)((a>=vet[i][k])+(b>=vet[i][k]))!=val[i][k]){flag=false;break;}
                        }
                        f[0][a][b]=flag?g[0][a][b]:0;
                    }
            for(int a=1;a<i;a++)
                for(int b=a+1;b<i;b++)
                    for(int c=b+1;c<i;c++)
                        if(g[a][b][c]){
                            bool flag=true;
                            for(int k=0;k<len[i];k++){
                                if((int)((a>=vet[i][k])+(b>=vet[i][k])+(c>=vet[i][k]))!=val[i][k]){flag=false;break;}
                            }
                            f[a][b][c]=flag?g[a][b][c]:0;
                        }
        }
        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++)
                for(int k=0;k<=n;k++){
                    f[i][j][k]=4ll*f[i][j][k]%mod;
                    if(k)f[i][j][k]=3ll*f[i][j][k]%mod;
                    if(j)f[i][j][k]=2ll*f[i][j][k]%mod;
                    add(ans,f[i][j][k]);
                }
        std::cout<<ans<<std::endl;
    }
    // std::cerr<<clock()/(double)CLOCKS_PER_SEC<<std::endl;
}