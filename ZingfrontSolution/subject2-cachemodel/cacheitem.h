#include <iostream>
#include <random>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

//cache��Ľṹ����
struct CacheItem{
	int Id;
	int age;
	CacheItem *next;
	CacheItem(int id, int age):Id(id),age(age),next(NULL){ }
};

//cacheģ��
//��cache����������д�������100��
class CacheModel{
public:
	CacheModel(int x) :m_nowsize(x),m_maxid(x-1){ _initcache(); }
	void AddCacheItem();//�����λ�ò���һ��item
	void DeleteCacheItem();
	void Running();
	void _PrintCacheItems();
private:
	CacheItem *m_CacheHead;//cache ��ͷָ��
	int m_nowsize;//cache��ǰʹ����
	int m_maxid;
	void _initcache();//�����ʼ��cache
	void _InsertItem(int i,CacheItem *item);//ɾ����iλ�õĽڵ�
};
//��ʼ��cacheģ��
void CacheModel::_initcache()
{
	//��ʼ��50��item
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
//��iλ�ò���item
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
//��cache�в���һ��item
void CacheModel::AddCacheItem()
{
	if (m_nowsize == 100)//cache �Ѿ�������Ҫ��̭һ����Ȼ���ټ���
	{
		DeleteCacheItem();
	}
	unsigned seed1 = chrono::system_clock::now().time_since_epoch().count();
	minstd_rand0 g1(seed1);
	int pos = g1() % m_nowsize;
	CacheItem *temp = new CacheItem(++m_maxid, 1);
	_InsertItem(pos, temp);
}
//��cache����̭һ���age����10������������û�д���10����̭��һ����
//��һ�֣�û��Ҳû�д���10�Ĳ���̭��
void CacheModel::DeleteCacheItem()
{
	//�ȱ��������ִ��cache�ҵ�һ��age����10����̭��
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
	if (isfind == false && m_nowsize == 100)//�Ѿ����ˣ�����û���ҵ�age����10�ģ���̭��һ��
	{
		m_CacheHead = m_CacheHead->next;
		delete[] pnow;
		--m_nowsize;
	}
}
void CacheModel::_PrintCacheItems()
{
	cout << "��ǰcache����:" << m_nowsize << endl;
	CacheItem * pnow = m_CacheHead;
	while (pnow)
	{
		cout <<'('<< pnow->Id << ',' << pnow->age << ")->";
		pnow = pnow->next;
	}
	cout <<"NULL" <<endl;
}
//cache ÿ�����һ��age
void CacheModel::Running()
{
	CacheItem *pnow = m_CacheHead;
	while (pnow)
	{
		pnow->age = pnow->age + 1;
		pnow = pnow->next;
	}
}