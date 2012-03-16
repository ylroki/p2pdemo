#ifndef __INCLUDE_MD5_HEADER_H__
#define __INCLUDE_MD5_HEADER_H__
#include "linux_header.h"
#include <openssl/md5.h>

bool MD5File(const char* filename, unsigned char* hexHash);

bool MD5File(const std::string filename, unsigned char* hexHash);

#endif
