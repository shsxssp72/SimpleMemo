//
// Created by 星落_月残 on 2018/12/30.
//

#ifndef SIMPLEMEMO_ACCESSMEMOINTERFACEIMPL_H
#define SIMPLEMEMO_ACCESSMEMOINTERFACEIMPL_H


#include "AccessMemoInterface.h"


class AccessMemoInterfaceImpl:public AccessMemoInterface
{
public:
	AccessMemoInterfaceImpl() = delete;
	explicit AccessMemoInterfaceImpl(const std::shared_ptr<MemoStorage> &memoStorage);
	AccessMemoInterfaceImpl(const AccessMemoInterface &another) = delete;
	void Create(const MemoInterfaceParameters &params) override;
	MemoData Retrieve(const MemoInterfaceParameters &params) override;
	void Update(const MemoInterfaceParameters &params) override;
	void Delete(const MemoInterfaceParameters &params) override;
	void Traverse(std::function<void(const std::any &)> function) const override;
private:
	std::shared_ptr<MemoStorage> memoStorage;
};


#endif //SIMPLEMEMO_ACCESSMEMOINTERFACEIMPL_H
