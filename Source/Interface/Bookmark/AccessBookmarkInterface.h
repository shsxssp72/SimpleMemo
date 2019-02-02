//
// Created by 星落_月残 on 2019/1/4.
//

#ifndef SIMPLEMEMO_ACCESSBOOKMARKINTERFACE_H
#define SIMPLEMEMO_ACCESSBOOKMARKINTERFACE_H

#include <any>
#include <functional>
#include "BookmarkInterfaceParameters.h"

class AccessBookmarkInterface
{
public:
	AccessBookmarkInterface()= default;
	AccessBookmarkInterface(const AccessBookmarkInterface &another)= delete;
	virtual void Create(const BookmarkInterfaceParameters &params) = 0;
	virtual void Update(const BookmarkInterfaceParameters &params) = 0;
	virtual void Delete(const BookmarkInterfaceParameters &params) = 0;
	//!
	//! 仅当get时使用，以函数内部的变量（如list）存储get的值，即谓词在函数内部
	virtual void Traverse(std::function<void(const std::any &)> function) const = 0;
};


#endif //SIMPLEMEMO_ACCESSBOOKMARKINTERFACE_H
