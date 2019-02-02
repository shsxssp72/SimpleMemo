//
// Created by 星落_月残 on 2018/12/25.
//

#ifndef SIMPLEMEMO_SERIALIZATIONUTILITY_H
#define SIMPLEMEMO_SERIALIZATIONUTILITY_H

#include <type_traits>
#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <chrono>
#include "../Config/ChronoSerialization.h"



template<class T>
class SerializationUtility
{
public:

	static void save(const T &toSave,std::ostream &fout)
	{
//		static_assert(std::is_base_of<BoostSerializable,T>::value);
		boost::archive::xml_oarchive oarchive(fout);
		oarchive<<BOOST_SERIALIZATION_NVP(toSave);
	}
	static std::shared_ptr<T> load(std::istream &fin)
	{
//		static_assert(std::is_base_of<BoostSerializable,T>::value);
		boost::archive::xml_iarchive iarchive(fin);
		T result;
		iarchive>>BOOST_SERIALIZATION_NVP(result);
		return std::make_shared<T>(std::move(result));
	}
};



#endif //SIMPLEMEMO_SERIALIZATIONUTILITY_H
