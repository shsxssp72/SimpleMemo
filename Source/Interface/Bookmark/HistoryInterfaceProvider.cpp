//
// Created by 星落_月残 on 2019/1/23.
//

#include "HistoryInterfaceProvider.h"
#include "../../Utility/SerializationUtility.h"
#include "AccessBookmarkInterfaceImpl.h"


HistoryInterfaceProvider::HistoryInterfaceProvider()
		:history(nullptr)
{
}
HistoryInterfaceProvider::HistoryInterfaceProvider(const std::shared_ptr<MemoBookmark> &history)
		:history(history)
{
}
std::shared_ptr<AccessBookmarkInterface> HistoryInterfaceProvider::getHistoryInterface()
{
	return this->getContainedDataInterface();
}
void HistoryInterfaceProvider::resetHistory(const std::shared_ptr<MemoBookmark> &inHistory)
{
	this->resetContainedData(inHistory);
}
void HistoryInterfaceProvider::saveHistory(std::ostream &out)
{
	this->saveContainedData(out);
}
std::shared_ptr<AccessBookmarkInterface> HistoryInterfaceProvider::getContainedDataInterface() const
{
	return std::make_shared<AccessBookmarkInterfaceImpl>(history);
}
void HistoryInterfaceProvider::resetContainedData(const std::shared_ptr<MemoBookmark> &inData)
{
	history=inData;
}
void HistoryInterfaceProvider::saveContainedData(std::ostream &out)
{
	SerializationUtility<MemoBookmark>::save(*this->history,out);
}

