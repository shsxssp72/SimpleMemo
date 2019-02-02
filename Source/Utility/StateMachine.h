//
// Created by 星落_月残 on 2019/1/30.
//

#ifndef SIMPLEMEMO_STATEMACHINE_H
#define SIMPLEMEMO_STATEMACHINE_H

#include "EventMonitor.h"

class State;

class StateMachine
{
public:
	StateMachine();
	StateMachine(const StateMachine &another)= delete;
	void addState(const std::string &stateName);
	void removeState(const std::string &stateName);
	void connect(const std::string &fromStateName,const std::string &toStateName);
	void disconnect(const std::string &fromStateName,const std::string &toStateName);
	void addStateActivationHandler(const std::string &stateName,const std::string &handlerName,
			std::shared_ptr<EventHandler> handler,int priority=COMPARER_IGNORE_PRIORITY);
	void transferToState(const std::string &nextStateName,std::any &&params);
	const std::string &getCurrentStateName();
private:
	std::map<std::string,std::shared_ptr<State>> states;
	std::shared_ptr<State> currentState;
};

class State:public ListenerBase
{
	friend class StateMachine;

public:
	State() = delete;
	explicit State(const std::string &inName);
	State(const State &another) = delete;const std::string &getStateName() const;
private:
	void addNextState(const std::string &nextStateName,std::shared_ptr<State> pState);
	void removeNextState(const std::string &nextStateName);
	void onActivation(std::any &&params);
private:
	std::string stateName;
	std::map<std::string,std::shared_ptr<State>> nextStates;

};

#endif //SIMPLEMEMO_STATEMACHINE_H
