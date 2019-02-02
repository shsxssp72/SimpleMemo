//
// Created by 星落_月残 on 2019/1/23.
//

#ifndef SIMPLEMEMO_HISTORYINTERFACEPROVIDER_H
#define SIMPLEMEMO_HISTORYINTERFACEPROVIDER_H

#include "../../Entity/MemoBookmark.h"
#include "../AbstractInterfaceProvider.h"
#include "AccessBookmarkInterface.h"


class HistoryInterfaceProvider:public AbstractInterfaceProvider<MemoBookmark,AccessBookmarkInterface>
{
public:
	HistoryInterfaceProvider();
	explicit HistoryInterfaceProvider(const std::shared_ptr<MemoBookmark> &bookmark);
	std::shared_ptr<AccessBookmarkInterface> getHistoryInterface();
protected:
	void resetHistory(const std::shared_ptr<MemoBookmark> &inHistory);
	void saveHistory(std::ostream &out);
private:
	std::shared_ptr<AccessBookmarkInterface> getContainedDataInterface() const override;
	void resetContainedData(const std::shared_ptr<MemoBookmark> &inData) override;
	void saveContainedData(std::ostream &out) override;
private:
	std::shared_ptr<MemoBookmark> history;
};


#endif //SIMPLEMEMO_HISTORYINTERFACEPROVIDER_H
