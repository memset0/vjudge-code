#include<bits/stdc++.h>//偷懒专用库 
#define ll long long
#define INF 15200
#define MAXN 99999//宏定义 
using namespace std;

inline int read(){
  char c=getchar();int x=0,f=1;
  while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
  while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
  return x*f;
}//这里是快读，可以提供借鉴，忽略掉也无所谓的 

struct love
{
	int milk;
	int time;
}you[INF];//定义一个机构体 

int cmp(love x,love y)
{
	return x.milk>y.milk;
}//结构体排序，按照加仑牛奶的价值从大到小排，先处理价值大的，保证不能挤得越小越好 

int n,ans,tot;
int a[INF];//判断这个时间点挤没有挤过奶 

int main()//主函数部分 
{
    n=read();//读入 
    for(int i=1;i<=n;++i)
	  {
	  	you[i].milk=read();
	  	you[i].time=read();
      } //读入加仑牛奶价值和挤得最后时间 
	sort(you+1,you+1+n,cmp);//排序 
	for(int i=1;i<=n;++i)//判断是否能挤 
	 {
	 	tot=0;//这是一个判断用的东西，待会就明白了 
	 	for(int j=you[i].time;j>=1;--j)//从他的最大时间开始，一直到一，看看有没有一个时间点没挤过 
	 	 {
	 	 	if(a[j]==0)//如果这个点没挤过，就代表当前的牛奶可以被挤 
	 	 	 {
	 	 	 	a[j]=1;//把这个点变成挤过 
	 	 	 	tot=1;//然后标记成挤过 
	 	 	 	break;//跳出循环 
			 }//因为此时找到是最晚能挤的时间，所以不会影响以后的选择 
		 }
		if(tot==1)
		 ans+=you[i].milk;//如果标记过，证明奶挤过，所以答案加上价值 
     }
    cout<<ans;//输出
	return 0;//养成好习惯，从你我做起 
}