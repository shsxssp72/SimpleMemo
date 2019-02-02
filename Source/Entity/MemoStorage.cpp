//
// Created by 星落_月残 on 2018/12/24.
//

#include "MemoStorage.h"
#include "MemoData.h"


MemoStorage::MemoStorage(const MemoStorage &another)
{
	this->storage=another.storage;
}

const MemoData &MemoStorage::RetrieveMemoByKey(const std::string &key)
{
	storage.at(key).updateVisitTimeAndFrequency();
	return storage.at(key);
}
void MemoStorage::UpdateMemo(const MemoData &memoData)
{
	if(storage.count(memoData.getKey())!=0)
	{
		throw std::invalid_argument("MemoStorage::UpdateMemo: Key duplicate.");
	}
	storage.emplace(memoData.getKey(),memoData);
	storage.at(memoData.getKey()).updateVisitTimeAndFrequency();
}
void MemoStorage::UpdateMemoKey(const std::string &oldKey,const std::string &newKey)
{
	auto itemToModify=storage.at(oldKey);
	if(storage.count(newKey)!=0)
	{
		throw std::invalid_argument("MemoStorage::UpdateMemoKey: NewKey duplicate.");
	}
	itemToModify.setKey(newKey);
	this->UpdateMemo(itemToModify);

	this->DeleteMemoByKey(oldKey);


}
void MemoStorage::DeleteMemoByKey(const std::string &key)
{
	storage.erase(key);
}
void MemoStorage::Traverse(std::function<void(const MemoData &)> traverseFunction) const
{
	for(auto &r:storage)
	{
		traverseFunction.operator()(r.second);
	}
}
