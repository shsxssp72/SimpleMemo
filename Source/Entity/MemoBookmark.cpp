//
// Created by 星落_月残 on 2019/1/3.
//

#include "MemoBookmark.h"


void MemoBookmark::addBookmark(const std::string &key)
{
	MemoBookmarkContent content;
	content.key=key;
	content.lastVisit=std::chrono::steady_clock::now();
	bookmarks.push_front(std::move(content));
	if(maxSize>0&&bookmarks.size()>maxSize)
	{
		bookmarks.pop_back();
	}
}
void MemoBookmark::removeBookmark(const std::string &key)
{
	bookmarks.remove_if([&](const MemoBookmarkContent &input)
						{return input.key==key;});
}
void MemoBookmark::updateBookmarkTime(const std::string &key)
{
	for(auto &r:bookmarks)
	{
		if(r.key==key)
			r.lastVisit=std::chrono::steady_clock::now();
	}
}
void MemoBookmark::setMaxSizeAndApply(long long inSize)
{
	maxSize=inSize;
	for(;maxSize>0&&bookmarks.size()>maxSize;)
	{
		bookmarks.pop_back();
	}
}
void MemoBookmark::Traverse(std::function<void(const MemoBookmarkContent &)> traverseFunction) const
{
	for(auto &r:bookmarks)
	{
		traverseFunction.operator()(r);
	}
}
