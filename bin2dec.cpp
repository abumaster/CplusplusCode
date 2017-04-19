#include <iostream>
#include <string.h>
using namespace std;

const int LEN = 100;
/**
 * [bin2dec 二进制转换成十进制]
 * @param decnum [十进制数字串]
 * @param n      [二进制1后面的0的个数]
 */
void bin2dec(int *decnum, int n)
{
	int index = LEN-1;
	decnum[index] = 1;
	int jinwei = 0;
	while (n--) //总共几个0
	{
		for(int i = LEN-1; i>=0; i--)
		{
			int nowtemp = 2*decnum[i]+jinwei;
			if(nowtemp>=10)//需要进位
			{
				decnum[i] = nowtemp%10; //改变当前的数值
				jinwei = nowtemp/10; //进位的多少
			}
			else
			{
				decnum[i] = nowtemp;
				jinwei=0;
			}
		}
	}
}
/**
 * 将两个大数合并，放入左边数组
 * @param left  相加结果放入此
 * @param right 数组
 */
void sumbignum(int *left, int *right, int n=LEN)
{
	int jinwei = 0;
	for(int i=n-1; i>=0; i--)
	{
		int temp = left[i]+right[i]+jinwei;//俩数之和加上进位标志
		if(temp >= 10)//需要进位的
		{
			left[i] = temp%10;
			jinwei = temp/10;
		}
		else //不用进位
		{
			left[i] = temp;
			jinwei = 0;
		}
	}
}
void PrintInt(int *arr, int n)
{
	int start = 0;//bug
	for (int i=0; i<n-1; i++)
	{
		int j = i+1;
		if(arr[i]==0 && arr[j]!=0 && !start)
		{
			start = 1;
		}
		if (start)
			cout << arr[j];
	}
	cout << endl;
}
//测试转换
void testzhuanhuan()
{
	for (int i=0; i<11; i++)
	{
		int *decnum = new int[LEN];
		memset(decnum, 0, LEN*sizeof(int));
		bin2dec(decnum, i);
		PrintInt(decnum, LEN);
	}
}
//测试大数相加
void testSum()
{
	int a[5]={1,2,3,4,5};
	int b[5]={6,7,8,9,0};
	sumbignum(a, b, 5);
	for (int i =0; i<5; i++)
		cout<<a[i];
	cout<<endl;
}
void testBin2Decnum()
{
	string strNum;
	while (cin >> strNum)
	{
		//申请一段用于保存结果的空间，长度可以设置，默认100
		int *decnum = new int[LEN];
		memset(decnum, 0, LEN*sizeof(int));
		int len = strNum.size();
		for(int i=len-1; i>=0; i--)
		{
			int *tempnum = new int[LEN];
			memset(tempnum, 0, LEN*sizeof(int));
			if(strNum[i]-'0' == 1)//二进制位为1时，开始计算
			{
				bin2dec(tempnum, len-1-i);//转换
				sumbignum(decnum, tempnum, LEN);
			}
			delete []tempnum;
		}//for
		PrintInt(decnum,LEN);
		delete []decnum;
	}
}
int main()
{
	//testzhuanhuan();
	//testSum();
	testBin2Decnum();
	system("pause");
	return 0;
}