#include <utility>

#include <utility>

//
// Created by 星落_月残 on 2019/1/23.
//

#ifndef SIMPLEMEMO_TRANSFERENTITY_H
#define SIMPLEMEMO_TRANSFERENTITY_H


#include <boost/serialization/nvp.hpp>
#include <string>

class TransferEntity
{
	friend class boost::serialization::access;

	template<class Archive>
	void save(Archive &ar,const unsigned int version) const
	{
		ar<<BOOST_SERIALIZATION_NVP(memoStorage);
		ar<<BOOST_SERIALIZATION_NVP(bookmark);
		ar<<BOOST_SERIALIZATION_NVP(history);

	}

	template<class Archive>
	void load(Archive &ar,const unsigned int version)
	{
		ar>>BOOST_SERIALIZATION_NVP(memoStorage);
		ar>>BOOST_SERIALIZATION_NVP(bookmark);
		ar>>BOOST_SERIALIZATION_NVP(history);
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();
public:
	TransferEntity()
	{
	}
	TransferEntity(std::string memoStorage,std::string bookmark,std::string history)
			:memoStorage(std::move(memoStorage)),bookmark(std::move(bookmark)),history(std::move(history))
	{
	}
	std::string memoStorage;
	std::string bookmark;
	std::string history;
};


#endif //SIMPLEMEMO_TRANSFERENTITY_H
