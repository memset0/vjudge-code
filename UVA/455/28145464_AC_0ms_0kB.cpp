#include<cstdio>
#include<cstring>
char ch[110];
int main()
{
	int t;
	//while(~scanf("%d",&t))
	scanf("%d",&t);
	while(t--){
		scanf("%s",ch);
		int len=strlen(ch);
		for(int k,i=1;i<=len;i++){
			if(len%i==0){
				for(k=i;k<len;k++){
					if(ch[k]!=ch[k%i]) break;
				}
				if(k==len){
					printf("%d\n",i);
					break;
				}
			}
		}
		if(t) printf("\n");
	}
	return 0;
}