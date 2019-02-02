//
// Created by 星落_月残 on 2019/1/23.
//

#ifndef SIMPLEMEMO_ABSTRACTINTERFACEPROVIDER_H
#define SIMPLEMEMO_ABSTRACTINTERFACEPROVIDER_H

#include <memory>


template<class DataType,class DataInterfaceType>
class AbstractInterfaceProvider
{
protected:
	virtual std::shared_ptr<DataInterfaceType> getContainedDataInterface() const = 0;
	virtual void resetContainedData(const std::shared_ptr<DataType> &inData) = 0;
	virtual void saveContainedData(std::ostream &out) = 0;
};

#endif //SIMPLEMEMO_ABSTRACTINTERFACEPROVIDER_H
