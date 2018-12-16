#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;

class CRand
{
public:
	 CRand()
	 {
	 	srand(time(NULL));
	 	this->level = 0;
	 	this->cnt = 1;
	 	this->yes = false;
	 	this->flag = 1;
	 }
	 int getrand()
	 {
	 	return rand() % 100;
	 }
	 bool setrand(int a = 0)
	 {
	 	if(getrand() < a)
	 		this->yes = true;
	 	else
	 		this->yes = false;
	 }
	 void fun(int a = 15)
	 {
	 	while(1)
	 	{
	 		if(yes)
	 		{
	 			level++;
	 			func();
	 			if(a == level)
	 			{
		 			cout << level << " " << flag << " " << cnt << " ";
		 			//level = 0;
		 			printf("%f\r",(double)flag/cnt);
		 			flag++;
		 			//cnt++;
		 		}
	 		}
	 		else if(level < 9)
	 		{
	 			func();
	 			//cout << level << " ";
	 		}
	 		else
	 		{
	 			//cout << level << " ";
	 			cnt++;
	 			level = 0;
	 			func();
	 		}
	 	}
	 }
	 void func()
	 {
	 	switch (level)
	 	{
	 		case 0:
	 		case 1:
	 		case 2:
	 			setrand(100);
	 			break;
	 		case 3:
	 			setrand(90);
	 			break;
	 		case 4:
	 			setrand(80);
	 			break;
	 		case 5:
	 			setrand(71);
	 			break;
	 		case 6:
	 			setrand(63);
	 			break;
	 		case 7:
	 			setrand(55);
	 			break;
	 		case 8:
	 			setrand(40);
	 			break;
	 		case 9:
	 			setrand(29);
	 			break;
	 		case 10:
	 			setrand(22);
	 			break;
	 		case 11:
	 			setrand(19);
	 			break;
	 		case 12:
	 			setrand(16);
	 			break;
	 		case 13:
	 			setrand(13);
	 			break;
	 		case 14:
	 			setrand(10);
	 			break;
	 		case 15:
	 			//cout << "success!" << endl;
	 			setrand(0);
	 			break;
	 		default:
	 			cout << endl << "error!" << endl;
	 			exit(1);
	 	}
	 }
private:
	int level;
	bool yes;
	int cnt;
	int flag;
};

int main(int argc,char *argv[])
{

	CRand *a = new CRand;
	a->fun(atoi(argv[1]));
	return 0;
}