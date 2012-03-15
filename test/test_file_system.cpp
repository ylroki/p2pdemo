#include "file_system.h"
#include "config.h"

int main()
{
	CConfig config;
	config.Init("config/client.conf");
	CFileSystem fs;
	fs.Start(&config);

	while (true)
	{
		if (Kbhit() != -1)
		{
			fs.Stop();
			break;
		}
		Sleep(100);
	}
	return 0;
}
