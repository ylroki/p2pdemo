#include "command.h"
// Client foreground process send to Client background process.
const char* g_LocalCommand[] = {"stop", "download"};

bool IsLocalCommand(const char* command)
{
	int size = sizeof(g_LocalCommand) / sizeof(char*);
	for (int i = 0; i < size; ++i)
		if (strcmp(command, g_LocalCommand[i]) == 0)
			return true;
	return false;
}

int GenerateCommand(char* buf, char id, ...)// parameter in host byte order
{	
	va_list ap;
	va_start(ap, id);
	switch (id)
	{
	case 0x01:
		{
			unsigned short port = static_cast<unsigned short>(va_arg(ap, unsigned long));
			unsigned long nHash = va_arg(ap, unsigned long);
			unsigned char* pHash = va_arg(ap, unsigned char*);
			CMemoryStream stream(buf, 0);
			stream.WriteInteger<char>(0x01);
			stream.WriteInteger<unsigned short>(htons(port));
			stream.WriteInteger<unsigned long>(htonl(nHash));
			stream.WriteBuffer(pHash, nHash*16);
			return stream.GetSize();
		}
	default:	
		{
			break;
		}
	}
	va_end(ap);
}
