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

                              std::stringstream  receivers;
                              std::copy(currentTask->receivers.begin(),currentTask->receivers.end(), std::ostream_iterator<std::string>(receivers,", "));

                              log_info("ActorSystem found task: sender: {}, receivers: {} type: {}. size of tasks {}", currentTask->sender, receivers.str(), typeid(*currentTask->messageBox).name(), tasks.size());

                              for (const std::string& receiver : currentTask->receivers) {
                                  if (actors.contains(receiver)) {
                                      actors[receiver]->pushTask(currentTask);
                                  }
                              }
                              popTask();
                          }
                          log_info("size of tasks {}", tasks.size());
                          std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
