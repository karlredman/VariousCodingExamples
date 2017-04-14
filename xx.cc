#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	char *p_c = new char[256];
	cout << "sizeof p_c =" << sizeof(p_c) << endl;

	delete p_c;

	return 0;
}
