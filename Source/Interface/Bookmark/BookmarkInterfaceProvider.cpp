//
// Created by 星落_月残 on 2019/1/23.
//

#include "BookmarkInterfaceProvider.h"
#include "../../Utility/SerializationUtility.h"
#include "AccessBookmarkInterfaceImpl.h"


BookmarkInterfaceProvider::BookmarkInterfaceProvider()
		:bookmark(nullptr)
{
}
BookmarkInterfaceProvider::BookmarkInterfaceProvider(const std::shared_ptr<MemoBookmark> &bookmark)
		:bookmark(bookmark)
{
}
std::shared_ptr<AccessBookmarkInterface> BookmarkInterfaceProvider::getBookmarkInterface()
{
	return this->getContainedDataInterface();
}
void BookmarkInterfaceProvider::resetBookmark(const std::shared_ptr<MemoBookmark> &inBookmark)
{
	this->resetContainedData(inBookmark);
}
void BookmarkInterfaceProvider::saveBookmark(std::ostream &out)
{
	this->saveContainedData(out);
}
std::shared_ptr<AccessBookmarkInterface> BookmarkInterfaceProvider::getContainedDataInterface() const
{
	return std::make_shared<AccessBookmarkInterfaceImpl>(bookmark);
}
void BookmarkInterfaceProvider::resetContainedData(const std::shared_ptr<MemoBookmark> &inData)
{
	bookmark=inData;
}
void BookmarkInterfaceProvider::saveContainedData(std::ostream &out)
{
	SerializationUtility<MemoBookmark>::save(*this->bookmark,out);
}

