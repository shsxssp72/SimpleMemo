//
// Created by 星落_月残 on 2019/1/23.
//

#ifndef SIMPLEMEMO_CHRONOSERIALIZATION_H
#define SIMPLEMEMO_CHRONOSERIALIZATION_H

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <chrono>


namespace boost
{
	namespace serialization
	{
		template<class Archive,typename clock>
		void load(Archive &ar,std::chrono::time_point<clock> &tp,unsigned)
		{
			using namespace std::chrono;
			nanoseconds::rep nanos;

			ar>>BOOST_SERIALIZATION_NVP(nanos);
//			ar>>nanos;
			tp=time_point<clock>(nanoseconds(nanos));
		}

		template<class Archive,typename clock>
		void save(Archive &ar,std::chrono::time_point<clock> const &tp,unsigned)
		{
			using namespace std::chrono;
			nanoseconds::rep nanos=duration_cast<nanoseconds>(tp.time_since_epoch()).count();
			ar<<BOOST_SERIALIZATION_NVP(nanos);
		}

		template<class Archive,typename clock>
		inline void serialize(Archive &ar,std::chrono::time_point<clock> &tp,unsigned version)
		{
			boost::serialization::split_free(ar,tp,version);
		}

	}
}
//BOOST_CLASS_IS_WRAPPER(long long);
#endif //SIMPLEMEMO_CHRONOSERIALIZATION_H
