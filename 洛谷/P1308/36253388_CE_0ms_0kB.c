#include<stdio.h>
#include<string.h>
#include<ctype.h>
void find_word(char word,char txt) { strupr(word); strupr(txt); long wlen=strlen(word),tlen=strlen(txt); int num=0,first=-1;

for(int i=0;i<=tlen-wlen;i++)
{
    int j=0;
    while(j<wlen&&*(txt+i+j)==*(word+j))j++;
    if(j==wlen)
    {
        if(i==0)
        {
            if(!isalpha(*(txt+i+j)))
            {
                num++;
                if(first==-1)
                first=i;
            }
        }
        else 
        {
            if(!isalpha(*(txt+i+j)))
            if(!isalpha(*(txt+i-1)))
            {
                num++;
                if(first==-1)
                first=i;
            }
        }
    }
}
if(num==0)
    printf("-1");
else
    printf("%ld %ld",num,first);
}
char a[1000001],b[11];
int main() {  gets(b); gets(a); find_word(b,a);

return 0;
} 