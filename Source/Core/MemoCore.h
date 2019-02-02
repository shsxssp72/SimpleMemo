//
// Created by 星落_月残 on 2019/1/22.
//

#ifndef SIMPLEMEMO_MEMOCORE_H
#define SIMPLEMEMO_MEMOCORE_H


#include "../Entity/MemoStorage.h"
#include "../Entity/MemoBookmark.h"
#include "../Interface/Memo/AccessMemoInterface.h"
#include "../Interface/Memo/MemoInterfaceProvider.h"
#include "../Interface/Bookmark/AccessBookmarkInterface.h"
#include "../Interface/Bookmark/BookmarkInterfaceProvider.h"
#include "../Interface/Bookmark/HistoryInterfaceProvider.h"
#include "../Utility/EventMonitor.h"


class MemoCore:public MemoInterfaceProvider,
			   public BookmarkInterfaceProvider,
			   public HistoryInterfaceProvider,
			   public MonitorBase
{
public:
	MemoCore();

private:
	//TODO 此处基类直接指向实体的storage，可以考虑改为接口，便于扩展为基于数据库

};
//!注意仅修改此处而不修改UI持有的指针会导致错误


#endif //SIMPLEMEMO_MEMOCORE_H
