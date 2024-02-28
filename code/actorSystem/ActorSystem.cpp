//
// Created by user on 20.02.24.
//

#include "ActorSystem.h"

std::map<std::string, AbstractActor*> &ActorSystem::getActors() {
    return actors;
}

void ActorSystem::popTask() {
    tasks.pop();
}

void ActorSystem::traceQueue() {
    std::thread t([this]() {
                      while(1){
                          if (!tasks.empty()) {
                              auto currentTask = tasks.front();
                              log_info("ActorSystem found task: sender: {}, receiver: {}, type: {}. size of tasks {}", currentTask->sender, currentTask->receiver, typeid(*currentTask->messageBox).name(), tasks.size());
                              if(actors.contains(currentTask->receiver)){
                                  actors[currentTask->receiver]->pushTask(currentTask);
                              }
                              popTask();
                          }
                          log_info("size of tasks {}", tasks.size());
                          std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                      }
                  }
    );
    t.detach();
}

ActorSystem::ActorSystem() {
    traceQueue();
}

void ActorSystem::pushTask(const std::shared_ptr<DataExchanger>&dataExchanger) {
    tasks.push(dataExchanger);
}
