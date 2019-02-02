//
// Created by 星落_月残 on 2019/1/4.
//

#include "Source/Utility/Commons.h"
#include "AccessBookmarkInterfaceImpl.h"


AccessBookmarkInterfaceImpl::AccessBookmarkInterfaceImpl(const std::shared_ptr<MemoBookmark> &inMemoBookmarkStorage)
		:memoBookmarkStorage(inMemoBookmarkStorage)
{
}
void AccessBookmarkInterfaceImpl::Create(const BookmarkInterfaceParameters &params)
{
	auto parameters=std::any_cast<BookmarkInterfaceParameters>(params);
	if(isAnyStringEmpty(parameters.key))
		throw std::invalid_argument("AccessBookmarkInterfaceImpl::Create: Key should not be empty.");
	memoBookmarkStorage->addBookmark(parameters.key);
}
void AccessBookmarkInterfaceImpl::Update(const BookmarkInterfaceParameters &params)
{
	auto parameters=std::any_cast<BookmarkInterfaceParameters>(params);
	bool updated=false;
	if(!isAnyStringEmpty(parameters.key))
	{
		memoBookmarkStorage->updateBookmarkTime(parameters.key);
		updated=true;
	}
	if(parameters.maxSize)
	{
		memoBookmarkStorage->setMaxSizeAndApply(parameters.maxSize);
		updated=true;
	}
	if(!updated)
		throw std::invalid_argument("AccessBookmarkInterfaceImpl::Update: Key or maxSize should not be empty.");
}
void AccessBookmarkInterfaceImpl::Delete(const BookmarkInterfaceParameters &params)
{
	auto parameters=std::any_cast<BookmarkInterfaceParameters>(params);
	if(isAnyStringEmpty(parameters.key))
		throw std::invalid_argument("AccessBookmarkInterfaceImpl::Delete: Key should not be empty.");
	memoBookmarkStorage->removeBookmark(parameters.key);
}
void AccessBookmarkInterfaceImpl::Traverse(std::function<void(const std::any &)> function) const
{
	memoBookmarkStorage->Traverse(function);
}
