#include "mimabook.pb.h"
#include "CPassWord.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

enum STATUS{SUCCESS ,FAILD};
const string inifile = ".\\ini.bin";

mimabook::myprivatebook passwordbook;//全局变量，保存密码本的信息

int checkUser()
{
	cout << "verify your login name and password" << endl;
	string uname, upass;
	cout << "Input name: ";
	cin >> uname;
	cout << "Input password: ";
	CPassWord cpw;
	cpw.InputPassword();
	cout << endl;
	upass = cpw.GetPassword();
	if (passwordbook.username() != uname || passwordbook.userpass() != upass)
	{
		cout << "user name or password error, please train again" << endl;
		return FAILD;
	}
	return SUCCESS;
}
void AddItemDefault(mimabook::mimacode *pinfo)//添加默认信息
{
	pinfo->set_app("appname");
	pinfo->set_name("username");
	pinfo->set_password("password");
	pinfo->set_priority(0);
}
void AddItem(mimabook::mimacode *pinfo)//由用户输入添加信息
{
	string appname,username,userpassword;
	int privo=1;
	//Read from user input
	cout << "Input application name: ";
	cin >> appname;
	cout << "Input username: ";
	cin >> username;
	cout << "Input user password: ";
	//getline(cin, userpassword);
	cin >> userpassword;
	//Write to protobuf
	pinfo->set_app(appname);
	pinfo->set_name(username);
	pinfo->set_password(userpassword);
	pinfo->set_priority(privo);

}
void ListAllInfo(mimabook::myprivatebook& pbook)//列出所有的密码信息
{
	cout.flags(ios::left);
	cout << "------------------- Your Password ---------------------------" << endl;
	for (int i = 0; i < pbook.mimainfo_size(); i++)
	{
		const mimabook::mimacode& codeinfo = pbook.mimainfo(i);
		cout << left << setw(15) << codeinfo.app() << left << setw(25) << codeinfo.name()<<left<<setw(25)
			<< codeinfo.password() << endl;
		cout << "-------------------------------------------------------------" << endl;
	}
}
void ChangeInfo(mimabook::myprivatebook &pinfo)//改变某一条密码信息
{
	string strnpwd,name;
	cout << "Input you want to change: ";
	cin >> name;
	int i;
	for (i = 0; i < pinfo.mimainfo_size(); i++)
	{
		mimabook::mimacode *codeinfo= pinfo.mutable_mimainfo(i);

		if (name == codeinfo->app()) //Find change
		{
			cout << "new password: ";
			cin >> strnpwd;
			codeinfo->set_password(strnpwd);
			cout << "Done!" << endl;
			break;
		}
	}
	if (i == pinfo.mimainfo_size())
	{
		cout << "not found changed name" << endl;
	}
	
}
//Main function UI
void MainUI()
{
	int num;
	cout << "Make your choise:" << endl;
	cout << "--- 0.Exit ---" << endl;
	cout << "--- 1.Add ----" << endl;
	cout << "--- 2.List ---" << endl;
	cout << "-- 3.Modify --" << endl;
	cout << "your input: ";
	cin >> num;
	
	while (true && num!=0)
	{
		system("cls");
		switch (num)
		{
		case 1:
			AddItem(passwordbook.add_mimainfo());
			break;
		case 2:
			ListAllInfo(passwordbook);
			break;
		case 3:
			ChangeInfo(passwordbook);
			break;
		default:
			break;
		}
		cout << "Make your choise:" << endl;
		cout << "--- 0.Exit ---" << endl;
		cout << "--- 1.Add ----" << endl;
		cout << "--- 2.List ---" << endl;
		cout << "-- 3.Modify --" << endl;
		cout << "your input: ";
		cin >> num;
		
	}
}
//检测是否为第一次运行
int CheckFirstRun()
{
	fstream infile(inifile.c_str(), ios::in | ios::binary);
	if (!infile) //没有配置文件，写入默认信息
	{
		cout << "First Run the application will init something ..." << endl;
		fstream outfile(inifile.c_str(), ios::out | ios::trunc | ios::binary);
		mimabook::myprivatebook defaultinfo;
		defaultinfo.set_username("admin");
		defaultinfo.set_userpass("admin");
		AddItemDefault(defaultinfo.add_mimainfo());
		if (!defaultinfo.SerializeToOstream(&outfile))
		{
			cout << "init error ..." << endl;
			return FAILD;
		}
		else
		{
			cout << "init success!" << endl;
		}
	}
	else 
	{
		cout << "======== Welcome to back ========" << endl;
		//passwordbook.ParseFromIstream(&infile);
	}
	return SUCCESS;
}
int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	static int trytime = 0;

	if (CheckFirstRun()==FAILD) 
	{
		cout << "RUN Error!" << endl;
		return 1;
	}
	fstream infile(inifile.c_str(), ios::in | ios::binary);
	passwordbook.ParseFromIstream(&infile);
	infile.close();
	//三次机会验证登录用户和密码
	while (trytime < 3 ) {
		if (checkUser() == FAILD) trytime++;
		else break;
	}
	if (trytime == 3) return 1;
	
	MainUI();

	fstream outfile(inifile.c_str(), ios::out | ios::binary | ios::trunc);
	passwordbook.SerializeToOstream(&outfile);
	outfile.close();

	system("pause");
	return 0;
}