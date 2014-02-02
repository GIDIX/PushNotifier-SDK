#include "exception.h"

using namespace std;

CustomException::CustomException(string status, int code)
{
	this->status = status;
	this->code = code;
}
