//
// Created by 星落_月残 on 2019/1/4.
//

#ifndef SIMPLEMEMO_ACCESSBOOKMARKINTERFACEIMPL_H
#define SIMPLEMEMO_ACCESSBOOKMARKINTERFACEIMPL_H

#include "AccessBookmarkInterface.h"
#include "../../Entity/MemoBookmark.h"



class AccessBookmarkInterfaceImpl:public AccessBookmarkInterface
{
public:
	AccessBookmarkInterfaceImpl()= delete;
	explicit AccessBookmarkInterfaceImpl(const std::shared_ptr<MemoBookmark> &inMemoBookmarkStorage);
	AccessBookmarkInterfaceImpl(const AccessBookmarkInterfaceImpl &another)= delete;
	AccessBookmarkInterfaceImpl(const AccessBookmarkInterface &another) = delete;
	void Create(const BookmarkInterfaceParameters &params) override;
	void Update(const BookmarkInterfaceParameters &params) override;
	void Delete(const BookmarkInterfaceParameters &params) override;
	void Traverse(std::function<void(const std::any &)> function) const override;
private:
	std::shared_ptr<MemoBookmark> memoBookmarkStorage;
};


#endif //SIMPLEMEMO_ACCESSBOOKMARKINTERFACEIMPL_H
