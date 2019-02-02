//
// Created by 星落_月残 on 2018/12/30.
//

#ifndef SIMPLEMEMO_MEMOINTERFACEPARAMETERS_H
#define SIMPLEMEMO_MEMOINTERFACEPARAMETERS_H

#include <string>


//params包含key,newKey,value
struct MemoInterfaceParameters
{
	explicit MemoInterfaceParameters(std::string_view key="",
									 std::string_view newKey="",
									 std::string_view value="")
			:key(key),newKey(newKey),value(value)
	{}
	std::string key;
	std::string newKey;
	std::string value;
};


#endif //SIMPLEMEMO_MEMOINTERFACEPARAMETERS_H
