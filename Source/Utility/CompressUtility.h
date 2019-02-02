//
// Created by 星落_月残 on 2019/1/23.
//

#ifndef SIMPLEMEMO_COMPRESSUTILITY_H
#define SIMPLEMEMO_COMPRESSUTILITY_H

#include <snappy.h>

class CompressUtility
{
public:
	static std::string Compress(const std::string &in)
	{
		std::string result;
		snappy::Compress(in.data(),in.size(),&result);
		return result;
	}
	static std::string Uncompress(const std::string &in)
	{
		std::string result;
		snappy::Uncompress(in.data(),in.size(),&result);
		return result;
	}
};


#endif //SIMPLEMEMO_COMPRESSUTILITY_H
