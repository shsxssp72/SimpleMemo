//
// Created by 星落_月残 on 2019/1/3.
//

#ifndef SIMPLEMEMO_MEMOBOOKMARK_H
#define SIMPLEMEMO_MEMOBOOKMARK_H

#include <list>
#include <string>
#include <chrono>
#include <functional>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/list.hpp>


//TODO 以时间降序排列map

struct MemoBookmarkContent
{
	friend class boost::serialization::access;

	template<class Archive>
	void save(Archive &ar,const unsigned int version) const
	{
		ar&BOOST_SERIALIZATION_NVP(key);
		ar&BOOST_SERIALIZATION_NVP(lastVisit);
	}
	template<class Archive>
	void load(Archive &ar,const unsigned int version)
	{
		ar&BOOST_SERIALIZATION_NVP(key);
		ar&BOOST_SERIALIZATION_NVP(lastVisit);
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();
	std::string key;
	std::chrono::steady_clock::time_point lastVisit;
};


class MemoBookmark
{
	friend class boost::serialization::access;

	template<class Archive>
	void save(Archive &ar,const unsigned int version) const
	{
		ar&BOOST_SERIALIZATION_NVP(bookmarks);
		ar&BOOST_SERIALIZATION_NVP(maxSize);
	}
	template<class Archive>
	void load(Archive &ar,const unsigned int version)
	{
		ar&BOOST_SERIALIZATION_NVP(bookmarks);
		ar&BOOST_SERIALIZATION_NVP(maxSize);
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();
public:
	MemoBookmark() = default;
	MemoBookmark(const MemoBookmark &another) = default;
	void addBookmark(const std::string &key);
	void removeBookmark(const std::string &key);
	void updateBookmarkTime(const std::string &key);
	void setMaxSizeAndApply(long long inSize);
	void Traverse(std::function<void(const MemoBookmarkContent &)> traverseFunction) const;

private:
	std::list<MemoBookmarkContent> bookmarks;
	long long maxSize=0;
};


#endif //SIMPLEMEMO_MEMOBOOKMARK_H
