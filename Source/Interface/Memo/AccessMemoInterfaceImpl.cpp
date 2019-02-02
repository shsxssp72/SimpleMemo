//
// Created by 星落_月残 on 2018/12/30.
//

#include "../../Utility/Commons.h"
#include "AccessMemoInterfaceImpl.h"



AccessMemoInterfaceImpl::AccessMemoInterfaceImpl(const std::shared_ptr<MemoStorage> &inMemoStorage)
		:memoStorage(inMemoStorage)
{
}
void AccessMemoInterfaceImpl::Create(const MemoInterfaceParameters &params)
{
	auto parameters=std::any_cast<MemoInterfaceParameters>(params);
	if(isAnyStringEmpty(parameters.key,parameters.value))
		throw std::invalid_argument("AccessMemoInterfaceImpl::Create: Key and value should not be empty.");
	memoStorage->UpdateMemo(MemoData(parameters.key,parameters.value));
}
MemoData AccessMemoInterfaceImpl::Retrieve(const MemoInterfaceParameters &params)
{
	auto parameters=std::any_cast<MemoInterfaceParameters>(params);
	if(isAnyStringEmpty(parameters.key))
		throw std::invalid_argument("AccessMemoInterfaceImpl::Retrieve: Key should not be empty.");
	return memoStorage->RetrieveMemoByKey(parameters.key);
}
void AccessMemoInterfaceImpl::Update(const MemoInterfaceParameters &params)
{
	auto parameters=std::any_cast<MemoInterfaceParameters>(params);
	if(parameters.key.empty())
		throw std::invalid_argument("AccessMemoInterfaceImpl::Update: Key should not be empty.");
	else if(!parameters.newKey.empty()&&parameters.value.empty())
	{
		memoStorage->UpdateMemoKey(parameters.key,parameters.newKey);
	}
	else if(parameters.newKey.empty()&&!parameters.value.empty())
	{
		memoStorage->UpdateMemo(MemoData(parameters.key,parameters.value));
	}
	else if(!parameters.newKey.empty()&&!parameters.value.empty())
	{
		memoStorage->DeleteMemoByKey(parameters.key);
		memoStorage->UpdateMemo(MemoData(parameters.newKey,parameters.value));
	}
	else
	{
		throw std::invalid_argument("AccessMemoInterfaceImpl::Update: NewKey or value should not be empty.");
	}
}
void AccessMemoInterfaceImpl::Delete(const MemoInterfaceParameters &params)
{
	auto parameters=std::any_cast<MemoInterfaceParameters>(params);
	if(isAnyStringEmpty(parameters.key))
		throw std::invalid_argument("AccessMemoInterfaceImpl::Delete: Key should not be empty.");
	memoStorage->DeleteMemoByKey(parameters.key);
}
void AccessMemoInterfaceImpl::Traverse(std::function<void(const std::any &)> function) const
{
	memoStorage->Traverse(std::move(function));
}
