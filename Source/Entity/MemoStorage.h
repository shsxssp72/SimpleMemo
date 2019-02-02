//
// Created by 星落_月残 on 2018/12/24.
//

#ifndef SIMPLEMEMO_MEMOSTORAGE_H
#define SIMPLEMEMO_MEMOSTORAGE_H

#include <map>
#include <functional>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/map.hpp>
#include "MemoData.h"
#include "../Utility/Comparer.h"


using MemoMap=std::map<std::string,MemoData,AbstractAscendingComparer<std::string>>;


class MemoStorage
{
	friend class boost::serialization::access;

	template<class Archive>
	void save(Archive &ar,const unsigned int version) const
	{
		ar<<BOOST_SERIALIZATION_NVP(storage);
	}

	template<class Archive>
	void load(Archive &ar,const unsigned int version)
	{
		ar>>BOOST_SERIALIZATION_NVP(storage);
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();

public:
	MemoStorage() = default;
	MemoStorage(const MemoStorage &another);
	const MemoData &RetrieveMemoByKey(const std::string &key);
	void UpdateMemo(const MemoData &memoData);
	void UpdateMemoKey(const std::string &oldKey,const std::string &newKey);
	void DeleteMemoByKey(const std::string &key);
	void Traverse(std::function<void(const MemoData &)> traverseFunction) const;
private:
	MemoMap storage;
};


#endif //SIMPLEMEMO_MEMOSTORAGE_H
