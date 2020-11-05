#include<bits/stdc++.h>
const int N=1e6+10;
int T,n,top,stk[N],w0[N],w1[N],h0[N],h1[N];
char s[N];
inline bool check(int i,int j,int len){
    if(((h0[i+len-1]-(long long)h0[i-1]*w0[len])-(h0[j+len-1]-(long long)h0[j-1]*w0[len]))%1000000009)return false;
    // if(((h1[i+len-1]-(long long)h1[i-1]*w1[len])-(h1[j+len-1]-(long long)h1[j-1]*w1[len]))%1000000007)return false;
    return true;
}
inline int cp(int i,int ie,int j,int je){
    int len=std::min(ie-i+1,je-j+1);
    int l=1,r=len,mid,res=0;
    while(l<=r){
        mid=(l+r)>>1;
        if(check(i,j,mid)){
            l=mid+1,res=mid;
        }else{
            r=mid-1;
        }
    }
    // printf("cp %d %d %d %d : %d %d\n",i,ie,j,je,res,res==len?ie-i<je-j:s[i+res]<s[j+res]);
    return res==len?ie-i<je-j:s[i+res]<s[j+res];
}
int main(){
#ifdef memset0
    freopen("2.in","r",stdin);
    freopen("1.out","w",stdout);
#endif
    w0[0]=w1[0]=1;
    for(int i=1;i<N;i++){
        w0[i]=(long long)w0[i-1]*131131%1000000009;
        // w1[i]=(long long)w1[i-1]*131131%1000000007;
    }
    for(scanf("%d",&T);T--;){
        scanf("%s",s+1),n=strlen(s+1),s[n+1]=0;
        for(int i=1;i<=n;i++){
            h0[i]=((long long)h0[i-1]*131131+s[i])%1000000009;
            // h1[i]=((long long)h1[i-1]*131131+s[i])%1000000007;
        }
        int tmp=1,ans=0;
        top=0;
        for(int i=1;i<=n;i++){
            stk[++top]=i;
            while(top>1){
                if(cp(stk[top-1],i,stk[top],i)){
                    top--;
                }else{
                    break;
                }
            }
            // printf("%d\n",stk[top]);
            ans=(ans+(long long)tmp*stk[top])%1000000007;
            tmp=(long long)tmp*1112%1000000007;
        }
        printf("%d\n",ans);
    }
    // fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
}