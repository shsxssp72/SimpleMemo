//
// Created by 星落_月残 on 2018/12/25.
//
#include <gtest/gtest.h>
#include "../Source/Entity/MemoStorage.h"
#include "../Source/Utility/SerializationUtility.h"
#include "../Source/Entity/MemoBookmark.h"
#include "../Source/Entity/TransferEntity.h"
#include "../Source/Utility/CompressUtility.h"
#include "../Source/Utility/Crypto.h"


TEST(Serialization,tmp1)
{MemoStorage memoStorage;
	MemoBookmark bookmark;
	MemoBookmark history;

	std::list<std::pair<std::string,std::string>> list;
	list.emplace_back("TestKey1","TestValue1");
	list.emplace_back("TestKey2","TestValue2");
	list.emplace_back("TestKey3","TestValue3");
	list.emplace_back("TestKey4","TestValue4");

	for(auto &r:list)
	{
		memoStorage.UpdateMemo(MemoData(r.first,r.second));
		bookmark.addBookmark(r.first);
		history.addBookmark(r.first);
	}


	auto ss=std::stringstream();
	auto fout=std::ofstream("1.xml");
	auto fin=std::ifstream("1.xml");



	std::stringstream memoSS;
	std::stringstream bookmarkSS;
	std::stringstream historySS;

	SerializationUtility<MemoStorage>::save(memoStorage,memoSS);
	SerializationUtility<MemoBookmark>::save(bookmark,bookmarkSS);
	SerializationUtility<MemoBookmark>::save(history,historySS);


	std::string memoXML;
	memoSS>>memoXML;
	std::string bookmarkXML;
	bookmarkSS>>bookmarkXML;
	std::string historyXML;
	historySS>>historyXML;

	//TODO 此处可进行加密

	auto crypto=Crypto::getInstance();
	TransferEntity transferEntity(
			crypto.getOperation("Base64Encode").operator()(CryptoParameters(memoXML)),
			crypto.getOperation("Base64Encode").operator()(CryptoParameters(bookmarkXML)),
			crypto.getOperation("Base64Encode").operator()(CryptoParameters(historyXML))
	);

	SerializationUtility<TransferEntity>::save(transferEntity,fout);
//	for(auto &r:list)
//	{
//		ASSERT_EQ(memoStorage.RetrieveMemoByKey(r.first).getValue(),
//				  loaded->RetrieveMemoByKey(r.first).getValue());
//	}

}

TEST(Serialization,tmp2)
{
	MemoStorage memoStorage;
	MemoBookmark bookmark;
	MemoBookmark history;

	std::list<std::pair<std::string,std::string>> list;
	list.emplace_back("TestKey1","TestValue1");
	list.emplace_back("TestKey2","TestValue2");
	list.emplace_back("TestKey3","TestValue3");
	list.emplace_back("TestKey4","TestValue4");

	for(auto &r:list)
	{
		memoStorage.UpdateMemo(MemoData(r.first,r.second));
		bookmark.addBookmark(r.first);
		history.addBookmark(r.first);
	}


	std::ofstream fout("Memo.xml");

	std::stringstream memoSS;
	std::stringstream bookmarkSS;
	std::stringstream historySS;

	SerializationUtility<MemoStorage>::save(memoStorage,memoSS);
	SerializationUtility<MemoBookmark>::save(bookmark,bookmarkSS);
	SerializationUtility<MemoBookmark>::save(history,historySS);


	std::string memoXML=memoSS.str();
	std::string bookmarkXML=bookmarkSS.str();
	std::string historyXML=historySS.str();

	//TODO 此处可进行加密

	auto crypto=Crypto::getInstance();
	TransferEntity transferEntity(
			crypto.getOperation("Base64Encode").operator()(CryptoParameters(CompressUtility::Compress(memoXML))),
			crypto.getOperation("Base64Encode").operator()(CryptoParameters(CompressUtility::Compress(bookmarkXML))),
			crypto.getOperation("Base64Encode").operator()(CryptoParameters(CompressUtility::Compress(historyXML)))
	);

	SerializationUtility<TransferEntity>::save(transferEntity,fout);
}

TEST(Serialization,tmp3)
{
	auto crypto=Crypto::getInstance();


	std::ifstream fin("Memo.xml");
	auto loadedEntity=SerializationUtility<TransferEntity>::load(fin);

	std::string decryptedMemoXML=crypto.getOperation("Base64Decode").operator()(CryptoParameters(loadedEntity->memoStorage));
	std::string decryptedBookmarkXML=crypto.getOperation("Base64Decode").operator()(CryptoParameters(loadedEntity->bookmark));
	std::string decryptedHistoryXML=crypto.getOperation("Base64Decode").operator()(CryptoParameters(loadedEntity->history));

	std::string memoXML=CompressUtility::Uncompress(decryptedMemoXML);
	std::string bookmarkXML=CompressUtility::Uncompress(decryptedBookmarkXML);
	std::string historyXML=CompressUtility::Uncompress(decryptedHistoryXML);

	//TODO 此处可进行解密

	std::stringstream memoSS;
	memoSS.str(memoXML);
	std::stringstream bookmarkSS;
	bookmarkSS.str(bookmarkXML);
	std::stringstream historySS;
	historySS.str(historyXML);

	auto memo=SerializationUtility<MemoStorage>::load(memoSS);
	auto bookmark=SerializationUtility<MemoBookmark>::load(bookmarkSS);
	auto history=SerializationUtility<MemoBookmark>::load(historySS);
	printf("Complete\n");
}

TEST(Serialization,tmp4)
{
	MemoBookmark bookmark;
	std::list<std::pair<std::string,std::string>> list;
	list.emplace_back("TestKey1","TestValue1");
	list.emplace_back("TestKey2","TestValue2");
	list.emplace_back("TestKey3","TestValue3");
	list.emplace_back("TestKey4","TestValue4");

	for(auto &r:list)
	{
		bookmark.addBookmark(r.first);
	}


	std::stringstream ss;
	SerializationUtility<MemoBookmark>::save(bookmark,ss);
	printf("%s\n",ss.str().c_str());
	auto loadedBookmark=SerializationUtility<MemoBookmark>::load(ss);
	int a=0;
}