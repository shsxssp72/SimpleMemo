//
// Created by 星落_月残 on 2018/12/26.
//

#ifndef SIMPLEMEMO_COMMONS_H
#define SIMPLEMEMO_COMMONS_H

#include <functional>

template<class ...Args>
bool ExpectAll(Args ...args)
{
	return (args&&...);
};

template<class ...Args>
bool ExpectAny(Args ...args)
{
	return (args||...);
};

template<class T,class ...Args>
bool isOneOf(T &input,Args &&...args)
{
	return ((input==args)||...);
}

template<class F,class ...Args>
bool satisfyAll(F &&f,Args &&...args)
{
	return ((f(args))&&...);
}

template<class F,class ...Args>
bool satisfyAny(F &&f,Args &&...args)
{
	return ((f(args))||...);
}

class JudgeAnyStringEmpty
{
public:
	template <class ...Args>
	bool operator()(Args &&...args) const
	{
		return satisfyAny(std::bind(&std::string::empty,std::placeholders::_1),std::forward<Args>(args)...);
	}
};


const JudgeAnyStringEmpty isAnyStringEmpty;

#endif //SIMPLEMEMO_COMMONS_H
