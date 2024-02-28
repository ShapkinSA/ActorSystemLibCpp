//
// Created by user on 20.02.24.
//

#ifndef ACTORSYSTEM_ABSTRACTACTOR_H
#define ACTORSYSTEM_ABSTRACTACTOR_H

#include <string>
#include "code/actorSystem/ActorSystem.h"
#include "code/utils/Logger.h"
#include <queue>
#include <functional>
#include <typeindex>
#include <any>
#include <utility>
#include "code/dataExchanger/DataExchanger.h"

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

    template<typename T, typename std::enable_if<std::is_base_of<MessageBox, T>::value>::type * = nullptr>
    void tell(const std::string &receiver, T *& messageBox) {
        actorSystem->pushTask(std::make_shared<DataExchanger>(name, receiver, dynamic_cast<MessageBox*>(messageBox)));
        messageBox = nullptr;
    }

private:
    ActorSystem *actorSystem;
    std::queue<std::shared_ptr<DataExchanger>> actorRequests;
    void traceQueue();

protected:
    std::map<const std::type_index,  std::function<void(const std::string &, const MessageBox *)>> callbackMap;
};


#endif //ACTORSYSTEM_ABSTRACTACTOR_H
