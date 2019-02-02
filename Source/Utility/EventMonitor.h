//
// Created by 星落_月残 on 2018/6/12.
//



#ifndef TRIGGER_EVENTMONITOR_H
#define TRIGGER_EVENTMONITOR_H

#include <string>
#include <map>
#include <any>
#include <memory>
#include <functional>
#include "Comparer.h"
#include "../Config/Constants.h"

class HandlerMapKey
{
public:
	HandlerMapKey() = default;
	HandlerMapKey(const HandlerMapKey &another) = default;
	HandlerMapKey(const std::string &inName,long long inPriority=COMPARER_IGNORE_PRIORITY);//!Not marked Explicit
	~HandlerMapKey() = default;
	bool operator==(const HandlerMapKey &rhs) const;
	bool operator!=(const HandlerMapKey &rhs) const;
	bool operator<(const HandlerMapKey &rhs) const;
	explicit operator std::string();
	std::string name;
	long long priority=COMPARER_IGNORE_PRIORITY;
};




class EventHandler;

using Parameters=std::map<std::string,std::any>;
using ListenerHandlerMap=std::map<HandlerMapKey,
							   std::shared_ptr<EventHandler>,
							   AbstractAscendingComparer<HandlerMapKey>>;//!为了引入调用优先级
using EventHandlerMap=std::map<std::string,
							   std::shared_ptr<EventHandler>,
							   AbstractAscendingComparer<std::string>>;

class MonitorBase;

class EventMonitor
{
	friend MonitorBase;
public:
	EventMonitor() = default;
	EventMonitor(const EventMonitor &another);
	~EventMonitor();
	std::shared_ptr<EventHandler> getEventHandlerByName(const std::string &inputName);
	//!
	//! \param handlerName
	//! \param toExec 注意：
	//! 如果传入lambda，且需要引用Monitor的方法，
	//! 可以使用std::bind来绑定对象指针，
	//!	lambda的参数列表可能类似于
	//! “BasicEventMonitor *p,(其他参数)”
	void AddEventHandler(const std::string &handlerName,
						 std::function<void(EventMonitor *,std::any &&)> toExec);
	void RemoveEventHandler(const std::string &handlerName);
	std::any &getParameterByName(const std::string &inputName);
	void AddParameter(const std::string &inputName,const std::any &params);
	void RemoveParameter(const std::string &inputName);
//protected:
	EventHandlerMap interveningEventHandlers;
	Parameters parameters;
};

//!作为使用EventMonitor的基类
class MonitorBase
{
public:
	MonitorBase() = default;
	std::shared_ptr<EventHandler> getEventHandler(const std::string &inputName);
	//!
	//! \param handlerName
	//! \param toExec 注意：
	//! 如果传入lambda，且需要引用Monitor的方法，
	//! 可以使用std::bind来绑定对象指针，
	//!	lambda的参数列表可能类似于
	//! “BasicEventMonitor *p,(其他参数)”
	void addHandler(const std::string &handlerName,
					std::function<void(EventMonitor *,std::any &&)> toExec);
	std::any &getParameter(const std::string &inputName);
	void addParameter(const std::string &inputName,const std::any &params);
private:
	EventMonitor eventMonitor;
};

class EventListener;

class EventHandler
{
public:
	EventHandler() = delete;
	EventHandler(const std::string &inputName,std::function<void(std::any &&)> toExec,EventMonitor *inputIncludedIn);
	EventHandler(const EventHandler &another) = default;
	virtual void operator()(std::any &&params);//可默认使用传入的function，也可继承实现具体功能
	virtual ~EventHandler();
	const std::string &getHandlerName() const;
	EventMonitor *getIncludedIn() const;
private:
	friend EventListener;
	void addInsertedListenerProperty(EventListener *inListener,const std::string &inName);
	void removeInsertedListenerProperty(EventListener *inListener);
protected:
	std::string handlerName;
	std::function<void(std::any &&)> function;
	EventMonitor *includedIn;
	std::map<EventListener *,std::string> insertedIn;
};

//!此处可视为多个Monitor的handler的统一管理,用于作为基类
class EventListener
{
public:
	EventListener() = default;
	EventListener(const EventListener &another);
	~EventListener();
	void onTriggered(const std::any &args);
	void Register(const std::string &name,std::shared_ptr<EventHandler> handler,int priority=COMPARER_IGNORE_PRIORITY);
	void Unregister(const std::string &name);
private:
	ListenerHandlerMap triggers;
};


//!作为使用EventListener的基类
//考虑了eventHandler预先被析构的情况
class ListenerBase
{
public:
	ListenerBase() = default;
	void addListener(const std::string &listenerName);
	void removeListener(const std::string &listenerName);
	void registerHandler(const std::string &listenerName,const std::string &handlerName,std::shared_ptr<EventHandler> handler,int priority=COMPARER_IGNORE_PRIORITY);
	void unregisterHandler(const std::string &listenerName,const std::string &handlerName);
	void onTriggered(const std::string &listenerName,const std::any &args);
private:
	std::map<std::string,std::unique_ptr<EventListener>> listeners;
};


#endif //TRIGGER_EVENTMONITOR_H
