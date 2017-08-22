#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;
#include "cacheitem.h"

void _TestDelete()
{
	CacheModel cm(50);
	cm._PrintCacheItems();
	for (int i = 0; i < 100; ++i)
	{
		cm.DeleteCacheItem();
		cm.Running();
		cm._PrintCacheItems();
	}
}
void _TestAdd()
{
	CacheModel cm(50);
	cm._PrintCacheItems();
	for (int i = 0; i < 100; ++i)
	{
		cm.Running();
		cm.AddCacheItem();
		cm._PrintCacheItems();
	}
}
//测试cache
void _TestCacheRuning()
{
	CacheModel cm(50);
	unsigned seed1 = chrono::system_clock::now().time_since_epoch().count();
	minstd_rand0 g1(seed1);
	int test_times = 300;
	for (int i = 0; i < 300; ++i)
	{
		/*cm._PrintCacheItems();
		int method = g1() % 2;//随机选择插入和淘汰
		switch (method){
		case 0:
			cm.DeleteCacheItem();
			cm.Running();
			break;
		case 1:
			cm.Running();
			cm.AddCacheItem();
		default:
			break;
		}*/
		cm._PrintCacheItems();
		//每秒进行以下操作，
		cm.DeleteCacheItem();
		cm.Running();
		cm.AddCacheItem();
	}
	cm._PrintCacheItems();
}
int main()
{
	//_TestDelete();
	//_TestAdd();
	_TestCacheRuning();

	system("pause");
	return 0;
}