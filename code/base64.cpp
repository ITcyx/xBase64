#include"base64.h"
#include<fstream>
#include<thread>

static const char base64table[65] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/','=' };

static const unsigned char dbase64table[256]=
{
	64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,64,64,64,62,64,64,64,63,
	52,53,54,55,56,57,58,59,60,61,64,64,64,64,64,64,
	64,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,
	15,16,17,18,19,20,21,22,23,24,25,64,64,64,64,64,
	64,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
	41,42,43,44,45,46,47,48,49,50,51,64,64,64,64,64,
	64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
};

bool x::fbase64(const std::string& sourcepath, const std::string& targetpath, const int& endcode)
{
	std::ifstream a;
	a.open(sourcepath, std::ios::binary);
	if (!a.is_open())
		return false;
	std::ofstream b;
	b.open(targetpath, std::ios::binary);
	if (!b.is_open())
		return false;
	int i, j, x, y, h, k;
	unsigned char c[76];
	unsigned char d[57];
	unsigned char e[4];
	const unsigned char f[2] = { 13,10 };
	while (a.peek() != EOF)
	{
		y = 0;
		for (i = 0; i < 57; ++i)
		{
			if (a.peek() == EOF)
				break;
			a.read((char*)&d[i], 1);
			++y;
		}
		if (y % 3 == 0)
			x = y / 3 * 4;
		else
			x = (y / 3 + 1) * 4;
		for (i = 0; i < y; i += 3)
		{
			if (i + 2 < y)
			{
				e[0] = unsigned char(d[i]) >> 2;
				e[1] = (unsigned char(unsigned char(d[i]) << 6) >> 2) + (unsigned char(d[i + 1]) >> 4);
				e[2] = (unsigned char(unsigned char(d[i + 1]) << 4) >> 2) + (unsigned char(d[i + 2]) >> 6);
				e[3] = unsigned char(unsigned char(d[i + 2]) << 2) >> 2;
			}
			else if (i + 1 < y)
			{
				e[0] = unsigned char(d[i]) >> 2;
				e[1] = (unsigned char(unsigned char(d[i]) << 6) >> 2) + (unsigned char(d[i + 1]) >> 4);
				e[2] = (unsigned char(unsigned char(d[i + 1]) << 4) >> 2);
				e[3] = 64;
			}
			else
			{
				e[0] = unsigned char(d[i]) >> 2;
				e[1] = (unsigned char(unsigned char(d[i]) << 6) >> 2);
				e[2] = 64;
				e[3] = 64;
			}
			for (j = i / 3 * 4; j < i / 3 * 4 + 4; ++j)
				c[j] = base64table[e[j - i / 3 * 4]];
		}
		b.write((char*)c, x);
		switch (endcode)
		{
		case code::CRLF:
			b.write((char*)f, 2);
			break;
		case code::CR:
			b.write((char*)(&f[0]), 1);
			break;
		case code::LF:
			b.write((char*)(&f[1]), 1);
			break;
		default:
			b.write((char*)f, 2);
		}
	}
	a.close();
	b.close();
	return true;
}

bool x::sbase64(const char* const originstr, const int& originstrlen, char*& base64str, int& base64strlen)
{
	if (originstrlen <= 0 || originstrlen > 1610612733)
		return false;
	unsigned char b[4];
	int i, j;
	if (originstrlen % 3 == 0)
		base64strlen = originstrlen / 3 * 4;
	else
		base64strlen = (originstrlen / 3 + 1) * 4;
	base64str = new char[base64strlen];
	for (i = 0; i < originstrlen; i += 3)
	{
		if (i + 2 < originstrlen)
		{
			b[0] = unsigned char(originstr[i]) >> 2;
			b[1] = (unsigned char(unsigned char(originstr[i]) << 6) >> 2) + (unsigned char(originstr[i + 1]) >> 4);
			b[2] = (unsigned char(unsigned char(originstr[i + 1]) << 4) >> 2) + (unsigned char(originstr[i + 2]) >> 6);
			b[3] = unsigned char(unsigned char(originstr[i + 2]) << 2) >> 2;
		}
		else if (i + 1 < originstrlen)
		{
			b[0] = unsigned char(originstr[i]) >> 2;
			b[1] = (unsigned char(unsigned char(originstr[i]) << 6) >> 2) + (unsigned char(originstr[i + 1]) >> 4);
			b[2] = (unsigned char(unsigned char(originstr[i + 1]) << 4) >> 2);
			b[3] = 64;
		}
		else
		{
			b[0] = unsigned char(originstr[i]) >> 2;
			b[1] = (unsigned char(unsigned char(originstr[i]) << 6) >> 2);
			b[2] = 64;
			b[3] = 64;
		}
		for (j = i / 3 * 4; j < i / 3 * 4 + 4; ++j)
			base64str[j] = base64table[b[j - i / 3 * 4]];
	}
	return true;
}

