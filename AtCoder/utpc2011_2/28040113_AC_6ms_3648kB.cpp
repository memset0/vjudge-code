#include<bits/stdc++.h>
using namespace std;
string iwi;	//定义字符串，不限长度
bool flag;
int len,sum;
int main(){
	cin>>iwi;//读入字符串，string类型可以直接cin
	len=iwi.size();//得到字符串长度
	for(int i=0;i<=(len-1)/2;i++){ //这个终止条件很重要，我第一次也不小心写成li<=len/2,我错的这个单单适用于奇数情况，偶数会多一个
		flag=false; //预设状态是要改
		if(iwi[i]==iwi[len-i-1]&&iwi[i]=='i')	flag=true;	//看看是不是对称，这两个是看是不是i或w的回文，是则改为不需改的状态；顺便说下有一条题解错就错在他没有判断相等是不是不是括号，这样ta用或的话就会bug
		else if(iwi[i]==iwi[len-i-1]&&iwi[i]=='w')	flag=true;
		else if(iwi[i]=='('&&iwi[len-i-1]==')')	flag=true;//这两个是判断是否是成对的括号，后一个也是，只不过是反过来而已
		else if(iwi[i]==')'&&iwi[len-i-1]=='(')	flag=true;
		if(!flag)	sum++;//如果不回文，动一下其中一个，不考虑全改，因为字符均不可能不在i，w和括号之间
	}
	cout<<sum<<"\n";//漂亮的输出有换行才完美
	return 0;
}