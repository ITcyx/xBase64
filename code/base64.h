#pragma once
#ifndef XBASE64_H
#define XBASE64_H
#include"code.h"

#include<string>

namespace x
{
	bool fbase64(const std::string&, const std::string&, const int& = code::CRLF);
	bool dfbase64(const std::string&, const std::string&);
	bool sbase64(const char* const, const int&, char*&, int&);
	bool dsbase64(const char* const, const int&, char*&, int&);
	bool sbase64(const unsigned char* const, const int&, unsigned char*&, int&);
	bool dsbase64(const unsigned char* const, const int&, unsigned char*&, int&);
	bool sbase64(const std::string&, std::string&);
	bool dsbase64(const std::string&, std::string&);
}

#endif
