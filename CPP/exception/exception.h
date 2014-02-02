#ifndef CUSTOM_EXCEPTION_H
#define CUSTOM_EXCEPTION_H

#include <string>

class CustomException
{
public:
	CustomException(std::string status, int code);
	std::string status;
	int code;
};

#endif
