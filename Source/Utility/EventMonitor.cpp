#include <utility>

#include <utility>

//
// Created by 星落_月残 on 2018/6/12.
//

#include <exception>
//#include "../Config/Constants.h"
#include "EventMonitor.h"
#include "ParameterDecorator.h"
#include "Commons.h"


HandlerMapKey::HandlerMapKey(const std::string &inName,long long inPriority)
		:name(inName),priority(inPriority)
{
}
bool HandlerMapKey::operator==(const HandlerMapKey &rhs) const
{
	return name==rhs.name;
}
bool HandlerMapKey::operator!=(const HandlerMapKey &rhs) const
{
	return !(rhs==*this);
}
HandlerMapKey::operator std::string()
{
	return name;
}
bool HandlerMapKey::operator<(const HandlerMapKey &rhs) const
{
	if(this->priority!=COMPARER_IGNORE_PRIORITY&&rhs.priority!=COMPARER_IGNORE_PRIORITY)
	{
		return this->priority<rhs.priority;//0为最高优先
	}
//	else if(this->priority!=COMPARER_IGNORE_PRIORITY&&rhs.priority==COMPARER_IGNORE_PRIORITY)
//	{
//		return true;
//	}
//	else if(this->priority==COMPARER_IGNORE_PRIORITY&&rhs.priority!=COMPARER_IGNORE_PRIORITY)
//	{
//		return false;
//	}
	else
	{
		return this->name<rhs.name;
	}
}


EventMonitor::~EventMonitor()
{
}
std::shared_ptr<EventHandler> EventMonitor::getEventHandlerByName(const std::string &inputName)
{
	return interveningEventHandlers.at(inputName);
}
void EventMonitor::AddEventHandler(const std::string &handlerName,
								   std::function<void(EventMonitor *,std::any &&)> toExec)
{
	if(interveningEventHandlers.count(handlerName)!=0)
		throw std::invalid_argument("EventMonitor::AddEventHandler: Duplicate handler name is not allowed.");
	interveningEventHandlers.emplace(handlerName,
									 std::make_shared<EventHandler>(handlerName,
																	std::bind(toExec,this,std::placeholders::_1),
																	this));
}
void EventMonitor::RemoveEventHandler(const std::string &handlerName)
{
	parameters.erase(handlerName);
}
std::any &EventMonitor::getParameterByName(const std::string &inputName)
{
	//注意处理out_of_range异常
	return parameters.at(inputName);
}

void EventMonitor::AddParameter(const std::string &inputName,const std::any &params)
{
	if(parameters.count(inputName)!=0)
		throw std::invalid_argument("EventMonitor::AddParameter: Duplicate parameter name is not allowed.");
	parameters.emplace(inputName,params);
}
void EventMonitor::RemoveParameter(const std::string &inputName)
{
	parameters.erase(inputName);
}


std::shared_ptr<EventHandler> MonitorBase::getEventHandler(const std::string &inputName)
{
	return std::move(eventMonitor.getEventHandlerByName(inputName));
}
void MonitorBase::addHandler(const std::string &handlerName,
							 std::function<void(EventMonitor *,std::any &&)> toExec)
{

	//!Duplication of EventMonitor::AddEventHandler, to remove function copy
	if(eventMonitor.interveningEventHandlers.count(handlerName)!=0)
		throw std::invalid_argument("MonitorBase::addHandler: Duplicate handler name is not allowed.");
	eventMonitor.interveningEventHandlers.emplace(handlerName,
												  std::make_shared<EventHandler>(handlerName,
																				 std::bind(toExec,&this->eventMonitor,std::placeholders::_1),
																				 &this->eventMonitor));
}
std::any &MonitorBase::getParameter(const std::string &inputName)
{
	return eventMonitor.getParameterByName(inputName);
}
void MonitorBase::addParameter(const std::string &inputName,const std::any &params)
{
	eventMonitor.AddParameter(inputName,params);
}


EventHandler::EventHandler(const std::string &inputName,
						   std::function<void(std::any &&)> toExec,
						   EventMonitor *inputIncludedIn)
		:handlerName(inputName),function(std::move(toExec)),includedIn(inputIncludedIn)
{
}
void EventHandler::operator()(std::any &&params)
{
	function.operator()(std::move(params));
}
EventHandler::~EventHandler()
{
	for(auto &r:insertedIn)
	{
		if(r.first)
		{
			r.first->Unregister(r.second);
		}
	}
	insertedIn.clear();
}
void EventHandler::addInsertedListenerProperty(EventListener *inListener,const std::string &inName)
{
	insertedIn.emplace(inListener,inName);
}
void EventHandler::removeInsertedListenerProperty(EventListener *inListener)
{
	insertedIn.erase(inListener);
}
const std::string &EventHandler::getHandlerName() const
{
	return handlerName;
}
EventMonitor *EventHandler::getIncludedIn() const
{
	return includedIn;
}


EventListener::~EventListener()
{
	for(auto &r:triggers)
	{
		r.second->removeInsertedListenerProperty(this);
	}
}

void EventListener::onTriggered(const std::any &args)
{
	for(auto &r:triggers)
		r.second->operator()(std::move(std::any(args)));
}
void EventListener::Register(const std::string &name,
							 std::shared_ptr<EventHandler> handler,
							 int priority)
{
	handler->addInsertedListenerProperty(this,name);
	triggers.emplace(HandlerMapKey(name,priority),handler);
}
void EventListener::Unregister(const std::string &name)
{
	if(triggers.count(name)!=0)
	{
		triggers.at(name)->removeInsertedListenerProperty(this);
		triggers.erase(name);
	}
}


void ListenerBase::addListener(const std::string &listenerName)
{
	listeners.emplace(listenerName,std::make_unique<EventListener>());
}
void ListenerBase::removeListener(const std::string &listenerName)
{
	listeners.erase(listenerName);
}
void ListenerBase::registerHandler(const std::string &listenerName,const std::string &handlerName,std::shared_ptr<EventHandler> handler,int priority)
{
	listeners.at(listenerName)->Register(handlerName,std::move(handler),priority);
}
void ListenerBase::unregisterHandler(const std::string &listenerName,const std::string &handlerName)
{
	if(listeners.count(listenerName)!=0)
		listeners.at(listenerName)->Unregister(handlerName);
}
void ListenerBase::onTriggered(const std::string &listenerName,const std::any &args)
{
	listeners.at(listenerName)->onTriggered(args);
}


