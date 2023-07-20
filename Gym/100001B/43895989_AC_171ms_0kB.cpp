#include<cstdio>
#include<cctype>
const char *Const=" ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char s[101];
void Solve1() {
    int i=0,j=0,num1=0,num2=0;
    int t[101];
    for(++i;isdigit(s[i]);++i)
        (num2*=10)+=s[i]-'0';
    for(++i;s[i];++i)
        (num1*=10)+=s[i]-'0';
    for(;num1;num1=num1/26-!(num1%26)) {    //特判
        if(num1%26)
            t[++j]=num1%26;
        else
            t[++j]=26;    //特判
    }
    for(;j;--j)
        putchar(Const[t[j]]);
    printf("%d\n",num2);
}
void Solve2() {
    int i=0,num1=0,num2=0;
    for(;isupper(s[i]);++i)
        (num2*=26)+=s[i]-'A'+1;    //注意这个加一，A表示1而不是0
    for(;s[i];++i)
        (num1*=10)+=s[i]-'0';
    printf("R%dC%d\n",num1,num2);
}
int main() {
    int n;
    bool flag;
    for(scanf("%d",&n);n;--n) {
        scanf("%s",s);
        flag=0;
        for(int i=0;s[i]&&!flag;++i)
            if(i&&isdigit(s[i-1])&&isupper(s[i]))
            //这里利用了两种表示法的特殊性来判断是哪种表示法，(R,C)表示法在数字后有可能有字母，然而Excel表示法一定不可能
                flag=1;
        if(flag)
            Solve1();
        else
            Solve2();
    }
    return 0;
}//123131212312312312321313213213123132132