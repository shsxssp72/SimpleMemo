#include <utility>

//
// Created by 星落_月残 on 2019/1/30.
//

#include "StateMachine.h"


StateMachine::StateMachine()
{
	addState(DEFAULT_INITIAL_STATE_NAME);
	currentState=states.at(DEFAULT_INITIAL_STATE_NAME);
}
void StateMachine::addState(const std::string &stateName)
{
	states.emplace(stateName,std::make_shared<State>(stateName));
}
void StateMachine::removeState(const std::string &stateName)
{
	states.erase(stateName);
}
void StateMachine::connect(const std::string &fromStateName,const std::string &toStateName)
{
	if(states.count(fromStateName)==0)
	{
		throw std::invalid_argument("StateMachine::connect: fromState does not exist: "+fromStateName);
	}
	if(states.count(toStateName)==0)
	{
		throw std::invalid_argument("StateMachine::connect: toState does not exist: "+toStateName);
	}
	states.at(fromStateName)->addNextState(toStateName,states.at(toStateName));
}
void StateMachine::disconnect(const std::string &fromStateName,const std::string &toStateName)
{
	if(states.count(fromStateName)==0)
	{
		throw std::invalid_argument("StateMachine::disconnect: fromState does not exist: "+fromStateName);
	}
	if(states.count(toStateName)==0)
	{
		throw std::invalid_argument("StateMachine::disconnect: toState does not exist: "+toStateName);
	}
	states.at(fromStateName)->removeNextState(toStateName);
}
void StateMachine::addStateActivationHandler(const std::string &stateName,const std::string &handlerName,std::shared_ptr<EventHandler> handler,int priority)
{
	if(states.count(stateName)==0)
	{
		throw std::invalid_argument("StateMachine::addStateActivationHandler: state does not exist: "+stateName);
	}
	states.at(stateName)->registerHandler(DEFAULT_STATE_LISTENER_NAME,stateName,std::move(handler),priority);
}
void StateMachine::transferToState(const std::string &nextStateName,std::any &&params)
{
	if(currentState->nextStates.count(nextStateName)!=0)
	{
		currentState=currentState->nextStates.at(nextStateName);
		currentState->onActivation(std::move(params));
	}
	else
	{
		throw std::invalid_argument("StateMachine::transferToState: No valid connection from "+getCurrentStateName()+" to "+nextStateName);
	}
}
const std::string &StateMachine::getCurrentStateName()
{
	return currentState->stateName;
}


State::State(const std::string &inName)
		:stateName(inName)
{
	this->addListener(DEFAULT_STATE_LISTENER_NAME);
}
const std::string &State::getStateName() const
{
	return stateName;
}
void State::addNextState(const std::string &nextStateName,std::shared_ptr<State> pState)
{
	nextStates.emplace(nextStateName,pState);
}
void State::removeNextState(const std::string &nextStateName)
{
	nextStates.erase(nextStateName);
}
void State::onActivation(std::any &&params)
{
	this->onTriggered(DEFAULT_STATE_LISTENER_NAME,params);
}
