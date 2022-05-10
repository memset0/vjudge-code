// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std ;
int main()
{
    int nDate1 = 0 ;
    int nDate2 = 0 ;
    cin>>nDate1>>nDate2 ;
    int nResult = 0 ;
    bool bYear = false ;//是否闰年 
    int nYear = 0 ;
    int nMonth = 0 ;
    int nDay = 0 ;
    char str[10] ;
    for(int i = nDate1;i <= nDate2;i++)
    {
    	itoa(i,str,10) ;
    	bYear = false ;
        nYear = i / 10000 ;
        nMonth = i % 10000 / 100 ;
        nDay = i % 100 ; 
        if(nMonth == 0 || nDay == 0 || nMonth > 12 || nDay > 31)
        {
            continue ;
        }
        if((nYear % 4 == 0 && nYear % 100 != 0) || (nYear % 400 == 0))
        {
            bYear = true ;
        }
        if(nMonth == 2)
        {
            if(!bYear && nDay > 28)
            {
                continue ;
            }
            else if(bYear && nDay > 29)
            {
                continue ;
            }
        }
        else if(nMonth == 4 || nMonth == 6 || nMonth == 9 || nMonth == 11)
        {
            if(nDay > 30)
            {
                continue ;
            }
        }
        if(nYear / 1000 == nDay % 10 && nYear / 100 % 10 == nDay / 10 && nYear / 10 % 10 == nMonth % 10 && nYear % 10 == nMonth / 10)
        {
        	//cout<<i<<endl ;
            nResult++ ;
        }
    }
    cout<<nResult<<endl ;
    return 0 ;
}