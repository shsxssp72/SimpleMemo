//
// Created by 星落_月残 on 2018/12/24.
//

#ifndef SIMPLEMEMO_XMLUTILITY_H
#define SIMPLEMEMO_XMLUTILITY_H

#include <thread>
#include <mutex>
#include <tinyxml2.h>
#include "../Entity/MemoStorage.h"
#include "TraverseHelper.h"
#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
//TODO eventhandler 的参数改为Any？

//! TODO Deprecated
template<class T>
class AbstractXMLUtility
{
public:
	virtual void save(const T &data,FILE *pFile) = 0;

};


class MemoStorageXMLUtility
{
public:
	static MemoStorageXMLUtility &getInstance()
	{
		std::lock_guard<std::mutex> lockGuard(mutex);
		static MemoStorageXMLUtility memoStorageXMLUtility;
		return memoStorageXMLUtility;
	}
	void save(const MemoStorage &memoStorage)
	{
		using namespace tinyxml2;
		XMLDocument document;

		XMLDeclaration *declaration=document.NewDeclaration();
		document.InsertFirstChild(declaration);
		XMLElement *root=document.NewElement("MEMO_ROOT");
		MemoDataTraverseHelperForGetter traverseHelper;
		memoStorage.Traverse(std::bind(&MemoDataTraverseHelperForGetter::operator (),&traverseHelper,std::placeholders::_1,[](const MemoData &input)->bool
		{ return true; }));
		for(auto &r:traverseHelper.getMemoDatas())
		{
			r.getVisitTimestamp();
		}
	}
private:
	MemoStorageXMLUtility() = default;
	static std::mutex mutex;
};

std::mutex MemoStorageXMLUtility::mutex=std::mutex();

#endif //SIMPLEMEMO_XMLUTILITY_H
