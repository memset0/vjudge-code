#include<bits/stdc++.h>
// template<class T> inline void read(T &x){
//   x=0; register char c=getchar(); register bool f=0;
//   while(!isdigit(c))f^=c=='-',c=getchar();
//   while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
// }
// inline void read(char *s,int &n){
//   n=0; char c=getchar();
//   while(!isupper(c))c=getchar();
//   while(isupper(c))s[n++]=c,c=getchar();
// }
const int N=410;
int T,n,m,q,x,y,l,r,len,til,a[N][N],cnt[N*N],que[N*N];
char s[4000010];
bool tag[N][N];
inline void updmax(int &a,int b){if(b>a)a=b;}
inline void updmin(int &a,int b){if(b<a)a=b;}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  scanf("%d",&T);
  while(T--){
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)
      for(int j=1;j<=m;j++){
        scanf("%d",&a[i][j]);
      }
    for(int i=1;i<=q;i++){
      scanf("%d%d%s",&x,&y,s),len=strlen(s);
      int lx=n+1,ly=m+1,rx=-1,ry=-1;
      for(int i=0;i<len;i++){
        switch(s[i]){
          case 'L':updmin(lx,x),updmax(rx,x),tag[x][y]=1,x--;break;
          case 'R':x++,updmin(lx,x),updmax(rx,x),tag[x][y]=1;break;
          case 'D':updmin(ly,y),updmax(ry,y),y--;break;
          case 'U':y++,updmin(ly,y),updmax(ry,y);break;
        }
      }
      ly--;
      int ans=0;
      til=0;
      for(int fl,i=lx;i<=rx;i++){
        fl=0;
        for(int j=ry;j>=ly;j--){
          fl^=tag[i][j],tag[i][j]=0;
          if(fl&&!cnt[a[i][j]]){
            ans++;
            cnt[a[i][j]]=1;
            que[til++]=a[i][j];
          }
        }
      }
      for(int i=0;i<til;i++){
        cnt[que[i]]=0;
      }
      printf("%d\n",ans);
    }
  }
}