#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long

char str[101];
int getn(char ch){
    if(ch>='0'&&ch<='9')return ch-'0';
    else return ch-'A'+10;
}
int getnum(int l,int r,int R){
    int tot=0;
    for(int i=l;i<=r;i++)
        tot=tot*R+getn(str[i]);
    return tot;
}
signed main(){
    while(scanf("%s",str+1)!=EOF){
        int nl=strlen(str+1);
        int p=0,eq=0,ans=2;
        for(int i=1;i<=nl;i++){
            if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'){
                p=i;
            }
            else if(str[i]=='='){
                eq=i;
            }
            else{
                ans=std::max(ans,getn(str[i])+1);
            }
        }
        bool cando=0;
        for(int r=ans;r<=16;r++){
            int v1=getnum(1,p-1,r),v2=getnum(p+1,eq-1,r),v3=getnum(eq+1,nl,r);
            if(str[p]=='+'){
                if(v1+v2==v3){
                    printf("%d\n",r);
                    cando=1;
                    break;
                }
            }
            else if(str[p]=='-'){
                if(v1-v2==v3){
                    printf("%d\n",r);
                    cando=1;
                    break;
                }
            }
            else if(str[p]=='/'){
                if(1ll*v1==1ll*v2*v3){
                    printf("%d\n",r);
                    cando=1;
                    break;
                }
            }
            else if(str[p]=='*'){
                if(1ll*v1*v2==1ll*v3){
                    printf("%d\n",r);
                    cando=1;
                    break;
                }
            }
        }
        if(!cando)puts("-1");
    }
} 