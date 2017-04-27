#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

class CPassWord
{
public:
	CPassWord(){ m_strPwd = ""; length = 0; }
	void InputPassword()
	{
		char temp_c;
		while (true) 
		{
			temp_c = _getch();
			if (temp_c != char(13))
			{
				switch (temp_c)
				{
				case 8:
					if (length != 0)
					{
						cout << "\b \b";
						m_strPwd = m_strPwd.substr(0, length-1);
						length--;
					}
					break;
				default:
					cout << "*";
					m_strPwd += temp_c;
					length++;
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
	string GetPassword()
	{
		return m_strPwd;
	}

private:
	string m_strPwd;
	int length;
};