//
// Created by 星落_月残 on 2019/1/4.
//

#ifndef SIMPLEMEMO_BOOKMARKINTERFACEPARAMETERS_H
#define SIMPLEMEMO_BOOKMARKINTERFACEPARAMETERS_H

#include <string>

struct BookmarkInterfaceParameters
{
	explicit BookmarkInterfaceParameters(std::string_view key="",long long inSize=0)
	:key(key),maxSize(inSize)
	{}
	std::string key;
	long long maxSize;
};


#endif //SIMPLEMEMO_BOOKMARKINTERFACEPARAMETERS_H
