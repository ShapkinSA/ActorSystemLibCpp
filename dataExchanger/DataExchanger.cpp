//
// Created by user on 21.02.24.
//

#include "DataExchanger.h"

#include <utility>
#include <iostream>

DataExchanger::DataExchanger(std::string  sender, std::string  receiver, const MessageBox *messageBox) : sender(std::move(sender)), receiver(std::move(receiver)){
    this->messageBox = messageBox;
}

DataExchanger::~DataExchanger() {
    if(messageBox!= nullptr){
        delete messageBox;
    }
}
