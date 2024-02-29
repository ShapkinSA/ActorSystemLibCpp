//
// Created by user on 20.02.24.
//

#ifndef ACTORSYSTEM_ABSTRACTACTOR_H
#define ACTORSYSTEM_ABSTRACTACTOR_H

#include <string>
#include "../actorSystem/ActorSystem.h"
#include "../utils/Logger.h"
#include <queue>
#include <functional>
#include <typeindex>
#include <any>
#include <utility>
#include "../dataExchanger/DataExchanger.h"

#define setCallback(type,function) (callbackMap[typeid(type)] = [this](const std::string & sender,  const MessageBox *mb){ function(sender,dynamic_cast<const type*>(mb));}  )

class ActorSystem;

class AbstractActor {
public:
    explicit AbstractActor(std::string name);
    virtual ~AbstractActor() = default;

public:
    std::string name;
    void pushTask(const std::shared_ptr<DataExchanger>&dataExchanger);
    void popTask();
    void setActorSystem(ActorSystem * actorSystemPtr);
    void tell(const std::string &receiver, MessageBox *& messageBox);
    virtual void preStart(){};
    virtual void postStop(){};
private:
    ActorSystem *actorSystem;
    std::queue<std::shared_ptr<DataExchanger>> actorRequests;
    void traceQueue();

protected:
    std::map<const std::type_index,  std::function<void(const std::string &, const MessageBox *)>> callbackMap;
};


#endif //ACTORSYSTEM_ABSTRACTACTOR_H