bool x::dsbase64(const char* const base64str, const int& base64strlen, char*& originstr, int& originstrlen)
{
	if (base64strlen <= 0 || base64strlen % 4 != 0)
		return false;
	if (base64str[base64strlen - 1] != '=')
		originstrlen = base64strlen / 4 * 3;
	else if (base64str[base64strlen - 2] != '=')
		originstrlen = base64strlen / 4 * 3 - 1;
	else
		originstrlen = base64strlen / 4 * 3 - 2;
	originstr = new char[originstrlen];
	unsigned char b[3];
	int i, j;
	for (i = 0; i < base64strlen; i += 4)
	{
		if (i + 4 < base64strlen)
		{
			b[0] = (dbase64table[base64str[i]] << 2) + (dbase64table[base64str[i + 1]] << 2 >> 6);
			b[1] = (dbase64table[base64str[i + 1]] << 4) + (dbase64table[base64str[i + 2]] << 2 >> 4);
			b[2] = (dbase64table[base64str[i + 2]] << 6) + (dbase64table[base64str[i + 3]] << 2 >> 2);
		}
		else
		{

		}
	}
	return true;
}

bool x::sbase64(const unsigned char* const originstr, const int& originstrlen, unsigned char*& base64str, int& base64strlen)
{
	if (originstrlen <= 0 || originstrlen > 1610612733)
		return false;
	unsigned char b[4];
	int i, j;
	if (originstrlen % 3 == 0)
		base64strlen = originstrlen / 3 * 4;
	else
		base64strlen = (originstrlen / 3 + 1) * 4;
	base64str = new unsigned char[base64strlen];
	for (i = 0; i < originstrlen; i += 3)
	{
		if (i + 2 < originstrlen)
		{
			b[0] = originstr[i] >> 2;
			b[1] = (originstr[i] << 6 >> 2) + (originstr[i + 1] >> 4);
			b[2] = (originstr[i + 1] << 4 >> 2) + (originstr[i + 2] >> 6);
			b[3] = originstr[i + 2] << 2 >> 2;
			for (j = i / 3 * 4; j < i / 3 * 4 + 4; ++j)
				base64str[j] = base64table[b[j - i / 3 * 4]];
		}
		else if (i + 1 < originstrlen)
		{
			b[0] = originstr[i] >> 2;
			b[1] = (originstr[i] << 6 >> 2) + (originstr[i + 1] >> 4);
			b[2] = (originstr[i + 1] << 4 >> 2) + (originstr[i + 2] >> 6);
			b[3] = 64;
			for (j = i / 3 * 4; j < i / 3 * 4 + 4; ++j)
				base64str[j] = base64table[b[j - i / 3 * 4]];
		}
		else
		{
			b[0] = originstr[i] >> 2;
			b[1] = (originstr[i] << 6 >> 2) + (originstr[i + 1] >> 4);
			b[2] = 64;
			b[3] = 64;
			for (j = i / 3 * 4; j < i / 3 * 4 + 4; ++j)
				base64str[j] = base64table[b[j - i / 3 * 4]];
		}
	}
	return true;
}

bool x::sbase64(const std::string& originstr, std::string& base64str)
{
	if (originstr.length() <= 0 || originstr.length() > 1610612733)
		return false;
	unsigned char b[4];
	int i, j;
	base64str = "";
	for (i = 0; i < originstr.length(); i += 3)
	{
		if (i + 2 < originstr.length())
		{
			b[0] = unsigned char(originstr[i]) >> 2;
			b[1] = (unsigned char(unsigned char(originstr[i]) << 6) >> 2) + (unsigned char(originstr[i + 1]) >> 4);
			b[2] = (unsigned char(unsigned char(originstr[i + 1]) << 4) >> 2) + (unsigned char(originstr[i + 2]) >> 6);
			b[3] = unsigned char(unsigned char(originstr[i + 2]) << 2) >> 2;
		}
		else if (i + 1 < originstr.length())
		{
			b[0] = unsigned char(originstr[i]) >> 2;
			b[1] = (unsigned char(unsigned char(originstr[i]) << 6) >> 2) + (unsigned char(originstr[i + 1]) >> 4);
			b[2] = (unsigned char(unsigned char(originstr[i + 1]) << 4) >> 2);
			b[3] = 64;
		}
		else
		{
			b[0] = unsigned char(originstr[i]) >> 2;
			b[1] = (unsigned char(unsigned char(originstr[i]) << 6) >> 2);
			b[2] = 64;
			b[3] = 64;
		}
		for (j = 0; j < 4; ++j)
			base64str += base64table[b[j]];
	}
	return true;
}