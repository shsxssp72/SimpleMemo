//
// Created by 星落_月残 on 2019/1/23.
//

#ifndef SIMPLEMEMO_MEMOINTERFACEPROVIDER_H
#define SIMPLEMEMO_MEMOINTERFACEPROVIDER_H

#include <memory>
#include "../../Entity/MemoStorage.h"
#include "../AbstractInterfaceProvider.h"
#include "AccessMemoInterface.h"


class MemoInterfaceProvider:public AbstractInterfaceProvider<MemoStorage,AccessMemoInterface>
{
public:
	MemoInterfaceProvider();
	explicit MemoInterfaceProvider(const std::shared_ptr<MemoStorage> &memoStorage);
	std::shared_ptr<AccessMemoInterface> getMemoInterface();
protected:
	void resetMemoStorage(const std::shared_ptr<MemoStorage> &inMemoStorage);
	void saveMemoStorage(std::ostream &out);
private:
	std::shared_ptr<AccessMemoInterface> getContainedDataInterface()const  override;
	void resetContainedData(const std::shared_ptr<MemoStorage> &inData) override;
	void saveContainedData(std::ostream &out) override;
private:
	std::shared_ptr<MemoStorage> memoStorage;
};
#endif //SIMPLEMEMO_MEMOINTERFACEPROVIDER_H
