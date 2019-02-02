//
// Created by 星落_月残 on 2018/12/23.
//

#ifndef SIMPLEMEMO_MEMODATA_H
#define SIMPLEMEMO_MEMODATA_H

#include <utility>
#include <string>
#include <list>
#include <chrono>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/map.hpp>


class MemoData
{
	friend class boost::serialization::access;

	template<class Archive>
	void save(Archive &ar,const unsigned int version) const
	{
		ar&BOOST_SERIALIZATION_NVP(item);
		ar&BOOST_SERIALIZATION_NVP(visitTimestamp);
		ar&BOOST_SERIALIZATION_NVP(accessFrequency);

//		ar&boost::serialization::make_binary_object(&visitTimestamp, sizeof(visitTimestamp));
	}
	template<class Archive>
	void load(Archive &ar,const unsigned int version)
	{
		ar&BOOST_SERIALIZATION_NVP(item);
		ar&BOOST_SERIALIZATION_NVP(visitTimestamp);
		ar&BOOST_SERIALIZATION_NVP(accessFrequency);

//		ar&boost::serialization::make_binary_object(&visitTimestamp, sizeof(visitTimestamp));
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();
public:
	MemoData() = default;
	MemoData(std::string key,std::string value);
	MemoData(const MemoData &another);
	void updateVisitTimeAndFrequency();
	const std::string &getKey() const;
	const std::string &getValue() const;
	void setKey(const std::string &newKey);
	void setValue(const std::string &newValue);
	const std::chrono::steady_clock::time_point &getVisitTimestamp() const;
	long long int getAccessFrequency() const;
private:
	std::pair<std::string,std::string> item;
	std::chrono::steady_clock::time_point visitTimestamp;
	long long accessFrequency=0;
};



#endif //SIMPLEMEMO_MEMODATA_H
