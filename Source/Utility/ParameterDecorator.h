//
// Created by 星落_月残 on 2018/12/26.
//

#ifndef SIMPLEMEMO_PARAMETERDECORATOR_H
#define SIMPLEMEMO_PARAMETERDECORATOR_H

#include <utility>

//!
//! \tparam Reference 需要绑定指针的对象类型
//! \tparam Function 传入的Callable对象，注意参数列表第一位应留给待绑定的指针



template<class Reference,class Function>
class ParameterDecorator
{
public:
	explicit ParameterDecorator(Reference *inP,Function inF)
			:p(inP),f(inF)
	{
	};
	template<class ...Args>
	auto operator()(Args &&... args) const
	{
		return f(p,std::forward<Args>(args)...);
	}
private:
	Reference *p;
	Function f;
};




template<class Reference,class Function>
auto encloseReferencePointer(Reference *pRef,Function &&f)
{
	return ParameterDecorator<Reference,Function>(pRef,std::forward<Function>(f));
}
#endif //SIMPLEMEMO_PARAMETERDECORATOR_H
