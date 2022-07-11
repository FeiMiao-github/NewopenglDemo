#include <fstream>
#include <iostream>
#include "demo/loader.h"

std::string LoadShader(const std::string &path)
{
	std::ifstream ifs(path);
	if (!ifs.is_open())
	{
		throw LoaderOpenFileException(path);
	}

	std::string ret;
	char buf[1024];
	while (!ifs.eof())
	{
		ifs.read(buf, 1024);
		ret.append(buf, ifs.gcount());
	}
	
	return ret;
}