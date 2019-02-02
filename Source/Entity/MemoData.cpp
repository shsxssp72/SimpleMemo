//
// Created by 星落_月残 on 2018/12/23.
//

#include "MemoData.h"


MemoData::MemoData(std::string key,std::string value)
		:item(key,value),accessFrequency(0)
{
	visitTimestamp=std::chrono::steady_clock::now();
}
MemoData::MemoData(const MemoData &another)
{
	this->item=another.item;
	this->visitTimestamp=another.visitTimestamp;
	this->accessFrequency=another.accessFrequency;
}
void MemoData::updateVisitTimeAndFrequency()
{
	visitTimestamp=std::chrono::steady_clock::now();
	accessFrequency++;
}
const std::string &MemoData::getKey() const
{
	return item.first;
}
const std::string &MemoData::getValue() const
{
	return item.second;
}
void MemoData::setKey(const std::string &newKey)
{
	item.first=newKey;
}
void MemoData::setValue(const std::string &newValue)
{
	item.second=newValue;
}

const std::chrono::steady_clock::time_point &MemoData::getVisitTimestamp() const
{
	return visitTimestamp;
}
long long int MemoData::getAccessFrequency() const
{
	return accessFrequency;
}

