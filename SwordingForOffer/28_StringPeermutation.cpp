/**
 * 字符串的排列
 * 给几个字符，输出这几个字符的所有排列
 */
#include <iostream>
#include <cstdio>
using namespace std;

static int a=0;
int check(char* pStr)
{
	int num = 0;
	for (int i=0; i<8; i++)
	{
		if(pStr[i] - '0' == i )
			num++;
	}
	if(num > 1)
		return 0;
	return 1;
}
void Permutation(char* pStr, char* pBegin)
{

	if(*pBegin == '\0')
	{
		if(check(pStr) == 1)
			printf("%s\n", pStr);
	}
	else
	{
		a++;
		for(char* pCh=pBegin; *pCh != '\0'; ++pCh)
		{
			char temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;

			Permutation(pStr, pBegin+1);

			temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;
		}
	}
}
void Permutation(char * pStr)
{
	if(pStr == NULL)
		return;

	Permutation(pStr, pStr);
}
int main()
{
	char ch[9]={'0','1','2','3','4','5','6','7', '\0'};
	Permutation(ch);
	printf("%d\n",a );
	return 0;
}