#include<bits/stdc++.h>
const int N=5001,L=12,set[]={1,1,4,5,1,4,1,9,1,9};
int T,n,s[L],ans[N];
std::bitset<N> f[L][L];
inline void upd(const std::bitset<N> &a,const std::bitset<N> &b,std::bitset<N> &c){
    for(int i=0;i<N;i++)if(a[i]){
        c|=b<<i;
        // for(int j=0;i+j<N;j++)c[i+j]=c[i+j]|b[j];
        for(int j=0;i*j<N;j++)c[i*j]=c[i*j]|b[j];
    }
}
int main(){
#ifdef memset0
    freopen("1.in","r",stdin);
#endif
    for(int i=0;i<L;i++)s[i]=set[i%10];
    for(int i=0;i<L;i++){
        f[i][i].set(s[i]);
        if(i+1<L&&s[i]*10+s[i+1]<N)f[i][i+1].set(s[i]*10+s[i+1]);
        if(i+2<L&&s[i]*100+s[i+1]*10+s[i+2]<N)f[i][i+2].set(s[i]*100+s[i+1]*10+s[i+2]);
        if(i+3<L&&s[i]*1000+s[i+1]*100+s[i+2]*10+s[i+3]<N)f[i][i+3].set(s[i]*1000+s[i+1]*100+s[i+2]*10+s[i+3]);
    }
    for(int r=0;r<L;r++){
        for(int l=r-1;l>=0;l--)
            for(int k=l;k<r;k++){
                upd(f[l][k],f[k+1][r],f[l][r]);
            }
        for(int i=0;i<N;i++)if(!ans[i]&&f[0][r][i])ans[i]=r+1;
    }
    // for(int i=0;i<N;i++)printf("%d%c",ans[i]," \n"[i+1==N]);
    // for(int i=1;i<N;i++)if(!ans[i])printf("%d\n",i);
    int min=*std::min_element(ans+1,ans+N);
    int max=*std::max_element(ans+1,ans+N);
    // printf("min=%d max=%d\n",min,max);
    for(std::cin>>T;T--;)std::cin>>n,std::cout<<(ans[n]?ans[n]:-1)<<std::endl;;
}