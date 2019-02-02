//
// Created by 星落_月残 on 2019/1/23.
//

#ifndef SIMPLEMEMO_BOOKMARKINTERFACEPROVIDER_H
#define SIMPLEMEMO_BOOKMARKINTERFACEPROVIDER_H


#include "../../Entity/MemoBookmark.h"
#include "../AbstractInterfaceProvider.h"
#include "AccessBookmarkInterface.h"


class BookmarkInterfaceProvider:public AbstractInterfaceProvider<MemoBookmark,AccessBookmarkInterface>
{
public:
	BookmarkInterfaceProvider();
	explicit BookmarkInterfaceProvider(const std::shared_ptr<MemoBookmark> &bookmark);
	std::shared_ptr<AccessBookmarkInterface> getBookmarkInterface();
protected:
	void resetBookmark(const std::shared_ptr<MemoBookmark> &inBookmark);
	void saveBookmark(std::ostream &out);
private:
	std::shared_ptr<AccessBookmarkInterface> getContainedDataInterface() const override;
	void resetContainedData(const std::shared_ptr<MemoBookmark> &inData) override;
	void saveContainedData(std::ostream &out) override;
private:
	std::shared_ptr<MemoBookmark> bookmark;
};


#endif //SIMPLEMEMO_BOOKMARKINTERFACEPROVIDER_H
