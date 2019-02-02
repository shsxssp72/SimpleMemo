//
// Created by 星落_月残 on 2019/1/22.
//

#include "../Entity/TransferEntity.h"
#include "../Interface/Memo/AccessMemoInterfaceImpl.h"
#include "../Utility/SerializationUtility.h"
#include "../Utility/CompressUtility.h"
#include "../Utility/Crypto.h"
#include "../Config/Constants.h"
#include "MemoCore.h"


MemoCore::MemoCore()
{
	auto crypto=Crypto::getInstance();
	//!params 要求为文件名
	this->addHandler(MEMOCORE_LOAD_HANDLER_NAME,
					 [this](EventMonitor *monitor,std::any &&params)
					 {
						 auto crypto=Crypto::getInstance();
						 std::string memoFileName=std::any_cast<std::string>(params);
						 if(!memoFileName.empty())
						 {
							 std::ifstream fin(memoFileName);
							 auto loadedEntity=SerializationUtility<TransferEntity>::load(fin);

							 std::string memoXML=CompressUtility::Uncompress(crypto.getOperation("Base64Decode").operator()(CryptoParameters(loadedEntity->memoStorage)));
							 std::string bookmarkXML=CompressUtility::Uncompress(crypto.getOperation("Base64Decode").operator()(CryptoParameters(loadedEntity->bookmark)));
							 std::string historyXML=CompressUtility::Uncompress(crypto.getOperation("Base64Decode").operator()(CryptoParameters(loadedEntity->history)));

							 //TODO 此处可进行解密

							 std::stringstream memoSS;
							 memoSS.str(memoXML);
							 std::stringstream bookmarkSS;
							 bookmarkSS.str(bookmarkXML);
							 std::stringstream historySS;
							 historySS.str(historyXML);

							 this->resetMemoStorage(SerializationUtility<MemoStorage>::load(memoSS));
							 this->resetBookmark(SerializationUtility<MemoBookmark>::load(bookmarkSS));
							 this->resetHistory(SerializationUtility<MemoBookmark>::load(historySS));
						 }
						 else
						 {
							 this->resetMemoStorage(std::make_shared<MemoStorage>());
							 this->resetBookmark(std::make_shared<MemoBookmark>());
							 this->resetHistory(std::make_shared<MemoBookmark>());
						 }
					 });
	this->addHandler(MEMOCORE_SAVE_HANDLER_NAME,
					 [this](EventMonitor *monitor,std::any &&params)
					 {
						 auto crypto=Crypto::getInstance();
						 std::string memoFileName=std::any_cast<std::string>(params);
						 if(!memoFileName.empty())
						 {
							 std::ofstream fout(memoFileName);

							 std::stringstream memoSS;
							 std::stringstream bookmarkSS;
							 std::stringstream historySS;

							 this->saveMemoStorage(memoSS);
							 this->saveBookmark(bookmarkSS);
							 this->saveHistory(historySS);

							 std::string memoXML=memoSS.str();
							 std::string bookmarkXML=bookmarkSS.str();
							 std::string historyXML=historySS.str();

							 //TODO 此处可进行加密

							 TransferEntity transferEntity(
									 crypto.getOperation("Base64Encode").operator()(CryptoParameters(CompressUtility::Compress(memoXML))),
									 crypto.getOperation("Base64Encode").operator()(CryptoParameters(CompressUtility::Compress(bookmarkXML))),
									 crypto.getOperation("Base64Encode").operator()(CryptoParameters(CompressUtility::Compress(historyXML)))
							 );

							 SerializationUtility<TransferEntity>::save(transferEntity,fout);
						 }
					 });

}
