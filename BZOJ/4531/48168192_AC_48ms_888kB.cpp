// tle


#include<iostream>
#include<cstring>
#include<cstdio>
#define P 1000000007
using namespace std;
int f[25][35][35][2],map[50][50],n,m,x,y,ans,num;
char ch[30];
bool cal(int x){return ch[x]=='+'||ch[x]=='-'||ch[x]=='*'||ch[x]=='/';}
bool isnum(int x){return ch[x]>='0'&&ch[x]<='9';}
int dp(int x,int k,int c,int t){
  if (k==num) return ((c==0)&&(!cal(x)));
  int now=f[x][k][c][t];
  if (now>=0) return now;
  now=0;
  for (int i=1;i<=n;i++)
    if (map[x][i]){
      if (isnum(i)){
        if (isnum(x)){
          if (!t) (now+=dp(i,k+1,c,0))%=P;	
        }
        else if (cal(x)||ch[x]=='(') (now+=dp(i,k+1,c,ch[i]=='0'))%=P;   
      }
	  else if (ch[i]=='('||ch[i]==')'){
	     if (ch[i]=='('&&(ch[x]=='('||cal(x))) (now+=dp(i,k+1,c+1,0))%=P;
	     else if (ch[i]==')'&&c&&(isnum(x)||ch[x]==')')) (now+=dp(i,k+1,c-1,0))%=P; 
	  }   
	  else{
	    if (isnum(x)) (now+=dp(i,k+1,c,0))%=P;
	    if (ch[x]==')'||(ch[x]=='('&&ch[i]=='-')) (now+=dp(i,k+1,c,0))%=P;
	  }
    }
  f[x][k][c][t]=now;
  return now;
}
int main(){
  scanf("%d%d%d",&n,&m,&num);
  scanf("%s",ch+1);
  for (int i=1;i<=m;i++){
    scanf("%d%d",&x,&y);
    map[x][y]=map[y][x]=1;
  }	
  memset(f,-1,sizeof(f));
  for (int i=1;i<=n;i++){
    if (ch[i]=='(') (ans+=dp(i,1,1,0))%=P;
    if (ch[i]=='-') (ans+=dp(i,1,0,0))%=P;
    if (ch[i]>='0'&&ch[i]<='9')(ans+=dp(i,1,0,ch[i]=='0'))%=P;
  }
  cout<<ans<<endl; 
}
