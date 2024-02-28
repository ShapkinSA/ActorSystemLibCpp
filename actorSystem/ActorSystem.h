//
// Created by user on 20.02.24.
//

#ifndef ACTORSYSTEM_ACTORSYSTEM_H
#define ACTORSYSTEM_ACTORSYSTEM_H

#include <list>
#include <map>
#include <memory>
#include <queue>
#include <thread>
#include <chrono>
#include <iostream>
#include "code/abstractActor/AbstractActor.h"
#include "code/dataExchanger/DataExchanger.h"
#include "code/utils/Logger.h"
#include <concepts>


class AbstractActor;

class ActorSystem {
public:
    ActorSystem();

    template<typename T, typename std::enable_if<std::is_base_of<AbstractActor, T>::value>::type * = nullptr, typename... Arguments>
    T *createActor(const std::string &name, Arguments ... args) {
        T *t = new T(name, args...);
        t->setActorSystem(this);
        getActors()[name] = t;
        return t;
    }

    std::map<std::string, AbstractActor*> &getActors();
    void pushTask(const std::shared_ptr<DataExchanger>&dataExchanger);
    void popTask();

private:
    std::map<std::string, AbstractActor*> actors;
    std::queue<std::shared_ptr<DataExchanger>> tasks;
    void traceQueue();
};


#endif //ACTORSYSTEM_ACTORSYSTEM_H
