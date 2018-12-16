#include <iostream>
#include "cstring"

using namespace std;

int main(int argc,char *argv[])
{
	char *ch = "你好";
	char *ch1= "hello world!";
	cout << ch << endl;
	cout << strlen(ch) << endl;
	cout << ch1 << endl;
	cout << strlen(ch1) << endl;
	return 0;
}