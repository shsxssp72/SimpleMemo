//
// Created by 星落_月残 on 2018/12/30.
//

#ifndef SIMPLEMEMO_ACCESSINTERFACE_H
#define SIMPLEMEMO_ACCESSINTERFACE_H

#include <any>
#include "../../Entity/MemoStorage.h"
#include "MemoInterfaceParameters.h"


class AccessMemoInterface
{
public:
	AccessMemoInterface() = default;
	AccessMemoInterface(const AccessMemoInterface &another) = delete;
	virtual void Create(const MemoInterfaceParameters &params) = 0;
	virtual MemoData Retrieve(const MemoInterfaceParameters &params) = 0;
	virtual void Update(const MemoInterfaceParameters &params) = 0;
	virtual void Delete(const MemoInterfaceParameters &params) = 0;
	//!
	//! 仅当get时使用，以函数内部的变量（如list）存储get的值，即谓词在函数内部
	virtual void Traverse(std::function<void(const std::any &)> function) const = 0;
};


#endif //SIMPLEMEMO_ACCESSINTERFACE_H
