#include "string_header.h"

std::string TrimString(std::string orgString)
{
	int left = 0;
	int right = orgString.size() - 1;
	while (left <= right)
	{
		if (orgString[left] == ' ' ||
			orgString[left] == '\n')
		{
			++left;
			continue;
		}
		if (orgString[right] == ' ' ||
			orgString[right] == '\n')
		{
			--right;
			continue;
		}
		break;
	}
	int len = right - left + 1;
	if (len > 0)
		return orgString.substr(left, len);
	else
		return "";
}

