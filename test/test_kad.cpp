#include "kad.h"

int main()
{
	CKad kad(NULL);
	kad.Start();
	Sleep(5);
	kad.Stop();
	return 0;
}
