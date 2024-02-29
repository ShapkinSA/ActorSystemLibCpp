//
// Created by user on 21.02.24.
//

#include "DataExchanger.h"

DataExchanger::DataExchanger(std::string  sender, const std::list<std::string> &receivers, const MessageBox *messageBox) : sender(std::move(sender)), receivers(receivers){
    this->messageBox = messageBox;
}

DataExchanger::~DataExchanger() {
    if(messageBox!= nullptr){
        delete messageBox;
    }
}
