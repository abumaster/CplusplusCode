#include <iostream>
#include <random>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

//cache项的结构属性
struct CacheItem{
	int Id;
	int age;
	CacheItem *next;
	CacheItem(int id, int age):Id(id),age(age),next(NULL){ }
};

//cache模型
//将cache的容纳总量写死，最多100项
class CacheModel{
public:
	CacheModel(int x) :m_nowsize(x),m_maxid(x-1){ _initcache(); }
	void AddCacheItem();//在随机位置插入一个item
	void DeleteCacheItem();
	void Running();
	void _PrintCacheItems();
private:
	CacheItem *m_CacheHead;//cache 的头指针
	int m_nowsize;//cache当前使用量
	int m_maxid;
	void _initcache();//随机初始化cache
	void _InsertItem(int i,CacheItem *item);//删除第i位置的节点
};
//初始化cache模型
void CacheModel::_initcache()
{
	//初始化50个item
	vector<int> vecrand;
	unsigned seed1 = chrono::system_clock::now().time_since_epoch().count();
	minstd_rand0 g1(seed1);
	vecrand.push_back(g1() % 50);
	for (int i = 0; i < 49; ++i)
	{
		int temp = g1() % 50;
		vecrand.push_back(temp);
	}
	m_CacheHead = new CacheItem(vecrand[0], g1()%10+1);
	CacheItem *pnext = m_CacheHead;
	for (int i = 1; i < 50; ++i)
	{
		CacheItem *nowitem = new CacheItem(vecrand[i], g1() % 10+1);
		pnext->next = nowitem;
		pnext = nowitem;
	}
}
//在i位置插入item
void CacheModel::_InsertItem(int i, CacheItem *item)
{
	int pos = i;
	CacheItem *pnow = m_CacheHead;
	while (pos-- > 0)
	{
		pnow = pnow->next;
	}
	item->next = pnow->next;
	pnow->next = item;
	++m_nowsize;
}
//向cache中插入一个item
void CacheModel::AddCacheItem()
{
	if (m_nowsize == 100)//cache 已经满了需要淘汰一个，然后再加入
	{
		DeleteCacheItem();
	}
	unsigned seed1 = chrono::system_clock::now().time_since_epoch().count();
	minstd_rand0 g1(seed1);
	int pos = g1() % m_nowsize;
	CacheItem *temp = new CacheItem(++m_maxid, 1);
	_InsertItem(pos, temp);
}
//从cache中淘汰一个项，age大于10，或者已满又没有大于10的淘汰第一个，
//另一种：没满也没有大于10的不淘汰？
void CacheModel::DeleteCacheItem()
{
	//先遍历所有现存的cache找到一个age大于10的淘汰掉
	bool isfind = false;
	CacheItem *pnow = m_CacheHead;
	if (pnow && pnow->age > 10) {
		m_CacheHead = pnow->next; 
		delete[]pnow;
		isfind = true;
		--m_nowsize;
	}
	else if (pnow){
		CacheItem *ppre = m_CacheHead;
		pnow = m_CacheHead->next;
		while (pnow){
			if (pnow->age > 10) {
				ppre->next = pnow->next;
				delete[] pnow;
				isfind = true;
				--m_nowsize;
				break;
			}
			pnow = pnow->next;
			ppre = ppre->next;
		}
	}
	if (isfind == false && m_nowsize == 100)//已经满了，并且没有找到age大于10的，淘汰第一个
	{
		m_CacheHead = m_CacheHead->next;
		delete[] pnow;
		--m_nowsize;
	}
}
void CacheModel::_PrintCacheItems()
{
	cout << "当前cache用量:" << m_nowsize << endl;
	CacheItem * pnow = m_CacheHead;
	while (pnow)
	{
		cout <<'('<< pnow->Id << ',' << pnow->age << ")->";
		pnow = pnow->next;
	}
	cout <<"NULL" <<endl;
}
//cache 每秒更新一下age
void CacheModel::Running()
{
	CacheItem *pnow = m_CacheHead;
	while (pnow)
	{
		pnow->age = pnow->age + 1;
		pnow = pnow->next;
	}
}