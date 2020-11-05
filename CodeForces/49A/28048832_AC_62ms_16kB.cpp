#include <bits/stdc++.h>

std::string str;
int main() {
    std::getline(std::cin, str);
    int len=str.length()-1;
    while (!isalpha(str[len])) len--;
    if (str[len]=='A'||str[len]=='E'||str[len]=='I'||str[len]=='O'||str[len]=='U'||str[len]=='Y'||str[len]=='a'||str[len]=='e'||str[len]=='i'||str[len]=='o'||str[len]=='u'||str[len]=='y') printf("YES");//判断是否为元音字母
    else printf("NO");
}