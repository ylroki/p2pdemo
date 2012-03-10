#include "upload_file.h"
#include "config.h"

int main()
{
	CConfig config;
	config.Init("config/client.conf");
	CUploadFile upload;
	upload.Start(&config);
	Sleep(1000);
	upload.Stop();
	return 0;
}
