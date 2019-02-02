//
// Created by 星落_月残 on 2018/12/27.
//

#ifndef SIMPLEMEMO_ABSTRACTSINGLETON_H
#define SIMPLEMEMO_ABSTRACTSINGLETON_H

#include <mutex>
#include <memory>


//!
//! \tparam T T必须声明unique_ptr和此类为友元
//https://www.cnblogs.com/lidabo/p/3949226.html
template<class T>
class AbstractSingleton
{
public:
	static T &getInstance()
	{
		if(instance.get()==nullptr)
		{
			std::lock_guard<std::mutex> lockGuard(mutex);
			if(instance.get()==nullptr)
			{
				instance.reset(new T());
			}
		}
		return *instance;
	}

protected:
	AbstractSingleton() = default;
	~AbstractSingleton() = default;
	static std::unique_ptr<T> instance;
private:
	static std::mutex mutex;
};

template<class T>
std::mutex AbstractSingleton<T>::mutex;
template<class T>
std::unique_ptr<T> AbstractSingleton<T>::instance;


#endif //SIMPLEMEMO_ABSTRACTSINGLETON_H
