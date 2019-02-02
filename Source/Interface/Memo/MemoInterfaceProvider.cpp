//
// Created by 星落_月残 on 2019/1/23.
//

#include "../../Utility/SerializationUtility.h"
#include "MemoInterfaceProvider.h"
#include "AccessMemoInterfaceImpl.h"


MemoInterfaceProvider::MemoInterfaceProvider()
		:memoStorage(nullptr)
{
}
MemoInterfaceProvider::MemoInterfaceProvider(const std::shared_ptr<MemoStorage> &memoStorage)
		:memoStorage(memoStorage)
{
}
std::shared_ptr<AccessMemoInterface> MemoInterfaceProvider::getMemoInterface()
{
	return this->getContainedDataInterface();
}
void MemoInterfaceProvider::resetMemoStorage(const std::shared_ptr<MemoStorage> &inMemoStorage)
{
	this->resetContainedData(inMemoStorage);
}
void MemoInterfaceProvider::saveMemoStorage(std::ostream &out)
{
	this->saveContainedData(out);
}
std::shared_ptr<AccessMemoInterface> MemoInterfaceProvider::getContainedDataInterface() const
{
	return std::make_shared<AccessMemoInterfaceImpl>(memoStorage);
}
void MemoInterfaceProvider::resetContainedData(const std::shared_ptr<MemoStorage> &inData)
{
	memoStorage=inData;
}
void MemoInterfaceProvider::saveContainedData(std::ostream &out)
{
	SerializationUtility<MemoStorage>::save(*this->memoStorage,out);
}

