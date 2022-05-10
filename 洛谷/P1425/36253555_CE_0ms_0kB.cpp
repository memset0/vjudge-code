#include<cstdio>//头文件
int main()
{
    int h1,h2,m1,m2;
    scanf("%d %d %d %d",&h1,&m1,&h2,&m2);
    if(m2<m1)//如果不够减
    {
        m2+=60;//退位
        h2--;
    }
    m1=m2-m1;//分减分
    h1=h2-h1;/;/时减时
    printf("%d %d",h1,m1);
    return 0;
}