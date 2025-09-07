#include "Pipe.h"
#include "Manager.h"
#include <iostream>
#include <thread>

using namespace std;

void runGraphics()
{
	
//	system("d:\\users\\user-pc\\desktop\\e.exe.lnk");
		

}
int main()
{
	srand(time_t(NULL));

	thread t(runGraphics);
	t.detach();
	Sleep(1000);

	Pipe p;
	bool isConnect = p.connect();

	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return 0;
		}
	}

	Manager mgr(p);

	mgr.playGame();

	p.close();

	return 0;
}