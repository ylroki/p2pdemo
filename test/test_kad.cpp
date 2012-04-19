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
	CKad kad(&g_Config, &g_FileSystem);
	kad.Start();
	Sleep(5000);
	kad.Stop();
	return 0;
}
