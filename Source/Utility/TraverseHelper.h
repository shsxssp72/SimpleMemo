//
// Created by 星落_月残 on 2018/12/25.
//

#ifndef SIMPLEMEMO_TRAVERSEHELPER_H
#define SIMPLEMEMO_TRAVERSEHELPER_H

#include "../Entity/MemoStorage.h"
#include "../Entity/MemoBookmark.h"
#include <any>

template<class T>
class AbstractTraverseHelper
{
public:
	virtual void operator ()(const T &input,std::function<bool(const T &)> function) = 0;
};

class MemoDataTraverseHelperForGetter:public AbstractTraverseHelper<MemoData>
{
public:
	void operator ()(const MemoData &input,std::function<bool(const MemoData &)> function) override
	{
		if(function(input))
			memoDatas.push_back(input);
	}
	const std::list<MemoData> &getMemoDatas() const
	{
		return memoDatas;
	}
private:
	std::list<MemoData> memoDatas;
};

class MemoDataTraverseHelperForAnyGetter:public AbstractTraverseHelper<std::any>
{
public:
	void operator ()(const std::any &input,std::function<bool(const std::any &)> function) override
	{
		if(function(input))
			memoDatas.push_back(std::any_cast<MemoData>(input));
	}
	const std::list<MemoData> &getMemoDatas() const
	{
		return memoDatas;
	}
	void clear()
	{
		memoDatas.clear();
	}
private:
	std::list<MemoData> memoDatas;
};

class BookmarkTraverseHelperForAnyGetter:public AbstractTraverseHelper<std::any>
{
public:
	void operator()(const std::any &input,std::function<bool(const std::any &)> function) override
	{
		if(function(input))
			bookmarks.push_back(std::any_cast<MemoBookmarkContent>(input));
	}
	const std::list<MemoBookmarkContent> &getBookmarks() const
	{
		return bookmarks;
	}
	void clear()
	{
		bookmarks.clear();
	}
private:
	std::list<MemoBookmarkContent> bookmarks;
};

#endif //SIMPLEMEMO_TRAVERSEHELPER_H
