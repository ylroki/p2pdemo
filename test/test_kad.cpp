#include "kad.h"
#include "file_system.h"
#include "config.h"

CConfig g_Config;
CFileSystem g_FileSystem;
int main()
{
	std::string configName = "config/client.conf";
	g_Config.Init(configName.c_str());
	g_FileSystem.Start(&g_Config);
	Sleep(1000);
	CKad kad(&g_Config, &g_FileSystem);
	kad.Start();
	Sleep(5000);
	kad.Stop();
	g_FileSystem.Stop();
	return 0;
}
