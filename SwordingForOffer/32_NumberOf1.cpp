#include <iostream>
#include <string.h>
using namespace std;

int PowerBase10(int n)
{
	int result = 1;
	for(int i=0; i<n; ++i)
		result *= 10;

	return result;
}
int NumberOf1(const char* strN)
{
	if(!strN || *strN < '0' || *strN > '9' || *strN == '\0')
		return 0;

	int first = *strN - '0';
	int length = strlen(strN);

	if(length == 1 && first == 0)
		return 0;
	if(length == 1 && first > 0)
		return 1;

	//位于最高位的1的数目
	int numFistDigit = 0;
	if(first > 1)
		numFistDigit = PowerBase10(length-1);
	else if(first == 1)
		numFistDigit = atoi(strN+1) + 1;

	//除了第一位之外的1的数目
	int numOtherDigits = first*(length-1)*PowerBase10(length-2);
	//递归求剩下的数字
	int numRecursive = NumberOf1(strN+1);

	return (numFistDigit+numOtherDigits+numRecursive);
}
int NumOf1andN(int n)
{
	if(n<=0)
		return 0;

	char strN[50];
	sprintf(strN, "%d", n);
	return NumberOf1(strN);
}
int main()
{
	int num;
	while(cin >> num){
		cout << NumOf1andN(num) << endl;
	}
	return 0;
}