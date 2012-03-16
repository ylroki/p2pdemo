#ifndef __INCLUDE_MD5_HEADER_H__
#define __INCLUDE_MD5_HEADER_H__
#include "linux_header.h"
#include <openssl/md5.h>

bool MD5File(const char* filename, unsigned char* hexHash);

bool MD5File(const std::string filename, unsigned char* hexHash);

void MD52Hex(const char* md5, unsigned char* hex);

void Hex2MD5(const unsigned char* hex, char* md5);
#endif
