//
// Created by 星落_月残 on 2018/12/28.
//

#ifndef SIMPLEMEMO_UUIDUTILITY_H
#define SIMPLEMEMO_UUIDUTILITY_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>


class UUIDUtility
{
public:
	std::string getRandomUUID()
	{
		return boost::uuids::to_string(random_uuid_generator.operator ()());
	}
	std::string setNameGenerator()
	{
		name_uuid_generator=boost::uuids::name_generator_latest(random_uuid_generator.operator ()());
	}
	std::string setNameGenerator(const std::string &input)
	{
		name_uuid_generator=
				boost::uuids::name_generator_latest(
						string_uuid_generator.operator()(input));
	}
	std::string getNameUUID(const std::string &input)
	{
		return boost::uuids::to_string(name_uuid_generator.operator()(input));
	}
	std::string getStringUUID(const std::string &input)
	{
		return boost::uuids::to_string(string_uuid_generator.operator()(input));
	}
private:
	boost::uuids::random_generator_mt19937 random_uuid_generator;
	boost::uuids::name_generator_latest name_uuid_generator;
	boost::uuids::string_generator string_uuid_generator;
};


#endif //SIMPLEMEMO_UUIDUTILITY_H
