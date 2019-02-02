//
// Created by 星落_月残 on 2018/12/24.
//

#ifndef SIMPLEMEMO_COMPARER_H
#define SIMPLEMEMO_COMPARER_H

template<class T>
class AbstractComparer
{
public:
	virtual bool operator ()(const T &a,const T &b)const = 0;
};

template<class T>
class AbstractAscendingComparer:public AbstractComparer<T>
{
public:
	bool operator ()(const T &a,const T &b)const override
	{
		return a<b;
	}
};

template<class T>
class AbstractDescendingComparer:public AbstractComparer<T>
{
public:
	bool operator ()(const T &a,const T &b)const override
	{
		return a>b;
	}
};

#endif //SIMPLEMEMO_COMPARER_H
