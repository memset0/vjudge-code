#include<bits/stdc++.h>
using namespace std;
const int N=2e5+7,K=22,Q=20000007,M=10000007; vector<int>v[N]; long long ans;
int n,k,m,q,qt,ow[K],df1[N],df2[N],rt1[N],rt2[N],s[K][N],zt[N],col[N],vx[N],ch[Q][2],va[Q],og[Q],req[M][21];
inline int read(){
    int num=0; char g=getchar(); while(g<48||57<g) g=getchar();
    while(47<g&&g<58) num=(num<<1)+(num<<3)+g-48,g=getchar(); return num;
}
inline void write(long long u){
    if(u>9) write(u/10); putchar(u%10+'0');
}
inline void dfs(int u){
    df1[u]=df2[u]=++q;
    for(int i=0;i<v[u].size();i++){
        if(!df1[v[u][i]]) dfs(v[u][i]),df2[u]=df2[v[u][i]];
    }
}
inline void add1(int l,int r,int ql,int qr,int t){
    if(!og[t]) og[t]=++qt;
    for(int j=0;j<=20;j++) req[og[t]][j]+=ow[j];
    if(l==ql&&r==qr){
        return;
    }
    int d=(l+r)>>1;
    if(ql<=d){
        if(!ch[t][0]) ch[t][0]=++k;
        add1(l,d,ql,min(qr,d),ch[t][0]);
    }
    if(d+1<=qr){
        if(!ch[t][1]) ch[t][1]=++k;
        add1(d+1,r,max(d+1,ql),qr,ch[t][1]);
    }
}
inline void add2(int l,int r,int ql,int qr,int t){
//    cout<<l<<","<<r<<" "<<ql<<" "<<qr<<endl;
    if(l==ql&&r==qr){
//        cout<<l<<","<<r<<" "<<ql<<" "<<qr<<" "<<ow[0]<<" "<<t<<endl;
        if(!og[t]) og[t]=++qt;
        for(int j=0;j<=20;j++) req[og[t]][j]+=ow[j];
        return;
    }
    int d=(l+r)>>1;
    if(ql<=d){
        if(!ch[t][0]) ch[t][0]=++k;
        add2(l,d,ql,min(qr,d),ch[t][0]);
    }
    if(d+1<=qr){
        if(!ch[t][1]) ch[t][1]=++k;
        add2(d+1,r,max(d+1,ql),qr,ch[t][1]);
    }
}
inline void add3(int l,int r,int ql,int qr,int t,int c){
    va[t]+=c;
    if(l==ql&&r==qr){
        return;
    }
    int d=(l+r)>>1;
    if(ql<=d){
        if(!ch[t][0]) ch[t][0]=++k;
        add3(l,d,ql,min(qr,d),ch[t][0],c);
    }
    if(d+1<=qr){
        if(!ch[t][1]) ch[t][1]=++k;
        add3(d+1,r,max(d+1,ql),qr,ch[t][1],c);
    }
}
inline void add4(int l,int r,int ql,int qr,int t,int c){
    if(l==ql&&r==qr){
        va[t]+=c;
//        cout<<l<<","<<r<<" "<<ql<<" "<<qr<<"ccccc"<<" "<<t<<" "<<c<<" "<<va[t]<<endl;
//        if(!og[t]) og[t]=qt;
//        for(int j=0;j<=20;j++) req[og[t]][j]+=ow[j];
        return;
    }
    int d=(l+r)>>1;
    if(ql<=d){
        if(!ch[t][0]) ch[t][0]=++k;
        add4(l,d,ql,min(qr,d),ch[t][0],c);
    }
    if(d+1<=qr){
        if(!ch[t][1]) ch[t][1]=++k;
        add4(d+1,r,max(d+1,ql),qr,ch[t][1],c);
    }
}
inline void search1(int l,int r,int ql,int qr,int t){
    if(l==ql&&r==qr){
        if(og[t]){
            for(int j=0;j<=20;j++) ow[j]+=req[og[t]][j];
        }
        return;
    }
    int d=(l+r)>>1;
    if(ql<=d&&ch[t][0])
        search1(l,d,ql,min(qr,d),ch[t][0]);
    if(d+1<=qr&&ch[t][1])
        search1(d+1,r,max(d+1,ql),qr,ch[t][1]);
}
inline int search3(int l,int r,int ql,int qr,int t){
    if(l==ql&&r==qr){
        return va[t];
    }
    int d=(l+r)>>1; int ans=0;
    if(ql<=d&&ch[t][0])
        ans+=search3(l,d,ql,min(qr,d),ch[t][0]);
    if(d+1<=qr&&ch[t][1])
        ans+=search3(d+1,r,max(d+1,ql),qr,ch[t][1]);
    return ans;
}
inline void search2(int l,int r,int ql,int qr,int t){
    int d=(l+r)>>1;
//    cout<<l<<","<<r<<" "<<ql<<" "<<qr<<" "<<t<<"www"<<" "<<og[t]<<endl;
    if(og[t]){
        for(int j=0;j<=20;j++) ow[j]+=req[og[t]][j];
    }
    if(ql<=d&&ch[t][0])
        search2(l,d,ql,min(qr,d),ch[t][0]);
    if(d+1<=qr&&ch[t][1])
        search2(d+1,r,max(d+1,ql),qr,ch[t][1]);
}
inline int search4(int l,int r,int ql,int qr,int t){
    int ans=va[t];
//    cout<<l<<","<<r<<" "<<t<<" "<<va[t]<<endl;
    if(l==ql&&r==qr){
//        cout<<l<<"www"<<r<<"sss"<<t<<endl;
        return ans;
    }
    int d=(l+r)>>1;
    if(ql<=d&&ch[t][0])
        ans+=search4(l,d,ql,min(qr,d),ch[t][0]);
    if(d+1<=qr&&ch[t][1])
        ans+=search4(d+1,r,max(d+1,ql),qr,ch[t][1]);
    return ans;
}
inline void addx(int col,int v){
    if(!rt1[col]) rt1[col]=++k;
    if(!rt2[col]) rt2[col]=++k;
    add1(1,n,df1[v],df1[v],rt1[col]);
    if(df1[v]+1<=df2[v])
        add2(1,n,df1[v]+1,df2[v],rt2[col]);
}
inline void addy(int col,int v){
    if(!rt1[col]) rt1[col]=++k;
    if(!rt2[col]) rt2[col]=++k;
    add3(1,n,df1[v],df1[v],rt1[col],1);
    if(df1[v]+1<=df2[v])
        add4(1,n,df1[v]+1,df2[v],rt2[col],1);
}
inline void suby(int col,int v){
    if(!rt1[col]) rt1[col]=++k;
    if(!rt2[col]) rt2[col]=++k;
    add3(1,n,df1[v],df1[v],rt1[col],-1);
    if(df1[v]+1<=df2[v])
        add4(1,n,df1[v]+1,df2[v],rt2[col],-1);
}
inline int searchc(int col,int v,int z){
    int val=0;
    
    if(rt1[col]&&df1[v]+1<=df2[v]) val+=search3(1,n,df1[v]+1,df2[v],rt1[col]);
    if(rt2[col]) val+=search4(1,n,df1[v],df1[v],rt2[col]);
    
    return val;
}
inline void adx(int col,int v,int c){
    memset(ow,0,sizeof(ow)); long long oop=searchc(col,v,0);
    if(rt1[col]&&df1[v]+1<=df2[v]) search1(1,n,df1[v]+1,df2[v],rt1[col]);
    if(rt2[col]) search2(1,n,df1[v],df1[v],rt2[col]);
//    cout<<v<<","<<oop<<endl;
//    cout<<ans<<"zzzzz"<<" "<<oop<<endl;
    for(int j=0;j<=20;j++){
        if(c&(1<<j))
            ans+=(1ll<<j)*(zt[col]-s[j][col]),ans-=(1ll<<j)*(oop-ow[j]),s[j][col]++;
        else
            ans+=(1ll<<j)*s[j][col],ans-=(1ll<<j)*ow[j];
//        if(ans<0){
//            cout<<v<<" "<<j<<","<<ans<<" "<<ow[0]<<" "<<c<<" "<<zt[col]<<" "<<oop<<endl;
//            break;
//        }
    } 
    memset(ow,0,sizeof(ow));
    for(int j=0;j<=20;j++)
        if(c&(1<<j)) ow[j]=1;
    addx(col,v),zt[col]++,addy(col,v);
}
inline void sux(int col,int v,int c){
    memset(ow,0,sizeof(ow));
    for(int j=0;j<=20;j++)
        if(c&(1<<j)) ow[j]=-1;
    addx(col,v);
    zt[col]--,suby(col,v);
    memset(ow,0,sizeof(ow));
    if(rt1[col]&&df1[v]+1<=df2[v]) search1(1,n,df1[v]+1,df2[v],rt1[col]);
    if(rt2[col]) search2(1,n,df1[v],df1[v],rt2[col]);
    long long oop=searchc(col,v,0);
    for(int j=0;j<=20;j++)
        if(c&(1<<j))
            s[j][col]--,ans-=(1ll<<j)*(zt[col]-s[j][col]),ans+=(1ll<<j)*(oop-ow[j]);
        else
            ans-=(1ll<<j)*s[j][col],ans+=(1ll<<j)*ow[j];
}
int main(){
//    freopen("in.txt","r",stdin);
//    freopen("c.txt","w",stdout);
    int t=read(); int a,b;
    while(t--){
        n=read(),q=0,ans=0;
        for(int i=1;i<=k;i++){
            ch[i][0]=ch[i][1]=0,va[i]=0,og[i]=0;
        }
        for(int i=1;i<=qt;i++){
            for(int j=0;j<=20;j++) req[i][j]=0;
        }
        qt=0,k=0;
        for(int i=1;i<=n;i++){
            col[i]=read(),df1[i]=df2[i]=0;
            for(int j=0;j<=20;j++) s[j][i]=0;
            zt[i]=rt1[i]=rt2[i]=rt1[i]=rt2[i]=0;
        }
        for(int i=1;i<=n;i++) vx[i]=read(),v[i].resize(0),df1[i]=0,df2[i]=0;
        for(int i=1;i<n;i++) a=read(),b=read(),v[a].push_back(b),v[b].push_back(a);
        dfs(1);
        for(int i=1;i<=n;i++)
            adx(col[i],i,vx[i]);
        write(ans),putchar('\n'),m=read();
        while(m--){
            int op=read(),x=read(),t=read();
            if(op==1){
                sux(col[x],x,vx[x]);
                vx[x]=t,adx(col[x],x,t);
            }
            else{
                sux(col[x],x,vx[x]);
                col[x]=t,adx(col[x],x,vx[x]);
            }
            write(ans),putchar('\n');
        }
    }
}